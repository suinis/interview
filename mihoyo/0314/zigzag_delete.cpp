/**
 * 最少删除几个元素，使剩余数组满足：
 * 相邻不等，且每个中间位置都是 小大小 或 大小大（锯齿形）。
 * 等价于：求最长「锯齿」子序列长度，答案 = n - 该长度。
 *
 * 状态：dp[i][0]=以 i 结尾且 a[i] 为峰(↑)，dp[i][1]=以 i 结尾且 a[i] 为谷(↓)。
 * 转移：峰只能从谷接（a[j]<a[i] 用 dp[j][1]），谷只能从峰接（a[j]>a[i] 用 dp[j][0]）。
 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    // dp[i][0] = 以 i 结尾、最后一步是「上升」(a[i] > 前一个) 的最长长度
    // dp[i][1] = 以 i 结尾、最后一步是「下降」(a[i] < 前一个) 的最长长度
    vector<array<int, 2>> dp(n);
    for (int i = 0; i < n; i++) dp[i][0] = dp[i][1] = 1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (a[j] == a[i]) continue;  // 相邻不能相等
            if (a[j] < a[i]) {
                dp[i][0] = max(dp[i][0], dp[j][1] + 1);  // j 结尾是下降，接上 i 变成上升
            } else {
                dp[i][1] = max(dp[i][1], dp[j][0] + 1);  // j 结尾是上升，接上 i 变成下降
            }
        }
    }

    int maxLen = 0;
    for (int i = 0; i < n; i++) {
        maxLen = max(maxLen, max(dp[i][0], dp[i][1]));
    }
    cout << n - maxLen << "\n";
    return 0;
}
