#include "dynamic.h"

int rob(vector<int>& nums) {
    int length = nums.size();
    int pre = 0, middle = 0, next = 0;
    if (length == 1) {
        return nums[0];
    }

    if (length == 2) {
        return max(nums[0], nums[1]);
    }

    if (length == 3) {
        return max(nums[1], nums[0] + nums[2]);
    }

    pre = nums[0];
    middle = max(nums[0], nums[1]);
    next = max(nums[1], nums[0] + nums[2]);
    int ret;

    int left, right;
    for (int i = 3; i < length; i++) {
        right = nums[i] + middle;
        left = nums[i - 1] + pre;
        ret = right > left ? right : left;
        pre = middle;
        middle = next;
        next = ret;
    }

    return next;
}

int dynamicBag(vector<std::pair<int, float>>& vct, int bagSize) {
    vector<int> dp(bagSize + 1, 0);
    for (int i = 0; i < vct.size(); i++) {
        for (int j = bagSize; j > 0; j--) {
            if (vct[i].second <= j) {
                if (dp[j] < vct[i].first + dp[int(j - vct[i].second)]) {
                    dp[j] = vct[i].first + dp[int(j - vct[i].second)];
                }
            }
        }
    }

    return dp[bagSize];
}