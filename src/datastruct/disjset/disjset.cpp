#include "disjset.h"
#include "gtest/gtest.h"

class disjsetTest : public ::testing::Test {
protected:
    disjsetTest() {
    }
    ~disjsetTest() override {
    }
    void SetUp() override {
    }
    void TearDown() override {
    }
};

TEST_F(disjsetTest, test1) {
    DisjSet ds(10);
    ds.unionSet(0, 1);
    ds.unionSet(1, 2);
    ds.unionSet(2, 3);
    ds.unionSet(5, 4);
    ds.unionSet(5, 6);
    ds.unionSet(5, 1);


    EXPECT_EQ(ds.find(6), 1);
    EXPECT_EQ(ds.find(8), 8);
    ds.printset();
}