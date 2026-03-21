#include <bits/stdc++.h>
#include <unordered_set>
using namespace std;

int main() {
    int T, n;
    cin >> T;
    while(T--) {
        cin >> n;
        // vector<int> in(n);
        unordered_set<int> unset;
        for(int i = 0; i < n; ++i) {
            int num;
            cin >> num;
            unset.insert(num);
        }
        cout << unset.size() << endl;
    }
}
// 64 位输出请用 printf("%lld")

/* 
2
4
1 1 2 3
5
4 5 3 3 4

3
3
*/