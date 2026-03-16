#include <bits/stdc++.h>
using namespace std;

bool cangetout(const vector<char>& in, int startIndex, int dir) { // dir = -1 左
    bool go = true;
    if(dir == -1) {
        while(startIndex > 1) {
            if(in[startIndex - 1] == '.') {
                --startIndex;
                go = true;
                continue;
            }
            if(go) { // '#'
                while(startIndex > 1) {
                    if(in[startIndex - 1] == '#') --startIndex;
                    else {
                        --startIndex;
                        break;
                    }
                }
                go = false;
            } 
            else return false;
        }
        if(startIndex == 1) return true;
    }
    else {
        while(startIndex < in.size() - 1) {
            if(in[startIndex + 1] == '.') {
                ++startIndex;
                go = true;
                continue;
            }
            if(go) { // '#'
                while(startIndex < in.size() - 1) {
                    if(in[startIndex + 1] == '#') ++startIndex;
                    else {
                        ++startIndex;
                        break;
                    }
                }
                go = false;
            } 
            else return false;
        }
        if(startIndex == in.size() - 1) return true;
    }
    return false;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int T;
    cin >> T;
    while(T--) {
        int n;
        cin >> n;
        vector<char> in(n + 1, ' ');
        int dindex = 0;

        for(int i = 1; i <= n; ++i) {
            cin >> in[i];
            if(in[i] == 'D') dindex = i;
        }
        in[dindex] = '.';
        // cout << dindex << "\n";

        bool can = false;
        if(dindex == 1 || dindex == n) can = true;
        else if(in[dindex - 1] == '#' && in[dindex + 1] == '#') can = false;
        else if(in[dindex - 1] == '#' && in[dindex + 1] == '.') {
            can = cangetout(in, dindex + 1, -1) || cangetout(in, dindex, 1);
        }
        else if(in[dindex - 1] == '.' && in[dindex + 1] == '#') {
            can = cangetout(in, dindex, -1) || cangetout(in, dindex - 1, 1);
        }
        else if(in[dindex - 1] == '.' && in[dindex + 1] == '.') {
            can = cangetout(in, dindex, -1) || cangetout(in, dindex, 1);
        }
        cout << (can ? "YES" : "NO") << "\n";
    }
}

/* 
1
10
#.##..D#.#

NO
YES
YES
YES

5
5
##D##
5
..D.#
7
#.#.D##
5
D####
10
#.##..D#.#

2
5
D####
10
#.##..D#.#

*/