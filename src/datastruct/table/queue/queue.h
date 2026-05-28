#ifndef MY_QUEUE_H
#define MY_QUEUE_H

#include <list>
#include <cstddef>
#include <utility>

template <typename Object>
class MyQueue {
public:
    MyQueue() = default;
    std::size_t size() const{
        return c.size();
    }

    bool empty() const {
        return c.empty();
    }

    void clear() {
        c.clear();
    }

    void push(const Object& o) {
        c.push_back(o);
    }

    void push(Object&& o) {
        c.push_back(std::move(o));
    }

    void pop() {
        c.pop_front();
    }

    Object& front() {
        return c.front();
    }

    const Object& front() const {
        return c.front();
    }

    Object& back() {
        return c.back();
    }

    const Object& back() const {
        return c.back();
    }

private:
    std::list<Object> c;
};

#endif