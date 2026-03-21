#include <bits/stdc++.h>
using namespace std;

// 树上从 u 到 v 的唯一简单路径（顺序为 u -> ... -> v）
bool path_uv(int u, int v, int parent, const vector<vector<int>>& adj, vector<int>& path) {
    path.push_back(u);
    if (u == v) return true;
    for (int w : adj[u]) {
        if (w == parent) continue;
        if (path_uv(w, v, u, adj, path)) return true;
    }
    path.pop_back();
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<int> num(n + 1, 0);
    for (int i = 1; i <= n; ++i) cin >> num[i];

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int from, to;
        cin >> from >> to;
        adj[from].push_back(to);
        adj[to].push_back(from);
    }

    for (int i = 0; i < m; ++i) {
        int choose, from, to;
        cin >> choose >> from >> to;
        vector<int> path;
        path_uv(from, to, -1, adj, path);
        if (choose == 1) {
            for (int x : path) num[x] ^= 1;
        } else {
            int val = 0;
            for (int x : path) val = (val << 1) | num[x];
            cout << val << '\n';
        }
    }
}

/*
第一行：n,m 分别代表n个节点，m次询问
第二行：代表n个节点初始值：0/1
后续n-1行：表示对应节点之间的边
最后m行：第一个数字1/2代表操作类别
（1：后面两节点之间的所有节点包括自身，初始值取反 0->1,1->0）
（2: 计算后面两节点路径组成的十进制值）
输入：
5 5
0 0 0 0 0
1 2
1 3
2 4
2 5
2 1 4
1 1 3
2 4 1
1 2 5
2 5 1

输出：
0
1
7

操作解释：
初始 0 0 0 0 0
2 1 4：计算节点1->4对应十进制值: 000 = 0
1 1 3：1->3之间只经过1,3节点，故初始值变化为 1 0 1 0 0
2 4 1：计算节点4->1对应十进制值：（路径：4->2->1）001 = 1
1 2 5：2->5之间只经过2,5节点，故初始值变化为 1 1 1 0 1
2 5 1：计算节点5->1对应十进制值：（路径：5->2->1）111 = 7
*/
