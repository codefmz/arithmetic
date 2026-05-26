#include "graph.h"
#include "gtest/gtest.h"

class graphTest : public ::testing::Test {
protected:
    graphTest() {
    }
    ~graphTest() override {
    }
    void SetUp() override {
    }
    void TearDown() override {
    }
};

TEST_F(graphTest, topuSortTest) {
    vector<vector<int>> graph{ {1},{2,3},{4},{4},{} };
    vector<int> ret = topuSort(5, graph);

    vector<int> extected = {0, 1, 2, 3, 4};
    for (int i = 0; i < ret.size(); ++i) {
        EXPECT_EQ(ret[i], extected[i]);
    }
}

TEST_F(graphTest, bfsTest) {
    TreeNode f3l(15, nullptr, nullptr);
    TreeNode f3r(7, nullptr, nullptr);
    TreeNode f2r(20, &f3l, &f3r);
    TreeNode f2l(9, nullptr, nullptr);
    TreeNode root(3, &f2l, &f2r);

    vector<vector<int>> ret = bfs(&root);
    for (int i = 0; i < ret.size(); ++i) {
        for (int j = 0; j < ret[i].size(); ++j) {
            cout << ret[i][j] << " ";
        }
        cout << endl;
    }
}

TEST_F(graphTest, dfsTest1) {
    TreeNode f3l(15, nullptr, nullptr);
    TreeNode f3r(7, nullptr, nullptr);
    TreeNode f2r(20, &f3l, &f3r);
    TreeNode f2l(9, nullptr, nullptr);
    TreeNode root(3, &f2l, &f2r);

    vector<int> ret = dfs(&root);
    for (int i = 0; i < ret.size(); ++i) {
        cout << ret[i] << " ";
    }
}

TEST_F(graphTest, dfsTest2) {
    TreeNode f3l(15, nullptr, nullptr);
    TreeNode f3r(7, nullptr, nullptr);
    TreeNode f2r(20, &f3l, &f3r);
    TreeNode f2l(9, nullptr, nullptr);
    TreeNode root(3, &f2l, &f2r);

    vector<int> ret = dfs(&root);
    for (int i = 0; i < ret.size(); ++i) {
        cout << ret[i] << " ";
    }
}

TEST_F(graphTest, disjTest1) {
    vector<vector<int>> vcts{ {0,4,4},{0,1,2},{1,4,2},{1,2,3},{4,3,1},{4,2,0},{2,3,1} };
    auto ret = dijstra(5, vcts, 0);
    for (int i = 0; i < ret.size(); ++i) {
        cout << ret[i] << " ";
    }
}

TEST_F(graphTest, disjTest2) {
    vector<vector<int>> vcts{ {0,4,4},{0,1,2},{1,4,2},{1,2,3},{4,3,1},{4,2,0},{2,3,1} };
    auto ret = dijstra2(5, vcts, 0);
    for (int i = 0; i < ret.size(); ++i) {
        cout << ret[i] << " ";
    }
}

TEST_F(graphTest, primTest) {
    vector<vector<int>> vcts{ {0,4,4},{0,1,2},{1,4,2},{1,2,3},{4,3,1},{4,2,0},{2,3,1} };
    auto ret = prim(5, vcts, 0);

    for (int i = 0; i < ret.size(); ++i) {
        cout << "i = " << i << " " << ret[i].first << " " << ret[i].second << endl;
    }
}

TEST_F(graphTest, kruskalTest) {
    vector<vector<int>> vcts{ {0,4,4},{0,1,2},{1,4,2},{1,2,3},{4,3,1},{4,2,0},{2,3,1} };
    auto ret = kruskal(5, vcts);

    for (int i = 0; i < ret.size(); ++i) {
        cout << "i = " << i << " " << ret[i].first << " " << ret[i].second << endl;
    }
}


