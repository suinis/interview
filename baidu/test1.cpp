#include <bits/stdc++.h>
using namespace std;

unordered_map<int, int> departcnt;

void computeCnt(int maxa, int mina) {
    if(maxa <= mina * 2) {
        departcnt[maxa] = 0;
    }
    for (int i = mina; i <= maxa / 2; ++i) {
        if(departcnt.find(maxa - i) == departcnt.end()) computeCnt(maxa - i, mina);
        if (departcnt.find(maxa) == departcnt.end()) {
            departcnt[maxa] = departcnt[maxa - i] + 1;
        }
        else {
            departcnt[maxa] = min(departcnt[maxa], departcnt[maxa - i] + 1);
        }
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    int n;
    cin >> n;

    vector<int> a(n, 0);
    int mina = INT_MAX, maxa = INT_MIN;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        if (a[i] < mina) mina = a[i];
        if (a[i] > maxa) maxa = a[i];
    }

    int cnt = 0;
    if (maxa > 2 * mina) {
        computeCnt(maxa, mina);
    }
    for (int i = 0 ; i < n; ++i) {
        if (a[i] > mina * 2) {
            if (departcnt.find(a[i]) == departcnt.end()) cout << "can not find" << "\n";
            cnt += departcnt[a[i]];
        }
    }

    for(auto pair: departcnt) {
        cout << pair.first << " : " << pair.second  << "\n";
    }
    cout << cnt << "\n";
}