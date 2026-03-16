#include <bits/stdc++.h>
using namespace std;

static int n, m;
static vector<vector<char>> matrix;
const vector<vector<int>> d = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
static vector<vector<bool>> v;

void dfs(int x, int y, int& cnt, char id) {
    for(int i = 0; i < 4; ++i) {
        int nextx = x + d[i][0];
        int nexty = y + d[i][1];
        if(nextx < 0 || nextx >= n || nexty < 0 || nexty >= m || v[nextx][nexty]) continue;
        if(matrix[nextx][nexty] == 'x') {
            v[nextx][nexty] = true;
            continue;
        }
        matrix[nextx][nexty] = id;
        ++cnt;
        v[nextx][nexty] = true;
        dfs(nextx, nexty, cnt, id);
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    cin >> n >> m;
    matrix = vector<vector<char>>(n, vector<char>(m, ' '));
    v = vector<vector<bool>>(n, vector<bool>(m, false));

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            cin >> matrix[i][j];
        }
    }

    unordered_map<char, int> hm;
    int id = 1;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            if(matrix[i][j] == 'x' || v[i][j]) continue;
            matrix[i][j] = id + '0';
            v[i][j] = true;
            int cnt = 1;
            dfs(i, j, cnt, id + '0');
            hm.insert(pair<char, int>(id + '0', cnt));
            ++id;
        }
    }

    // for(const auto& pair : hm) {
    //     cout << pair.first << ": " << pair.second << "\n";
    // }

    // for(int i = 0; i < n; ++i) {
    //     for(int j = 0; j < m; ++j) {
    //         cout << matrix[i][j] << " ";
    //     }
    //     cout << "\n";
    // }

    vector<vector<int>> ans(n, vector<int>(m, 0));
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            if(matrix[i][j] == 'o') {
                ans[i][j] = 0;
                continue;
            }
            unordered_set<char> idhs;
            int cutcnt = 1;
            for(int k = 0; k < 4; ++k) {
                int aroundx = i + d[k][0];
                int aroundy = j + d[k][1];
                if(aroundx < 0 || aroundx >= n || aroundy < 0 || aroundy >= m) continue;

                char cutid = matrix[aroundx][aroundy];
                if(idhs.count(cutid) > 0) continue;
                idhs.insert(cutid);
                cutcnt += hm[cutid];
            }
            ans[i][j] = cutcnt;
        }
    }

    int maxarea = 0;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            // cout << ans[i][j] << " ";
            maxarea = max(maxarea, ans[i][j]);
        }
        // cout << "\n";
    }
    cout << maxarea << "\n";
}

/* 
3 3
xoo
oxo
xox

6
*/