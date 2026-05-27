#include <thread>
#include <array>
#include "lock_free_stack.h"
#include "gtest/gtest.h"
#include "class.h"

using std::thread;

class lockFreeStackTest : public ::testing::Test {
protected:
    lockFreeStackTest() {
    }
    ~lockFreeStackTest() override {
    }
    void SetUp() override {
    }
    void TearDown() override {
    }
};

TEST_F(lockFreeStackTest, lockFreeStackTest1) {
    lock_free_stack freeStack;
    lock_free_stack usedStack;

    Node *node;
    for (int i = 0; i < 100; ++i) {
        node = new Node(0);
        freeStack.push(node);
    }

    for (int i = 0; i < 100; ++i) {
        node = freeStack.pop();
        node->data = i;
        usedStack.push(node);
    }

    for (int i = 0; i < 100; ++i) {
        node = usedStack.pop();
        EXPECT_EQ(node->data, 100 - i - 1);
    }
}

std::atomic<int> num(0);
void threadPush(lock_free_stack &freeStack)
{
    int count = 100;
    Node *node;
    while (count--) {
        node = new Node(0);
        freeStack.push(node);
        num.fetch_add(1);
    }
}

std::atomic<int> num2(0);
void threadPop(lock_free_stack &freeStack, lock_free_stack &usedStack)
{
    Node *node;
    do {
        node = freeStack.pop();
        if (node == nullptr) {
            break;
        }
        usedStack.push(node);
        num2.fetch_add(1);
    } while (true);
}

TEST_F(lockFreeStackTest, lockFreeStackTest2) {
    lock_free_stack freeStack;
    lock_free_stack usedStack;

    std::array<std::thread, 4> threads;
    for (int i = 0; i < 4; ++i) {
        threads[i] = std::thread(threadPush, std::ref(freeStack));
    }

    for (int i = 0; i < 4; ++i) {
        threads[i].join();
    }

    std::array<std::thread, 4> threads2;
    for (int i = 0; i < 4; ++i) {
        threads2[i] = std::thread(threadPop, std::ref(freeStack), std::ref(usedStack));
    }
    for (int i = 0; i < 4; ++i) {
        threads2[i].join();
    }

    int i = 0;
    while (true) {
        if (usedStack.pop() == nullptr) {
            break;
        }
        ++i;
    }

    EXPECT_EQ(i, 400);
}