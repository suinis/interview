#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    int n, k;
    cin >> n >> k;

    vector<int> input(n, 0);
    for(int i = 0; i < n; ++i) {
        cin >> input[i];
        // cout << input[i] << " ";
    }
    
    vector<int> ans{};
    unordered_map<int, string> indexstrmap{};
    unordered_map<string, int> strcntmap{};

    for(int i = 0; i < n; i += k) {
        string cutcombine{};
        for(int j = i; j < i + k && j < n; ++j) {
            cutcombine.push_back(input[j] + '0');
        }
        if(strcntmap.find(cutcombine) == strcntmap.end()) {
            indexstrmap[i / k] = cutcombine;
            // cout << i / k << ":" << cutcombine << endl;
        }
        ++strcntmap[cutcombine];
    }
    for(int i = 0; i <= n / k; ++i) {
        if(indexstrmap.find(i) != indexstrmap.end()) {
            string str = indexstrmap[i];
            // cout << str << endl;
            int strn = str.size();
            for(int stri = 0; stri < strn; ++stri) ans.emplace_back(str[stri] - '0');
            ans.emplace_back(strcntmap[str]);
        }
    }

    for(int val : ans) cout << val << " ";
}