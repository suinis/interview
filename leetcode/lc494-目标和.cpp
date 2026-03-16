#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int sum = 0;
        for(int i = 0; i < nums.size(); ++i) {
            sum += nums[i];
        }
        if(abs(target) > sum) return 0; // 防止越界

        int colsize = sum * 2 + 1;
        vector<vector<int>> dp(nums.size(), vector<int>(colsize, 0));
        ++dp[0][sum - nums[0]]; // nums[0] = 0时，要加两次，故不可直接设定为1
        ++dp[0][nums[0] + sum];

        for(int i = 1; i < nums.size(); ++i) {
            for(int j = 0; j < colsize; ++j) {
                if(j >= nums[i]) dp[i][j] += dp[i - 1][j - nums[i]];
                if(j + nums[i] < colsize) dp[i][j] += dp[i - 1][j + nums[i]];
            }
        }

        return dp[nums.size() - 1][target + sum];
    }
};

int main() {
    Solution sol;
    vector<int> input = {1,1,1,1,1};
    cout <<  sol.findTargetSumWays(input, 3) << endl;
}