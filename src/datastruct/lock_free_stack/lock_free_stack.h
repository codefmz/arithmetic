#ifndef LOCK_FREE_STACK_H
#define LOCK_FREE_STACK_H

#include <atomic>
#include <memory>

struct Node {
    int data;
    Node *next;
    Node(int data) :data(data), next(nullptr) {}

};

class lock_free_stack {
private:
    std::atomic<Node*> head;
public:
    lock_free_stack() :head(nullptr) {}
    ~lock_free_stack() {
    }
    void push(Node *node) {
        if (node == nullptr) {
            return;
        }
        node->next = head.load();
        while (!head.compare_exchange_weak(node->next, node));
    };

    Node* pop() {
        Node* oldHead = head.load();
        while (oldHead != nullptr && !head.compare_exchange_weak(oldHead, oldHead->next));
        return oldHead;
    }
};
#endif