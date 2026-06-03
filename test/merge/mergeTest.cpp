#include "merge.h"
#include "gtest/gtest.h"
#include <iostream>

using namespace std;

class mergeTest : public ::testing::Test {
protected:
    mergeTest() {
    }
    ~mergeTest() override {
    }
    void SetUp() override {
    }
    void TearDown() override {
    }
};

TEST_F(mergeTest, minPointDis) {
    vector<pair<int, int>> points{ {-5,-9},{-4,4},{-6,3},{5,-9},{-2,10},{5,9},{4,4},{1,3},{2,10},{-7,-9},{-9, 7} };
    float minDis = findClosestDis(points);

    cout << "minDis:" << minDis << endl;
}