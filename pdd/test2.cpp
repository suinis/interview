#include <bits/stdc++.h>
using namespace std;

const char other = 'Z';

void getcnt(string s, int ) {

}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int T;
    cin >> T;
    while(T--) {
        string in;
        int m ;
        cin >> m;
        cin.ignore();
        cin >> in;
        // cout << in << "\n";

        int left = 0, right = 0;
        unordered_map<char, int> hashmap;
        unordered_set<char> hashset = {'D', 'M', 'T', 'A', 'O'};
        vector<int> dp(in.size(), 0);
        for(int i = 0; i < 5 + m; ++i) {
            if(hashset.count(in[i] > 0)) ++hashmap[in[i]];
            else ++hashmap[other];
        }
        for(int i = 5 + m - 1; i < in.size(); ++i) {
            dp[i] = dp[i - 1] + getcnt();
        }
    }
}


/* 
1
3
DAVMTTBLMO

1
*/