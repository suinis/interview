#include <bits/stdc++.h>
#define endl "\n"
using namespace std;

const int presize = 4;
const int maxsize = 48;

int mstoi(const string& str) {
    int n = str.size();
    int ans = 0;
    for(int i = 0; i < n; ++i) {
        char num = str[i];
        // cout << num << " ";
        ans *= 10;
        ans += (num - '0');
    }
    return ans;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    unordered_set<string> hashset{};
    unordered_map<char, string> hashmap{
        {'0', "0000"},
        {'1', "0001"},
        {'2', "0010"},
        {'3', "0011"},
        {'4', "0100"},
        {'5', "0101"},
        {'6', "0110"},
        {'7', "0111"},
        {'8', "1000"},
        {'9', "1001"},
        {'a', "1010"},
        {'b', "1011"},
        {'c', "1100"},
        {'d', "1101"},
        {'e', "1110"},
        {'f', "1111"}
    };
    string s{};
    int M, m;

    cin >> M;
    cin.ignore();
    for(int i = 0; i < M; ++i) {
        getline(cin, s);
        int index = s.find('/');
        string str = s.substr(0, index);
        // cout << str << endl;
        // cout << s.substr(index + 1, s.size()) << endl;
        int count = mstoi(s.substr(index + 1, s.size()));
        // cout << count << endl;
        int cutcnt = 0;
        string cutcombine{};
        
        for(int stri = 0; stri < str.size(); ++stri) {
            bool istarget = (str[stri] >= '0' && str[stri] <= '9') || (str[stri] >= 'a' && str[stri] <= 'f');
            if((cutcnt < count / presize) && istarget) {
                cutcombine += hashmap[str[stri]];
                ++cutcnt;
            } else if(!istarget) {
                continue;
            } else {
                if(count % presize != 0) {
                    cutcombine += hashmap[str[stri]].substr(0, count % presize);
                }
                break;;
            }
        }
        // cout << "M:" << cutcombine << endl;
        hashset.insert(cutcombine);
        // find ""空, return yes
    }

    cin >> m;
    cin.ignore();
    for(int i = 0; i < m; ++i) {
        getline(cin, s);
        
        string cutcombine{};
        for(int stri = 0; stri < s.size(); ++stri) {
            bool istarget = (s[stri] >= '0' && s[stri] <= '9') || (s[stri] >= 'a' && s[stri] <= 'f');
            if(istarget) {
                cutcombine += hashmap[s[stri]];
            } 
        }
        // cout << "m:" << cutcombine << endl;
        
        // if(hashset.find("") != hashset.end()) {
        //     cout << "YES" << endl;
        //     continue;
        // }

        bool isfind = false;
        for(int i = 0; i <= maxsize; ++i) {
            string cutstr = cutcombine.substr(0, i);
            // cout << cutstr << endl;
            if(hashset.find(cutstr) != hashset.end()) {
                isfind = true;
                cout << "YES" << endl;
                break;
            }
        }
        if(!isfind) cout << "NO" << endl;
    }
    
}

// 2
// 00-d8-61-ef-31-3e/48 
// 00-e0-fc-00-ed-50/40
// 2
// 00-e0-fc-00-ed-66
// 00-d8-61-ef-31-3f
