#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> allpaths;
vector<int> path;
vector<bool> isselect;

void dfs(unordered_map<int, vector<int>>& hashmap, int startPoint, int targetPoint) {
    if(startPoint == targetPoint) {
        allpaths.push_back(path);
        return;
    }

    const vector<int>& tovec = hashmap[startPoint];
    for(int point : tovec) {
        path.push_back(point);
        isselect[point] = true;
        dfs(hashmap, point, targetPoint);
        path.pop_back();
        isselect[point] = false;
    }

}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    unordered_map<int, vector<int>> hashmap{};
    isselect = vector<bool>(n + 1, false);

    for(int i = 0; i < m; ++i) {
        int from, to;
        cin >> from >> to;
        hashmap[from].push_back(to);
    }

    path.push_back(1);
    isselect[1] = true;
    dfs(hashmap, 1, n);

    if(allpaths.empty()) {
         cout << -1 << "\n";
         return 0;
    }
    for(const auto& path : allpaths) {
        for(int i = 0; i < path.size() - 1; ++i) {
            cout << path[i] << " ";
        }
        cout << path.back() << "\n";
    }
}