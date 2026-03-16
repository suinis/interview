
#include <bits/stdc++.h>
using namespace std;

static int n, e;

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    cin >> n;

    queue<int> A{};
    vector<int> B(n+ 1, 0);

    for(int i = 0; i < n; ++i) {
        cin >> e;
        A.push(e);
    }
    for(int i = 1; i <= n; ++i) {
        cin >> e;
        B[i] = e;
    }
    
    
}

/* 
2
1 2
2 3

14
*/

// 1 1 | 2 2
// 1 2 | 1 2