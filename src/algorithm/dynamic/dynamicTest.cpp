#include "dynamic.h"
#include "gtest/gtest.h"

class dynamicTest : public ::testing::Test {
protected:
    dynamicTest() {
    }
    ~dynamicTest() override {
    }
    void SetUp() override {
    }
    void TearDown() override {
    }
};

TEST_F(dynamicTest, robTest) {
    EXPECT_EQ(rob(vector<int>{1, 2, 3, 1}), 4);
    EXPECT_EQ(rob(vector<int>{2, 7, 9, 3, 1}), 12);
}

TEST_F(dynamicTest, dynamicBagTest) {
    vector<pair<int, float>> vct = {{3000, 3}, {1000, 1}, {2000, 2}, {1500, 1.5}};
    EXPECT_EQ(dynamicBag(vct, 5), 5000);
}