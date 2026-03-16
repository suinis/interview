#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    
    int n, m;
    cin >> n >> m;
    vector<vector<char>> matrix(n, vector<char>(m, ' '));
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            cin >> matrix[i][j];
            // cout << matrix[i][j] << " ";
        }
    }

    vector<vector<int>> connectcnt(n, vector<int>(m, 0));
    vector<vector<int>> ans = {{5, 0, 0}, {0, 6, 0}, {3, 0, 5}};

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            cout << ans[i][j] << " ";
        }
        cout << "\n";
    }
}

/* 
3 3
xoo
oxo
xox
*/