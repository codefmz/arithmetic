#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <functional>
#include <stack>
#include "treenode.h"
#include "disjset.h"

using namespace std;

//1. 拓扑排序
vector<int> topuSort(int num, const vector<vector<int>>& graph);

//2.广度优先算法
vector<vector<int>> bfs(TreeNode* root);

//3.深度优先算法
//递归法实现
void dfs(TreeNode* node, vector<int>& ans);
//迭代法实现
vector<int>  dfs(TreeNode* node);

//3. 最小路径算法 dijstra 算法
//稀疏图
vector<int> dijstra(int num, const vector<vector<int>>& vcts, int src);
//稠密图
vector<int> dijstra2(int num, const vector<vector<int>>& vcts, int src);

//4.最小树算法
//稠密图
vector<pair<int, int>> prim(int num, const vector<vector<int>>& vcts, int src);
//稀疏图
vector<pair<int, int>> kruskal(int num, const vector<vector<int>>& vcts);

#endif