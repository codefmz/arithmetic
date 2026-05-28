#ifndef LOCK_FREE_STACK_H
#define LOCK_FREE_STACK_H

#include <atomic>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <memory>
#include <new>
#include <utility>
#include <vector>

template <typename Object>
class lock_free_stack {
private:
    static const uint32_t nullIndex = std::numeric_limits<uint32_t>::max();

    struct Node {
        std::unique_ptr<Object> data;
        std::atomic<uint32_t> next;

        Node() : data(nullptr), next(nullIndex) {}
    };

    class TaggedStack {
    public:
        TaggedStack() : head(pack(nullIndex, 0)) {}

        void push(uint32_t index, std::vector<std::unique_ptr<Node>>& nodes) {
            if (index == nullIndex) {
                return;
            }

            uint64_t oldHead = head.load(std::memory_order_acquire);
            uint64_t newHead;

            do {
                nodes[index]->next.store(getIndex(oldHead), std::memory_order_relaxed);
                newHead = pack(index, getVersion(oldHead) + 1);
            } while (!head.compare_exchange_weak(
                oldHead,
                newHead,
                std::memory_order_release,
                std::memory_order_acquire));
        }

        uint32_t pop(std::vector<std::unique_ptr<Node>>& nodes) {
            uint64_t oldHead = head.load(std::memory_order_acquire);
            uint64_t newHead;

            do {
                const uint32_t oldIndex = getIndex(oldHead);
                if (oldIndex == nullIndex) {
                    return nullIndex;
                }

                const uint32_t nextIndex =
                    nodes[oldIndex]->next.load(std::memory_order_acquire);
                newHead = pack(nextIndex, getVersion(oldHead) + 1);
            } while (!head.compare_exchange_weak(
                oldHead,
                newHead,
                std::memory_order_acq_rel,
                std::memory_order_acquire));

            const uint32_t index = getIndex(oldHead);
            nodes[index]->next.store(nullIndex, std::memory_order_relaxed);
            return index;
        }

        bool empty() const {
            return getIndex(head.load(std::memory_order_acquire)) == nullIndex;
        }

    private:
        static uint64_t pack(uint32_t index, uint32_t version) {
            return (static_cast<uint64_t>(version) << 32) | index;
        }

        static uint32_t getIndex(uint64_t value) {
            return static_cast<uint32_t>(value);
        }

        static uint32_t getVersion(uint64_t value) {
            return static_cast<uint32_t>(value >> 32);
        }

    private:
        std::atomic<uint64_t> head;
    };

public:
    explicit lock_free_stack(std::size_t capacity = 1024) {
        if (capacity >= nullIndex) {
            throw std::bad_alloc();
        }

        nodes.reserve(capacity);
        for (std::size_t i = 0; i < capacity; ++i) {
            nodes.push_back(std::unique_ptr<Node>(new Node));
            mFreeStack.push(static_cast<uint32_t>(i), nodes);
        }
    }

    ~lock_free_stack() = default;

    lock_free_stack(const lock_free_stack&) = delete;
    lock_free_stack& operator=(const lock_free_stack&) = delete;

    void push(const Object& value) {
        const uint32_t index = acquireNode(value);
        mUsedStack.push(index, nodes);
    }

    void push(Object&& value) {
        const uint32_t index = acquireNode(std::move(value));
        mUsedStack.push(index, nodes);
    }

    template <typename... Args>
    void emplace(Args&&... args) {
        const uint32_t index = acquireNode(std::forward<Args>(args)...);
        mUsedStack.push(index, nodes);
    }

    bool pop(Object& value) {
        const uint32_t index = mUsedStack.pop(nodes);
        if (index == nullIndex) {
            return false;
        }

        value = std::move(*nodes[index]->data);
        releaseNode(index);
        return true;
    }

    bool empty() const {
        return mUsedStack.empty();
    }

private:
    template <typename... Args>
    uint32_t acquireNode(Args&&... args) {
        const uint32_t index = mFreeStack.pop(nodes);
        if (index == nullIndex) {
            throw std::bad_alloc();
        }

        nodes[index]->data.reset(new Object(std::forward<Args>(args)...));
        return index;
    }

    void releaseNode(uint32_t index) {
        nodes[index]->data.reset();
        nodes[index]->next.store(nullIndex, std::memory_order_relaxed);
        mFreeStack.push(index, nodes);
    }

private:
    std::vector<std::unique_ptr<Node>> nodes;
    TaggedStack mUsedStack;
    TaggedStack mFreeStack;
};

#endif
