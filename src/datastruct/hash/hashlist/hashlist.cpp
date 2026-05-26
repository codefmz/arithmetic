#include "hashlist.h"
#include "gtest/gtest.h"

class hashTest : public ::testing::Test {
protected:
    hashTest() {
    }
    ~hashTest() override {
    }
    void SetUp() override {
    }
    void TearDown() override {
    }
};

TEST_F(hashTest, testHashTable) {
    HashTable<int> hashT;
    hashT.insert(0);
    hashT.insert(31);
    hashT.printHashTable();
}