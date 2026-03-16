#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    string s;
    getline(cin, s);
    
    int cnt = 0;
    for(int i = 0; i < s.size(); ++i) {
        if((s[i] >= '0' && s[i] <= '9') || (s[i] >= 'a' && s[i] <= 'z')) {
            s[cnt++] = s[i];
        } else if((s[i] >= 'A' && s[i] <= 'Z')) {
            s[cnt++] = tolower(s[i]);
        }
    }
    s.resize(cnt);
    // cout << s << "\n";
    int n = s.size();
    for(int i = 0; i <= (n >> 1); ++i) {
        if(s[i] != s[n - 1 - i]) {
            cout << "false" << "\n";
            return 0;
        }
    }
    cout << "true" << "\n";
}
// 64 位输出请用 printf("%lld")


/* 
A man, a plan, a canal: Panama


*/