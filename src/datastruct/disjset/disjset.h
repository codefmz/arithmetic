#ifndef _DISJSET_TEST_
#define _DISJSET_TEST_

#include <vector>
#include <iostream>
using namespace std;

// 不相交集类
class DisjSet {
public:
    explicit DisjSet(int numOfElement);
    int find(int x);
    int find(int x) const;
    bool unionSet(int root1, int root2);
    void printset();
private:
    vector<int> s;
};

#endif
