#include <iostream>
#include "gtest/gtest.h"
#include "class.h"
#include "binarysearch.h"

class binarysearchTest : public ::testing::Test {
protected:
    binarysearchTest() {
    }
    ~binarysearchTest() override {
    }
    void SetUp() override {
    }
    void TearDown() override {
    }
};


void testBinarySearchTree()
{
    struct Compara {
        bool operator()(const Dog& d1, const Dog& d2) {
            return d1.name > d2.name;
        }
    };
    BinarySearchTree<Dog, Compara> bstd;
    Dog dog("4", "哈巴狗4");
    bstd.insert(dog);
    bstd.insert(Dog("2", "哈巴狗2"));
    bstd.insert(Dog("5", "哈巴狗3"));
    bstd.insert(Dog("7", "哈巴狗7"));
    bstd.insert(Dog("6", "哈巴狗6"));
    bstd.printTree();
    cout << "min" << bstd.findMin() << endl;
}

TEST_F(binarysearchTest, test1) {
    BinarySearchTree<int> bst;
    bst.insert(4);
    bst.insert(5);
    bst.insert(6);
    bst.insert(1);
    bst.insert(2);
    bst.insert(3);

    bst.printTree();
}