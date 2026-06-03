#include "iterate.h"
#include "gtest/gtest.h"
#include <iostream>

using namespace std;

class iterateTest : public ::testing::Test {
protected:
    iterateTest() {
    }
    ~iterateTest() override {
    }
    void SetUp() override {
    }
    void TearDown() override {
    }
};

TEST_F(iterateTest, queueTest) {
    Queue queue;
}

TEST_F(iterateTest, honoiTest) {
    honoi(3, 'A', 'B', 'C');
}

TEST_F(iterateTest, mazeTest) {
    Maze maze(7, 6);
    maze.mazeInitialize();
    maze.printMaze();
    cout << "==================== "<< endl;
    maze.findWay(1, 1);
    maze.printMaze();
}