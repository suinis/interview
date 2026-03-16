#include <bits/stdc++.h>
using namespace std;

static string b, e;
static unordered_set<string> hs;
static unordered_map<string, int> hm; // 记录对应节点走过路径数
static queue<string> qs;
static int n;

int main() {
    cin >> n;
    cin >> b >> e;

    if(b.size() != e.size()) {
        cout << 0 << "\n";
        return 0;
    }

    for(int i = 0; i < n; ++i) {
        string cinstr;
        cin >> cinstr;
        hs.insert(cinstr);
    }
    hs.insert(b);
    hs.insert(e);

    qs.push(b);
    hm[b] = 1; 
    while(!qs.empty()) {
        string cut = qs.front(); qs.pop();

        // 遍历所有可能相邻str
        for(int i = 0; i < cut.size(); ++i) {
            string cuti = cut;
            for(int k = 0; k < 26; ++k) {
                cuti[i] = 'a' + k;
                // cout << cuti << "\n";
                if(cuti[i] != cut[i] && hs.count(cuti) > 0 && hm.find(cuti) == hm.end()) {
                    qs.push(cuti);
                    hm[cuti] = hm[cut] + 1;
                }
            }
        }
    }

    cout << hm[e] << "\n";
}

/* 
6
abc def
efc
dbc
ebc
dec
dfc
yhn

4
*/