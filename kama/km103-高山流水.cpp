#include <bits/stdc++.h>
using namespace std;

static int n, m;
static int d[4][2] = {1, 0, 0, 1, -1, 0, 0, -1};
static vector<vector<int>> l;
static vector<vector<int>> v;
static vector<vector<int>> f;

void dfs(int x, int y, int s) {
    for(int i = 0; i < 4; ++i) {
        int nextx = x + d[i][0];
        int nexty = y + d[i][1];
        if(nextx < 0 || nextx >= n || nexty < 0 || nexty >= m || v[nextx][nexty]) continue;
        if(l[nextx][nexty] >= l[x][y]) {
            ++f[nextx][nexty];
            v[nextx][nexty] = true;
            dfs(nextx, nexty, s);
        }
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    cin >> n >> m;

    l = vector<vector<int>>(n, vector<int>(m, 0));
    v = vector<vector<int>>(n, vector<int>(m, 0));
    f = vector<vector<int>>(n, vector<int>(m, 0)); 

    for(int i = 0; i < n; ++i) {
        for(int j = 0;  j< m; ++j) {
            cin >> l[i][j];
        }
    }

    // 左边界
    int leftcnt = 1, rightcnt = 2;
    for(int i = 0; i < n; ++i) {
        if(!v[i][0]) {
            ++f[i][0];
            v[i][0] = true;
            dfs(i, 0, leftcnt);
        }
    }
    for(int j = 1; j < m; ++j) {
        if(!v[0][j]) {
            ++f[0][j];
            v[0][j] = true;
            dfs(0, j, leftcnt);
        }
    }

    // 右边界
    v = vector<vector<int>>(n, vector<int>(m, false));
    for(int i = 0; i < n; ++i) {
        if(!v[i][m - 1]) {
            ++f[i][m - 1];
            v[i][m - 1] = true;
            dfs(i, m - 1, rightcnt);
        }
    }
    for(int j = 0; j < m - 1; ++j) {
        if(!v[n - 1][j]) {
            ++f[n - 1][j];
            v[n - 1][j] = true;
            dfs(n -1, j, rightcnt);
        }
    }

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            if(f[i][j] == 2) cout << i << " " << j << "\n";
        }
    }
}

/* 
5 5
1 3 1 2 4
1 2 1 3 2
2 4 7 2 1
4 5 6 1 1
1 4 1 2 1
*/