#include "dynamic.h"

int dynamicBag(vector<std::pair<int, float>>& vct, int bagSize) {
    vector<int> dp(bagSize + 1, 0);
    for (int i = 0; i < vct.size(); i++) {
        for (int j = bagSize; j > 0; j--) { // 这里使用了内存优化， 可以不用2维的数据结构，但必须从后往前遍历，否者新计算的结果会上一层的结果
            if (vct[i].second <= j) {
                if (dp[j] < vct[i].first + dp[int(j - vct[i].second)]) {
                    dp[j] = vct[i].first + dp[int(j - vct[i].second)];
                }
            }
        }
    }

    return dp[bagSize];
}