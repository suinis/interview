#include <cstddef>
#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    int T, n;
    cin >> T;
    while(T--) {
        cin >> n;
        cin.ignore();
        cin >> s;
        // cout << s << endl;
        int res = 0, cur_rightsum = 0;
        for(int i = 0; i < n; ++i) {
            if(s[i] == ')') ++cur_rightsum;
            else {
                res += cur_rightsum;
                --cur_rightsum;
            }
        }
        cout << res << endl;
    }
}
// 64 位输出请用 printf("%lld")

/* 
1
8
)(()(())
*/