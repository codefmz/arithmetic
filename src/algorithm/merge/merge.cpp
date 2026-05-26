#include <algorithm>
#include "merge.h"

float findClosestDis(vector<pair<int, int>>& points) {
    std::sort(points.begin(), points.end(), [](const pair<int, int>& p1, const pair<int, int>& p2) {
        return p1.first < p2.first;
    });
    int size = points.size();
    return divideMerge(points, 0, size - 1);
}

float divideMerge(vector<pair<int, int>>& points, int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        float lmin = divideMerge(points, left, mid - 1);
        float rmin = divideMerge(points, mid + 1, right);
        float minDis = min(lmin, rmin);

        //计算x坐标值在 mid +- minDis 的索引范围
        int beginIndex = -1, endIndex = -1;
        int size = points.size();
        for (size_t i = left; i <= right; ++i) {
            if (points[i].first >= points[mid].first - minDis && beginIndex == -1) {
                beginIndex = i;
            } else if (points[i].first <= points[mid].first + minDis) {
                endIndex = i;
            }
        }

        //计算左右两点间最小距离
        for (size_t i = beginIndex; i < endIndex; ++i) {
            for (size_t j = i + 1; j <= endIndex; ++j) {
                if (abs(points[i].second - points[j].second) >= minDis) {
                    continue;
                }
                float tDis = sqrt(pow(abs(points[i].first - points[j].first), 2) +
                    pow(abs(points[i].second - points[j].second), 2));
                if (tDis < minDis) {
                    minDis = tDis;
                }
            }
        }
        return minDis;
    }

    return INT_MAX / 2;
}

