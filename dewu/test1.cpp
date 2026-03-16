#include <bits/stdc++.h>
using namespace std;

static int m, n;

bool issu(int num) {
    if(num == 0 || num == 1) return false;
    for(int i = 2; i <= (num >> 1); ++i) {
        if(num % i == 0) return false;
    }
    return true;
}

bool isfind(int i) {
    int mod = 10;
    while(i >= mod) {
        int left = i / mod;
        int right = i % mod;
        // cout << left << " " << right << "\n"; 
        if(issu(left) && issu(right)) return true;
        mod *= 10;
    }
    return false;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    cin >> m >> n;

    int ans = 0;
    for(int i = m; i <= n; ++i) {
        if(issu(i) && isfind(i)) {
            cout << i << "\n";
            ++ans;
        }
    }
    cout << ans << "\n";
}

/* 
10 100

4
*/