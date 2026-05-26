#ifndef _MERGE_H_
#define _MERGE_H_

#include <vector>
#include <map>

using namespace std;

//分治算法
//(1).二维平面寻找最相近的节点, 存在
float findClosestDis(vector<pair<int, int>>& points);
float divideMerge(vector<pair<int, int>>& points, int left, int right);

#endif