#include <bits/stdc++.h>
using namespace std;

static int n, m;
static int d[4][2] = {0, 1, 0, -1, 1, 0, -1, 0};
static vector<vector<int>> l;
static vector<vector<bool>> v;

void bfs(int x, int y, bool issetzero) {
    queue<pair<int, int>> q;
    q.emplace(x, y);
    v[x][y] = true;
    if(issetzero) l[x][y] = 0;

    while(!q.empty()) {
        pair<int, int> p = q.front(); q.pop();
        int cutx = p.first;
        int cuty = p.second;
        for(int i = 0; i < 4; ++i) {
            int nextx = cutx + d[i][0];
            int nexty = cuty + d[i][1];
            if(nextx < 0 || nextx >= n || nexty < 0 || nexty >= m || v[nextx][nexty]) continue;
            if(l[nextx][nexty] == 0) {
                v[nextx][nexty] = true;
                continue;
            }
            v[nextx][nexty] = true;
            q.emplace(nextx, nexty);
            if(issetzero) l[nextx][nexty] = 0;
        }
    }
}

int main() {
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

    for(int j = 0; j < m; ++j) {
        if(l[0][j] == 1) bfs(0, j, false);
        if(l[n - 1][j] == 1) bfs(n - 1, j, false);
    }

    for(int i = 0; i < n; ++i) {
        if(l[i][0] == 1) bfs(i, 0, false);
        if(l[i][m - 1] == 1) bfs(i, m - 1, false);
    }

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            if(v[i][j] || l[i][j] == 0) continue;
            bfs(i, j, true);
        }
    }

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            cout << l[i][j] << " ";
        }
        cout << "\n";
    }

}

/* 
4 5
1 1 0 0 0
1 1 0 0 0
0 0 1 0 0
0 0 0 1 1
*/