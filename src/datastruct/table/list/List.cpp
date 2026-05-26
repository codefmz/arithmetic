#include <iostream>
#include "List.h"
#include "gtest/gtest.h"
#include "class.h"

using namespace std;

class listTest : public ::testing::Test {
protected:
    listTest() {
    }
    ~listTest() override {
    }
    void SetUp() override {
    }
    void TearDown() override {
    }
};

TEST_F(listTest, test1) {
    List<int> aList;
    aList.push_back(4);
    aList.push_back(5);
    aList.push_back(6);
    aList.push_back(7);
    aList.push_back(1);
    aList.push_back(2);
    aList.push_back(3);


    for (auto& i : aList) {
        cout << " i = " << i << endl;
    }
    cout << " size = " << aList.size() << endl;
    cout << " front = " << aList.front() << endl;
}