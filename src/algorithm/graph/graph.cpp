#include "graph.h"

vector<int> topuSort(int num, const vector<vector<int>>& graph) {
    //1. 获取入度
    vector<int> ret;
    vector<int> degree(num, 0);
    for (auto& vct : graph) {
        for (auto& i : vct) {
            ++degree[i];
        }
    }

    queue<int> qi;
    //2.入度放到 queue 中
    for_each(degree.begin(), degree.end(), [&](int aNum) {
        if (aNum == 0) {
            qi.push(aNum);
        }
    });

    while (!qi.empty()) {
        int curId = qi.front();
        ret.push_back(curId);
        qi.pop();
        for (auto& i : graph[curId]) {
            --degree[i];
            if (degree[i] == 0) {
                qi.push(i);
            }
        }
    }

    return ret;
}

vector<vector<int>> bfs(TreeNode* root) {
    vector<vector<int>> ret;
    queue<TreeNode*> tque;

    if (root) {
        tque.push(root);
    }

    while (!tque.empty()) {
        vector<int> temp;
        int size = tque.size();
        for (size_t i = 0; i < size; i++) {
            auto node = tque.front();
            tque.pop();
            temp.push_back(node->val);
            if (node->left) {
                tque.push(node->left);
            }

            if (node->right) {
                tque.push(node->right);
            }
        }
        ret.push_back(move(temp));
    }
    return ret;
}

vector<int> dijstra(int num, const vector<vector<int>>& vcts, int src) {
    vector<vector<pair<int, int>>> graph(num);
    for (auto& vct : vcts) {
        graph[vct[0]].push_back({ vct[1], vct[2] });
    }
    using Pair = pair<int, int>;
    priority_queue<Pair, vector<Pair>, std::function<bool(const Pair& p1, const Pair& p2)>> pq([](const Pair& p1, const Pair& p2) {
        return p1.second > p2.second;
    });

    vector<int> dis(num, INT_MAX);
    dis[src] = 0;
    pq.emplace(src, 0);
    while (!pq.empty()) {
        auto cur = pq.top();
        pq.pop();
        int curId = cur.first;
        int curDis = cur.second;
        for (auto& next : graph[curId]) {
            int nextId = next.first;
            int nextDis = next.second;
            int wDis = curDis + nextDis;
            if (wDis < dis[nextId]) {
                dis[nextId] = wDis;
                pq.emplace(nextId, wDis);
            }
        }
    }
    return dis;
}

void dfs(TreeNode* node, vector<int>& ans) {
    if (!node) {
        return;
    }
    dfs(node->left, ans);
    ans.push_back(node->val);
    dfs(node->right, ans);
}

vector<int> dfs(TreeNode* root) {
    vector<int> ret;
    stack<TreeNode*> nodeStack;
    while (root || !nodeStack.empty()) {
        while (root) {
            nodeStack.push(root);
            root = root->left;
        }
        root = nodeStack.top();
        nodeStack.pop();
        ret.push_back(root->val);
        root = root->right;
    }
    return ret;
}

vector<int> dijstra2(int num, const vector<vector<int>>& vcts, int src) {
    vector<vector<int>> graph(num, vector<int>(num, INT_MAX / 2));
    for (int i = 0; i < num; i++) {
        graph[i][i] = 0;
    }

    for (auto e : vcts) {
        graph[e[0]][e[1]] = e[2];
    }

    vector<bool> visited(num, false);
    visited[src] = true;
    for (int i = 0; i < num; ++i) {
        //进行一次表示，从K到j，经过一个点能不能缩短路径。一共进行N-1就可以。
        int min_id = 0, min_dis = INT_MAX / 2;//每次在unused的点中找到K最近的那个
        for (int j = 0; j < num; ++j) {
            if (visited[j] == false && graph[src][j] < min_dis) {
                min_dis = graph[src][j];
                min_id = j;
            }
        }

        visited[min_id] = true;//把这个点标记为“使用过了”
        for (int j = 0; j < num; j++) {
            if (min_dis + graph[min_id][j] < graph[src][j]) {
                graph[src][j] = min_dis + graph[min_id][j];
            }
        }
    }

    return graph[src];
}

vector<pair<int, int>> prim(int num, const vector<vector<int>>& vcts, int src) {
    // 合并集思路， 两个集合， 取每个点距离集合的最小顶点， 更新距离
    //1.构建图
    vector<vector<int>> graph(num, vector<int>(num, INT_MAX));
    for (auto& vct : vcts) {
        graph[vct[0]][vct[1]] = vct[2];
        graph[vct[1]][vct[0]] = vct[2];
    }

    for (size_t i = 0; i < num; ++i) {
        graph[i][i] = 0;
    }

    //2.判断是否经过 节点
    vector<int> visisted(num, false);
    visisted[src] = true;

    //3.构建距离集
    vector<pair<int, int>> closestDis;
    for (size_t i = 0; i < num; ++i) {
        closestDis.emplace_back(graph[src][i], src);
    }

    //4.逐个将顶点加入到集合中
    vector<pair<int, int>> ret;
    for (size_t i = 1; i < num; ++i) {
        //5.寻找最小节点
        int minId = 0, minDis = INT_MAX;
        for (size_t j = 0; j < num; ++j) {
            if (!visisted[j] && closestDis[j].first < minDis) {
                minId = j;
                minDis = closestDis[j].first;
            }
        }

        ret.emplace_back(closestDis[minId].second, minId);
        visisted[minId] = true;
        //6.更新最近距离与节点
        for (size_t k = 0; k < num; ++k) {
            if (!visisted[k] && graph[minId][k] < closestDis[k].first) {
                closestDis[k].first = graph[minId][k];
                closestDis[k].second = minId;
            }
        }
    }

    return ret;
}

vector<pair<int, int>> kruskal(int num, const vector<vector<int>>& vcts) {
    vector<pair<int, int>> ret;
    using Edge = tuple<int, int, int>; //start, end,
    vector<Edge> edges;
    for (auto& vct : vcts) {
        edges.emplace_back(vct[0], vct[1], vct[2]);
    }
    sort(edges.begin(), edges.end(), [](const Edge& e1, const Edge& e2)->bool {
        return get<2>(e1) < get<2>(e2);
    });

    DisjSet ds(num);
    int cnt = 1;
    for (auto& edge : edges) {
        int x = get<0>(edge);
        int y = get<1>(edge);
        if (ds.unionSet(x, y)) {
            ret.emplace_back(x, y);
            ++cnt;
            if (cnt == num) {
                break;
            }
        }
    }

    return ret;
}