#include "hashsquare.h"
#include "gtest/gtest.h"

class hashsquareTest : public ::testing::Test {
protected:
    hashsquareTest() {
    }
    ~hashsquareTest() override {
    }
    void SetUp() override {
    }
    void TearDown() override {
    }
};

TEST_F(hashsquareTest, testHashTable) {
    HashTable<int> hashT;
    hashT.insert(0);
    hashT.insert(31);
    hashT.printHashTable();
}