#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    pair<int, int> zeroOneCount(const string& str) {
        int zerocount = 0, onecount = 0;
        for(int i = 0; i < str.size(); ++i) {
            if(str[i] == '0') ++zerocount;
            else ++onecount;
        }
        return {zerocount, onecount};
    }

    // 一维dp（主要是将二维的j,k转为一维） + 滚动数组
    // leetcode上跑空间占用只比二维高一点点，耗时竟然比二维快十几毫秒
    // 但一维是定义了m * 101 + n的空间大小，二维则是m * n（1 <= m, n <= 100），相比之下还是二维更优，时间复杂度都是一致的，毕竟都是三层for
    int findMaxForm_1(vector<string>& strs, int m, int n) {
        vector<int> dp(m * 101 + n + 1, 0);
        pair<int, int> cutconut = zeroOneCount(strs[0]);

        for(int i = 0; i < strs.size(); ++i) {
            // cout << strs[i] << ": ";
            cutconut = zeroOneCount(strs[i]);
            // cout << cutconut.first << " " << cutconut.second << "\n";
            for(int j = m; j >= cutconut.first; --j) {
                for(int k = n; k >= cutconut.second; --k) {
                    int index = j * 101 + k;
                    dp[index] = max(dp[index], dp[index - cutconut.first * 101 - cutconut.second] + 1);
                }
            }
        }
        
        return dp.back();
    }

    // 二维dp + 滚动数组
    int findMaxForm_2(vector<string>& strs, int m, int n) {
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        pair<int, int> cutconut = zeroOneCount(strs[0]);

        // dp[i][j][k] : j个0，k个1，能存储前i + 1个数最多的字符串个数
        for(int i = 0; i < strs.size(); ++i) {
            cutconut = zeroOneCount(strs[i]);
            for(int j = m; j >= cutconut.first; --j) {
                for(int k = n; k >= cutconut.second; --k) {
                    dp[j][k] = max(dp[j][k], dp[j - cutconut.first][k - cutconut.second] + 1);
                }
            }
        }

        return dp.back().back();
    }

    int findMaxForm_3(vector<string>& strs, int m, int n) {
        vector<vector<vector<int>>> dp(strs.size(), vector<vector<int>>(m + 1, vector<int>(n + 1, 0)));
        pair<int, int> cutconut = zeroOneCount(strs[0]);

        for(int j = cutconut.first; j <= m; ++j) {
            for(int k = cutconut.second; k <= n; ++k) {
                dp[0][j][k] = 1;
            }
        }
        for(int i = 1; i < strs.size(); ++i) {
            cutconut = zeroOneCount(strs[i]);
            for(int j = 0; j <= m; ++j) {
                for(int k = 0; k <= n; ++k) {
                    if(j >= cutconut.first && k >= cutconut.second) {
                        dp[i][j][k] = max(
                            dp[i - 1][j][k], 
                            dp[i - 1][j - cutconut.first][k - cutconut.second] + 1);
                    } else {
                        dp[i][j][k] = dp[i - 1][j][k];
                    }
                }
            }
        }

        return dp.back().back().back();
    }
};

int main() {
    const int loop = 100000;
    Solution sol;
    vector<string> input{"10","0","1"};


    // 耗时测试不准确，每次循环都是一样的输入，需要改变输入计算多次
    clock_t t1 = clock();
    for(int i = 0; i < loop; ++i) {
        sol.findMaxForm_1(input, 1, 1);
    }
    clock_t t2 = clock();
    cout << "一维：" << 1000.0 * (t2 - t1) / CLOCKS_PER_SEC << "ms" << endl; // (t2 - t1) / CLOCKS_PER_SEC ，单位是秒

    t1 = clock();
    for(int i = 0; i < loop; ++i) {
        sol.findMaxForm_2(input, 1, 1);
    }
    t2 = clock();
    cout << "二维：" << 1000.0 * (t2 - t1) / CLOCKS_PER_SEC  << "ms"  << endl;
    
    t1 = clock();
    for (int i = 0; i < loop; ++i)
    {
        sol.findMaxForm_3(input, 1, 1);
    }
    t2 = clock();
    cout << "三维：" << 1000.0 * (t2 - t1) / CLOCKS_PER_SEC  << "ms"  << endl;
}