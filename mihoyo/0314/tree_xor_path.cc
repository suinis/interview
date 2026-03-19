/**
 * 无向树，边有权值。求所有点对 (u,v) 之间路径边权异或和 的总和。
 * 思路：根到某点 u 的路径异或记为 xor[u]，则 path_xor(u,v) = xor[u] ^ xor[v]。
 * 答案 = sum_{i<j} (xor[i]^xor[j])，按位统计：每位贡献 = (1<<b) * cnt_b * (n-cnt_b)。
 */
#include <bits/stdc++.h>
#include <functional>
#include <vector>
using namespace std;
using LL = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<vector<pair<int, int>>> g(n + 1);  // 1-indexed: (v, w)
        for (int i = 0; i < n - 1; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            g[u].emplace_back(v, w);
            g[v].emplace_back(u, w);
        }

        vector<LL> xor_from_root(n + 1);
        function<void(int, int, LL)> dfs = [&](int from, int father, LL cur) {
            xor_from_root[from] = cur;  // 根也会被赋成 0
            for (auto [to, weight] : g[from]) {
                if (to == father) continue;
                dfs(to, from, cur ^ weight);
            }
        }; 
        dfs(1, 0, 0);

        // 所有点对 (i,j) 且 i<j：path_xor(i,j) = xor[i]^xor[j]
        LL res = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = i + 1; j <= n; j++) {
                res += xor_from_root[i] ^ xor_from_root[j];
            }
        }
        cout << res << endl;

        // vector<LL> xor_from_root(n + 1);
        // function<void(int, int, LL)> dfs = [&](int u, int fa, LL cur) {
        //     xor_from_root[u] = cur;
        //     for (auto [v, w] : g[u]) {
        //         if (v == fa) continue;
        //         dfs(v, u, cur ^ w);
        //     }
        // };
        // dfs(1, 0, 0);

        // LL ans = 0;
        // for (int b = 0; b <= 31; b++) {
        //     int cnt = 0;
        //     for (int i = 1; i <= n; i++)
        //         if ((xor_from_root[i] >> b) & 1) cnt++;
        //     ans += (1LL << b) * (LL)cnt * (n - cnt);
        // }
        // cout << ans << "\n";
    }
    return 0;
}


/* 
2
2
1 2 1
2 3 1
3
1 2 0
2 3 0
3 4 7
*/