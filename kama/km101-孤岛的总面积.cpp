#include <bits/stdc++.h>
using namespace std;

static int n, m;
vector<vector<int>> l;
vector<vector<bool>> v;
static const int d[4][2] = {0, 1, 1, 0, 0, -1, -1, 0};

void dfs(int x, int y) {
    for(int i = 0; i < 4; ++i) {
        int cutx = x + d[i][0];
        int cuty = y + d[i][1];
        if(cutx < 0 || cutx >= n || cuty < 0 || cuty >= m || v[cutx][cuty]) continue;
        if(l[cutx][cuty] == 0) {
            v[cutx][cuty] = true;
            continue;
        }
        v[cutx][cuty] = true;
        dfs(cutx, cuty);
    }
}

void dfs(int x, int y, int& ans) {
    for(int i = 0; i < 4; ++i) {
        int cutx = x + d[i][0];
        int cuty = y + d[i][1];
        if(cutx < 0 || cutx >= n || cuty < 0 || cuty >= m || v[cutx][cuty]) continue;
        if(l[cutx][cuty] == 0) {
            v[cutx][cuty] = true;
            continue;
        }
        v[cutx][cuty] = true;
        ++ans;
        dfs(cutx, cuty, ans);
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    cin >> n >> m;
    l = vector<vector<int>>(n, vector<int>(m, 0));
    v = vector<vector<bool>>(n, vector<bool>(m , false));

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            cin >> l[i][j];
        }
    }

    for(int j = 0; j < m; ++j) {
        if(l[0][j] == 1) {
            v[0][j] = true;
            dfs(0, j);
        }
        if(l[n - 1][j] == 1) {
            v[n - 1][j] = true;
            dfs(n - 1, j);
        }
    }
    for(int i = 0; i < n; ++i){
        if(l[i][0] == 1) {
            v[i][0] = true;
            dfs(i, 0);
        }
        if(l[i][m - 1] == 1) {
            v[i][m - 1] = true;
            dfs(i, m - 1);
        }
    }

    int ans = 0;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            if(v[i][j] || l[i][j] == 0) continue;
            ++ans;
            v[i][j] = true;
            dfs(i, j, ans);
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