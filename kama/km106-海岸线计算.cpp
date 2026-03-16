#include <bits/stdc++.h>
using namespace std;

static int n, m;
static int d[4][2] = {0, 1, 1, 0, 0, -1, -1, 0};
vector<vector<int>> l;

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    cin >> n >> m;

    l = vector<vector<int>>(n, vector<int>(m, 0));

    for(int i = 0; i < n; ++i) {
        for(int j = 0;  j< m; ++j) {
            cin >> l[i][j];
        }
    }
    
    int aroundc = 0;

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            if(l[i][j] == 1) {
                int cutc = 0;
                for(int k = 0; k < 4; ++k) {
                    int aroundx = i + d[k][0];
                    int aroundy = j + d[k][1];
                    if(aroundx < 0 || aroundx >= n || aroundy < 0 || aroundy >= m || l[aroundx][aroundy] == 0) ++cutc; 
                }
                aroundc += cutc;
            }
        }
    }

    cout << aroundc << "\n";
}

/* 
5 5
0 0 0 0 0 
0 1 0 1 0
0 1 1 1 0
0 1 1 1 0
0 0 0 0 0

14
*/

/* 
2 2
0 0
1 1

6
*/