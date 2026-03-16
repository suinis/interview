#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    string s;
    cin >> s;
    int n = stoi(s.substr(s.find('=') + 1));
    cin >> s;
    s = s.substr(s.find('=') + 1);

    int cnt = 0;
    for(int i = 0; i < s.size(); ++i) {
        if(s[i] != '[' && s[i] != ']') {
            s[cnt++] = s[i];
        }
    }
    s.resize(cnt);
    // cout << n << "\n" << s << "\n";

    stringstream ss(s);
    string point;
    cnt = 0;
    int sou, tar;

    unordered_map<int, vector<int>> hashmap;
    while(getline(ss, point, ',')) {
        if(cnt % 2 == 0) {
            tar = stoi(point);
        }
        else {
            sou = stoi(point);
            hashmap[sou].push_back(tar);
        }
        ++cnt;
    }

    queue<int> que;
    vector<bool> v(n, false);
    vector<int> path;
    que.push(0);
    v[0] = true;
    path.push_back(0);
    while(!que.empty()) {
        int cur = que.front();
        que.pop();
        auto vec = hashmap[cur];
        for(int num : vec) {
            if(!v[num]) {
                path.push_back(num);
                v[num] = true;
                que.push(num);
            }
        }
    }

    for(int i = 0; i < n; ++i) {
        if(v[i] == false) {
            cout << "[]" << "\n";
            return 0;
        }
    }

    cout << "[";
    for(int i = 0; i < path.size() - 1; ++i) {
        cout << path[i] << ",";
    }
    cout << path[path.size() - 1] << "]\n";
}
// 64 位输出请用 printf("%lld")

/* 
num=4 process=[[1,0],[2,0],[3,1],[3,2]]
[0,2,1,3]

num=1 process=[]
[0]

num=5 process=[[2,1],[3,2],[4,0]]
[]
*/