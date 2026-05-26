#include <iostream>
#include "gtest/gtest.h"
#include "class.h"
#include "sort.h"

class sortTest : public ::testing::Test {
protected:
    sortTest() {
    }
    ~sortTest() override {
    }
    void SetUp() override {
    }
    void TearDown() override {
    }
};

TEST_F(sortTest, test1) {
    int* arr = new int[10]{1, 7, -1, 2, -5, 9, 0, -4, 10, 2};
    auto constexpr len = 10;
    sort(arr, len, quick3);

    for (size_t i = 0; i < len; i++) {
        cout << arr[i] << " ";
    }

    delete[] arr;
}