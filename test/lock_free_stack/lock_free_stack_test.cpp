#include <array>
#include <atomic>
#include <thread>

#include "gtest/gtest.h"
#include "lock_free_stack.h"

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
    lock_free_stack<int> usedStack;

    int value = 0;
    for (int i = 0; i < 100; ++i) {
        usedStack.push(i);
    }

    for (int i = 0; i < 100; ++i) {
        EXPECT_TRUE(usedStack.pop(value));
        EXPECT_EQ(value, 100 - i - 1);
    }
}

std::atomic<int> num(0);
void threadPush(lock_free_stack<int> &stack)
{
    int count = 100;
    while (count--) {
        stack.push(count);
        num.fetch_add(1);
    }
}

std::atomic<int> num2(0);
void threadPop(lock_free_stack<int> &freeStack, lock_free_stack<int> &usedStack)
{
    int value = 0;
    do {
        if (!freeStack.pop(value)) {
            break;
        }
        usedStack.push(value);
        num2.fetch_add(1);
    } while (true);
}

TEST_F(lockFreeStackTest, lockFreeStackTest2) {
    lock_free_stack<int> freeStack;
    lock_free_stack<int> usedStack;

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
    int value = 0;
    while (true) {
        if (!usedStack.pop(value)) {
            break;
        }
        ++i;
    }

    EXPECT_EQ(i, 400);
}
