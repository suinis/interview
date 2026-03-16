#include <bits/stdc++.h>
using namespace std;

static int n, s, t;

vector<int> ancestor(n + 1);

void init() {
    for(int i = 0; i < n + 1; ++i) {
        ancestor[i] = i;
    }
}

int findAncestor(int point) {
    if(ancestor[point] == point) return point;
    return ancestor[point] = findAncestor(ancestor[point]);
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

int main() {
    //方法原理：判断新加入的边上的两点，是否在同一个集合中
    cin >> n;
    init();
    for(int i = 0; i < n; ++i) {
        cin >> s >> t;
        if(isInSameSet(s, t)) {
            cout << s << " " << t << "\n";
            return 0;
        }
        join(s, t);
    }

}

/* 
5
2 1
2 3
4 5 // 此时构成两颗树2-1-3 | 4-5
3 5 // 本边两点虽都已存在，但加上去并不会导致成环，所以只能用并查集判断是否在同一个集合中（而不可以单纯地判断两点是否都已存在，来决定成环地边）
3 4

5
2 1
2 3
4 5
3 5
3 4
*/