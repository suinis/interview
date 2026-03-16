#include <iostream>
#include <vector>
#include <string>
#include <functional>

using namespace std;

int main() {
    int N, M;

    cin >> N >> M;
    vector<vector<char>> grid(N, vector<char>(M));
    pair<int, int> start, end;
    vector<pair<int, int>> portals;
    
    // 读取网格
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == 'E') {
                start = {i, j};
            } else if (grid[i][j] == 'Q') {
                end = {i, j};
            } else if (grid[i][j] == '2') {
                portals.push_back({i, j});
            }
        }
    }
    
    // 路径计数
    int pathCount = 0;
    vector<vector<bool>> visited(N, vector<bool>(M, false));
    
    // DFS函数
    function<void(int, int)> dfs = [&](int r, int c) {
        if (r < 0 || r >= N || c < 0 || c >= M || visited[r][c] || grid[r][c] == '-') {
            return;
        }
        
        // 到达终点
        if (r == end.first && c == end.second) {
            pathCount++;
            return;
        }
        
        // 标记访问
        visited[r][c] = true;
        
        // 如果是传送门，传送到另一个传送门
        if (grid[r][c] == '2' && portals.size() == 2) {
            pair<int, int> otherPortal;
            if (portals[0].first == r && portals[0].second == c) {
                otherPortal = portals[1];
            } else {
                otherPortal = portals[0];
            }
            
            // 如果另一个传送门没有被访问过，则传送
            if (!visited[otherPortal.first][otherPortal.second]) {
                // 递归探索另一个传送门的位置
                dfs(otherPortal.first, otherPortal.second);
            } else { // 是从另一个传送门里传过来的，不需要再传过去，继续四周dfs
                dfs(r + 1, c);
                dfs(r - 1, c);
                dfs(r, c + 1);
                dfs(r, c - 1);
            }
        } else {
            // 普通移动：上下左右
            dfs(r + 1, c);
            dfs(r - 1, c);
            dfs(r, c + 1);
            dfs(r, c - 1);
        }
        
        // 回溯
        visited[r][c] = false;
    };
    
    // 从起点开始DFS
    dfs(start.first, start.second);
    
    // 输出结果
    cout << pathCount << endl;
    
    return 0;
}


/* 
从E到Q所有可能路径数
E 入口
- 墙壁
0 可选
2 传送门（必定有两个）
Q 出口

4 5
E 0 0 0 0 
- - - - 0
0 0 - - 0
0 0 0 0 Q

4 5
E 0 0 0 0 
- - 2 - -
0 0 - - 0
0 2 0 0 Q

4 5
E 0 0 0 0 
0 - - - 0
0 0 - - 0
0 0 0 0 Q

3 3
E 0 0
0 0 0
0 0 Q
*/