#include <bits/stdc++.h>
using namespace std;

void computeMinPair() {

}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int n, sumx = 0, sumy = 0;
    cin >> n;
    vector<int> x(n, 0);
    vector<int> y(n, 0);

    for(int i = 0; i < n; ++i) {
        cin >> x[i];
        sumx += x[i];
    }

    for(int i = 0; i < n; ++i) {
        cin >> y[i];
        sumy += y[i];
    }

    vector<int> dp(n, 0);
    int avex = sumx / n;
    int avey = sumy / n;
    int ans = 0;
    for(int i = 0; i < n; ++i) {
        int cnt = abs(avex - x[i]) + abs(avey - y[i]);
        ans += (cnt % 2 == 0) ? cnt : cnt + 1;
    }
    cout << ans << endl;
} 

/* 
第一行表示:n个晶体
后面2行n列,分别表示硬度x和结晶度y
对晶体可以有四种操作(
x和y同时+0.5,
x和y同时-0.5,
x+0.5且y-0.5,
x-0.5且y+0.5)
问最少需要多少次操作可以使得所有晶体都一致(a.x == b.x == c.x ... && a.y == b.y == c.y ...)
2
2 4
1 3

2
*/