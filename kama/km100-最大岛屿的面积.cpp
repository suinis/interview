#include <bits/stdc++.h>
using namespace std;

static int n, m;
static vector<vector<int>> l;
static vector<vector<bool>> v;
static const int d[4][2] = {0, 1, 0, -1, 1, 0, -1, 0};

void dfs(int x, int y, int& cnt) {
    for(int i = 0; i < 4; ++i) {
        int cutx = x + d[i][0];
        int cuty = y + d[i][1];
        if(cutx < 0 || cutx >= n || cuty < 0 || cuty >= m || v[cutx][cuty]) continue;
        if(l[cutx][cuty] == 0) {
            v[cutx][cuty] = true;
            continue;
        }
        v[cutx][cuty] = true;
        // cout << cutx << ", " << cuty << "\n";
        ++cnt;
        dfs(cutx, cuty, cnt);
    }
}

int bfs(int x, int y) {
    queue<pair<int, int>> q;
    int cnt = 1;
    q.emplace(x, y);
    v[x][y] = true;

    while(!q.empty()) {
        pair<int, int> p = q.front(); q.pop();
        for(int i = 0; i < 4; ++i) {
            int cutx = p.first + d[i][0]; // 注意是p.first不是x，写错几次了！
            int cuty = p.second + d[i][1];
            if(cutx < 0 || cutx >= n || cuty < 0 || cuty >= m || v[cutx][cuty]) continue;
            if(l[cutx][cuty] == 0) {
                v[cutx][cuty] = true;
                continue;
            }
            q.emplace(cutx, cuty);
            v[cutx][cuty] = true;
            ++cnt;
        }
    }
    return cnt;
}

int main() {
    int ans = 0;
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cin >> n >> m;

    l = vector<vector<int>>(n, vector<int>(m, 0));
    v = vector<vector<bool>>(n, vector<bool>(m, false));

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            cin >> l[i][j];
        }
    }

    for(int i = 0; i < n; ++i) {
        for(int j  = 0; j < m; ++j) {
            if(v[i][j] || l[i][j] == 0) continue;
            // // dfs
            // int cnt = 1;
            // v[i][j] = true;
            // dfs(i, j, cnt);
            // cout << cnt << "\n";

            // bfs
            int cnt = bfs(i, j);
            ans = max(ans, cnt);
        }
    }

    cout << ans << "\n";
}

/* 
4 5
1 1 0 0 0
1 1 0 0 0
0 0 1 0 0
0 0 0 1 1
*/