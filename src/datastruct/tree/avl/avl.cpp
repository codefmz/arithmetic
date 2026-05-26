#include <iostream>
#include "gtest/gtest.h"
#include "class.h"
#include "avl.h"

class avlTest : public ::testing::Test {
protected:
    avlTest() {
    }
    ~avlTest() override {
    }
    void SetUp() override {
    }
    void TearDown() override {
    }
};

TEST_F(avlTest, test1) {
    AvlTree<int> avli;
    avli.insert(4);
    avli.insert(5);
    avli.insert(6);
    avli.insert(1);
    avli.insert(2);
    avli.insert(3);

    avli.printTree();
}