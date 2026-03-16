#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    int xsum = 0;
    int numsum = 0;

    char x;
    for(int i = 0; i < s.size(); ++i) {
        if((s[i] != '-' && s[i] != '+' && s[i] != '=') && (s[i] < '0' || s[i] > '9')){
            x = s[i];
            break;
        }
    }

    int ei = s.find('=');
    string left = s.substr(0, ei);
    string right = s.substr(ei + 1);
    // cout << left << " " << right << "\n";
    // cout << x << "\n";

    stack<char> st;
    for(int i = 0; i < left.size(); ++i) {
        if(left[i] != x) {
            st.push(left[i]);
            continue;
        }
        if(st.empty()) xsum += 1;
        else {
            int cutnum = 0;
            int mul = 1;
            while(!st.empty()) {
                char c = st.top();
                st.pop();
                if(c == '-') {
                    cutnum *= -1;
                    break;
                }
                if(c == '+') {
                    break;
                }
                else {
                    cutnum += (c - '0') * mul;
                    mul *= 10;
                }
            }
            xsum += cutnum;
        }
    }
    // to do : numst
    while(!st.empty()) {

    }

}