#include <bits/stdc++.h>
using namespace std;

static int n, m;
static vector<bool> v;
static vector<list<int>> vl;

void dfs(int s) {
    list<int> l = vl[s];
    for(int point : l) {
        if(v[point]) continue;
        v[point] = true;
        dfs(point);
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    cin >> n >> m;

    v = vector<bool>(n + 1, false); // 排除0
    vl = vector<list<int>>(n + 1);
    int s, t;

    for(int i = 0; i < m; ++i) {
        cin >> s >> t;
        vl[s].push_back(t);
    }

    v[1] = true;
    dfs(1);

    bool isall = true;
    for(int i = 1; i <= n; ++i) {
        if(!v[i]) {
            isall = false;
            break;
        }
    }
    cout << (isall ? 1 : -1) << "\n";
}

/* 
4 4
1 2
2 1
1 3
2 4

1
*/