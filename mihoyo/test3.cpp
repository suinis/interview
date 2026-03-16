#include <bits/stdc++.h>
using namespace std;

static vector<int> father;
static vector<vector<int>> dp;

void join(int s, int t) {
    father[t] = s;
}

int findfather(int i, int j) { // 第一次传入时，i > j
    if(i == j) return i;
    if(i > j) return findfather(father[i], j);
    return findfather(i, father[j]);
}

int pathcount(int point, int root) {
    if(point == root) return 0;
    return pathcount(father[point], root) + 1;
}

int main() {
    int n, m, s, t, u;
    cin >> n >> m;

    father = vector<int>(n + 1, 0);
    father[1] = 1;

    for(int i = 0; i < n - 1; ++i) {
        cin >> s >> t;
        // 是否需要对s,t排个序，默认t > s，s是t的父节点
        if(s > t) join(t, s);
        else join(s, t);
    }

    dp = vector<vector<int>>(n + 1, vector<int>(n + 1, 0));
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j < i; ++j) {
            int father = findfather(i, j);
            dp[i][j] = pathcount(i, father) + pathcount(j, father);
            dp[j][i] = dp[i][j];
        }
    }

    while(m--) {
        cin >> u;
        int cnt = 0;
        for(int i = u; i <= n; ++i) {
            for(int j = i + 1; j <= n; ++j) {
                cnt += dp[i][j];
            }
        }
        cout << cnt << "\n";
    }
}

/* 
5 3
1 2
1 3
3 4
3 5
1
3
5

18
4
0
*/