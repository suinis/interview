#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> a(n, 0);
    int mina = INT_MAX, maxa = INT_MIN;
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
        if(a[i] < mina) mina = a[i];
        if(a[i] > maxa) maxa = a[i];
    }

    int cnt = 0;
    for(int i = 0; i < n; ++i) {
        if(a[i] > mina * 2) {
            cnt += (a[i] - 1) / (mina * 2);
        }
    }
    cout << cnt << "\n";
}

/* 
3
3 5 13

2
*/