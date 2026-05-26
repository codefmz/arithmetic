#include <iostream>
#include "gtest/gtest.h"
#include "class.h"
#include "priorityqueue.h"

class priorityqueueTest : public ::testing::Test {
protected:
    priorityqueueTest() {
    }
    ~priorityqueueTest() override {
    }
    void SetUp() override {
    }
    void TearDown() override {
    }
};

TEST_F(priorityqueueTest, test1) {
    BinaryHeap<int> ibh;
    ibh.insert(1);
    ibh.insert(2);
    ibh.insert(3);
    ibh.insert(5);
    ibh.insert(7);
    ibh.insert(1);
    ibh.insert(10);
    ibh.insert(20);

    while (!ibh.isEmpty()) {
        int temp = 0;
        ibh.deleteMin(temp);
        cout << temp << endl;
    }
}