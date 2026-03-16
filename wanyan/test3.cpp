#include <bits/stdc++.h>
using namespace std;

static const int MOD = 1000000007;
typedef long long ll;

int compute(int n, int m , int k, int i) {
    ll nchoose = 1;
    ll mchoose = 1;
    ll nmulcnt = ll(3) + i;
    ll mmulcnt = ll(2) + (k - 5 - i);
    for(ll j = 0; j < nmulcnt; ++j) {
        nchoose *= (n - j);
        nchoose %= MOD;
    }
    for(ll j = 0; j < nmulcnt; ++j) {
        nchoose /= (j + 1);
        nchoose %= MOD;
    }
    for(ll j = 0; j < mmulcnt; ++j) {
        mchoose *= (m - j);
        mchoose %= MOD;
    }
    for(ll j = 0; j < mmulcnt; ++j) {
        mchoose /= (j + 1);
        mchoose %= MOD;
    }
    ll ret = (nchoose % MOD) * (mchoose % MOD);
    return ret;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int n, m, k;
    cin >> n >> m >> k;
    ll sum = 0;
    for(int i = k - 3 - m; i <= k - 5 && i <= n - 3; ++i) {
        sum += compute(n, m, k, i);
    }
    cout << sum << "\n";
}

/* 
5 2 6

5
*/