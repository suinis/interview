#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
static int n;
static ll m;

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    cin >> n >> m;

    vector<int> a(n, 0);
    for(int i = 0 ; i < n; ++i) {
        cin >> a[i];
    }

    vector<int> v(1000001, 0);
    ll sum = 0;
    ll cnt = 0;
    vector<int> mut(1000001, 0);
    while(cnt < m) {
        ll cutsum = sum;
        sum += a[cutsum % n];
        
        if(v[a[cutsum % n]] = 1) break;
        v[a[cutsum % n]] = 1;
        mut[cnt] = a[cutsum];
        ++cnt;
    }
    ll peradd = 0;
    for(int i = 0; i < cnt; ++i) {
        peradd += mut[i];
    }
    ll ans = (m / cnt) * peradd;
    for(int i = 0; i < m % cnt; ++i) {
        ans += mut[i];
    }
    cout << ans << "\n";
}

/* 
5 4
1 2 3 4 5

10
*/