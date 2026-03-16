#include <bits/stdc++.h>
using namespace std;

bool isok(vector<int>& house, int left, int right, bool lr) {
    int cnt = 0;
    for(int i = left; i <= right; ++i) {
        if(house[i] == 0) ++cnt;
    }
    if(lr) return (cnt >= (right - left) / 2);
    else return ((right - left + 1 - cnt) >= (right - left + 1) / 2);
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vector<int> house(n, 0);
        for(int i = 0; i < n; ++i) {
            cin >> house[i];
        }

        for(int i = 0; i < n; ++i) {
            if( isok(house, 0, i, 0) && isok(house, i + 1, n - 1, 1)) {
                cout << i + 1 << "\n";
                break;
            }
        }
    }
    // cout << "2\n3\n2\n3\n0\n1\n0\n";
    
}

/* 
2
3
101
7
1001011

10
*/