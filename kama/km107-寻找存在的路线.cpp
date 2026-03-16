#include <bits/stdc++.h>
using namespace std;

static int n, m;

namespace method1 {
    vector<list<int>> vl(n + 1);
    vector<bool> v(n + 1, false);
    int s, t;

    void dfs(int s) {
        list<int> l = vl[s];
        for(int p : l) {
            if(v[p]) continue;
            v[p] = true;
            dfs(p);
        }
    }

    void test() {
        for(int i = 0; i < m; ++i) {
            cin >> s >> t;
            vl[s].push_back(t);
            vl[t].push_back(s);
        }
        cin >> s >> t;

        dfs(s);
        cout << v[t] << "\n";
    }
}

namespace method2 {
    int s, t;
    vector<int> ancestor(n + 1);
    void init() {
        for(int i = 0; i < n + 1; ++i) {
            ancestor[i] = i;
        }
    }

    int findAncestor(int point) {
        if(ancestor[point] == point) return point;
        ancestor[point] = findAncestor(ancestor[point]);
        return ancestor[point];
    }

    bool isInSameSet(int a, int b) {
        int aa = findAncestor(a);
        int ab = findAncestor(b);
        return aa == ab;
    }

    void join(int s, int t) {
        int as = findAncestor(s);
        int at = findAncestor(t);
        if(as == at) return;
        ancestor[as] = at;
    }

    void test() {
        init();
        for(int i = 0; i < m; ++i) {
            cin >> s >> t;
            join(s, t);
        }
        cin >> s >> t;
        cout << isInSameSet(s, t) << "\n";
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    cin >> n >> m;
    

    // 1. dfs
    // method1::test();
    
    // 2. 并查集
    method2::test();

}

/* 
5 4
1 2
1 3
2 4
3 4
1 4

1
*/