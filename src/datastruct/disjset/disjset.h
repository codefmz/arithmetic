#ifndef _DISJSET_TEST_
#define _DISJSET_TEST_

#include <vector>
#include <iostream>
using namespace std;

// 不相交集类
class DisjSet {
public:
    explicit DisjSet(int numOfElement) :s(numOfElement, -1) {};
    int find(int x) {
        if (s[x] < 0) {
            return x;
        }
        // = 路径压缩，将每个节点都变为根节点的子节点，便于查找
        return s[x] = find(s[x]);
    }

    int find(int x) const {
        if (s[x] < 0) {
            return x;
        }
        return find(s[x]);
    }

    bool unionSet(int root1, int root2) {
        int x = find(root1);
        int y = find(root2);
        if (x == y) {
            return false;
        }

        // s[x] 小说明节点更多，应该以x作为根节点
        if (s[x] < s[y]) {
            s[y] = x;
        } else {
            if (s[x] == s[y]) {
                --s[y];
            }
            s[x] = y;
        }
        return true;
    }

    void printset() {
        for (int i = 0; i < s.size(); ++i) {
            cout << "s[" << i << "] = " << s[i] << " ";
        }
    }
private:
    vector<int> s;
};

#endif