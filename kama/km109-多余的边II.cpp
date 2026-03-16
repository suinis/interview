#include <bits/stdc++.h>
using namespace std;

static int n;
vector<int> father;

void init() {
    for(int i = 0; i < n; ++i) {
        father[i] = i;
    }
}

int find(int point) {   
    if(father[point] == point) return point;
    father[point] = find(father[point]);
    return father[point];
}

void join(int s, int t) {
    int sr = find(s);
    int tr = find(t);
    if(sr == tr) return;
    father[tr] = sr;
}

bool isinsameset(int a, int b) {
    int ar = find(a);
    int br = find(b);
    return ar == br;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    cin >> n;
    father = vector<int>(n + 1, 0);
    init();

    int s, t;
    int rets, rett;
    for(int i = 0; i< n; ++i) {
        cin >> s >> t;
        if(isinsameset(s, t)) {
            rets = s;
            rett = t;
        }else {
            join(s, t);
        }
    }
    cout << rets << " " << rett << "\n";
}

/* 
4
2 1
3 1
4 2
1 4

2 1
 */