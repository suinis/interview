#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    
    int n, m;
    cin >> n >> m;
    auto compfunc = [](const pair<int, int>& a, const pair<int, int>& b){
        return (b.second != a.second) ? b.second > a.second : b.first < a.first;
    };
    map<int, int> numcntmap;
    set<pair<int, int>, decltype(compfunc)> sortedmap(compfunc); 
    unordered_map<int, vector<int>> relationhash{};
    
    for(int i = 0; i < m; ++i) {
        int maleid, femaleid;
        cin >> maleid >> femaleid;
        ++numcntmap[maleid];
        ++numcntmap[femaleid];
        relationhash[maleid].push_back(femaleid);
        relationhash[femaleid].push_back(maleid);
    }

    int anscnt = 0;
    vector<int> ansvec{};
    for(auto it = sortedmap.begin(); it != sortedmap.end(); ++it) {
        

    }
    while(!numcntmap.empty()) {
        
        auto it = numcntmap.begin();
        cout << it->first << ": ";
        auto relavec = relationhash[it->first];
        for(auto id : relavec) cout << id << " ";
        cout << endl;

        for(auto id : relavec) {
            --numcntmap[id];
            if(numcntmap[id] == 0) numcntmap.erase(id);
        }
        ++anscnt;
        ansvec.push_back(it->first);
        numcntmap.erase(it->first);
    }

    cout << anscnt << endl;
    for(auto id : ansvec) {
        cout << id << " ";
    }
}