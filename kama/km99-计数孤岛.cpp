#include <bits/stdc++.h>
using namespace std; 

static int n, m;
const int dir[4][2] = {0, 1, 1, 0, -1, 0, 0, -1};
vector<vector<int>> island;
vector<vector<bool>> v;

void dfs(int x, int y) {
    int cutx, cuty;
    for(int i = 0; i < 4; ++i) {
        cutx = x + dir[i][0];
        cuty = y + dir[i][1];
        if(cutx < 0 || cutx >= n || cuty < 0 || cuty >= m || v[cutx][cuty]) continue;
        if(island[cutx][cuty] == 0) {
            v[cutx][cuty] = true;
            continue;
        }
        v[cutx][cuty] = true;
        dfs(cutx, cuty);
    }
}

void bfs(int x, int y) {
    queue<pair<int, int>> q{};
    q.emplace(x, y);
    v[x][y] = true; // bfs要注意，入队列就标记 。如果是出队列再标记会导致重复入队操作，耗时增加

    while(!q.empty()) {
        pair<int, int> cutxy = q.front(); q.pop();
        // cout << cutxy.first << "," << cutxy.second << " :";
        for(int k = 0; k < 4; ++k) {
            int nextx = cutxy.first + dir[k][0];
            int nexty = cutxy.second + dir[k][1];
            if(nextx < 0 || nextx >= n || nexty < 0 || nexty >= m || v[nextx][nexty]) continue;
            if(island[nextx][nexty] == 0) {
                v[nextx][nexty] = true;
                continue;
            }
            // cout << nextx << "," << nexty << " ";
            q.emplace(nextx, nexty);
            v[nextx][nexty] = true;
        }
        // cout << "\n";
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    
    cin >> n >> m;
    island = vector<vector<int>>(n, vector<int>(m, 0));
    v = vector<vector<bool>>(n, vector<bool>(m, false));
    
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            cin >> island[i][j];
        }
    }

    int ans = 0;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            if(v[i][j] || island[i][j] == 0) continue;
            // dfs(i, j);
            bfs(i, j);
            ++ans;
        }
    }

    cout << ans << "\n";
}