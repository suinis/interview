#include <bits/stdc++.h>
using namespace std;

static int n, m;
static int d[4][2] = {1, 0, 0, 1, -1, 0, 0, -1};
static vector<vector<int>> l;
static vector<vector<bool>> v;
static int ans = 0;

namespace dfs1 {
    void dfs(int x, int y, int& cnt) {
        for(int i = 0; i < 4; ++i) {
            int nextx = x + d[i][0];
            int nexty = y + d[i][1];
            if(nextx < 0 || nextx >= n || nexty < 0 || nexty >= m || v[nextx][nexty]) continue;
            if(l[nextx][nexty] == 0) {
                v[nextx][nexty] = true;
                continue;
            }
            v[nextx][nexty] = true;
            ++cnt;
            dfs(nextx, nexty, cnt);
        }
    }

    // 暴力搜索
    void test() {
        // 暴力搜索，O(n ^ 4)
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                v = vector<vector<bool>>(n, vector<bool>(m, 0));
                if(l[i][j] == 0) {
                    int cnt = 1;
                    dfs(i, j, cnt);
                    ans = max(ans, cnt);
                }
            }
        }

        ans = (ans == 0) ? n * m : ans;
        cout << ans << "\n";
    }
}

namespace dfs2 {
    void dfs(int x, int y, int& cnt, int id) {
        for(int i = 0; i < 4; ++i) {
            int nextx = x + d[i][0];
            int nexty = y + d[i][1];
            if(nextx < 0 || nextx >= n || nexty < 0 || nexty >= m || v[nextx][nexty]) continue;
            if(l[nextx][nexty] == 0) {
                v[nextx][nexty] = true;
                continue;
            }
            v[nextx][nexty] = true;
            l[nextx][nexty] = id;
            ++cnt;
            dfs(nextx, nexty, cnt, id);
        }
    }

    void test() {
        int id = 2; // 岛屿编号从2开始
        unordered_map<int, int> l_id;
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                if(v[i][j] || l[i][j] == 0) continue;
                v[i][j] = true;
                l[i][j] = id;
                int cnt = 1;
                dfs(i, j, cnt, id);

                l_id[id] = cnt; // 记录岛屿id对应面积
                ++id;
            }
        }

        cout <<"\n";
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                cout << l[i][j] << " ";
            }
            cout << "\n";
        }

        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                if(l[i][j] == 0) {
                    unordered_set<int> vl;
                    int cnt = 1; // 记录0填充后，对应连接岛屿面积
                    for(int k = 0; k < 4; ++k) {
                        int nextx = i + d[k][0];
                        int nexty = j + d[k][1];
                        if(nextx < 0 || nextx >= n || nexty < 0 || nexty >= m) continue;

                        int id = l[nextx][nexty];
                        if(vl.count(id) == 0) cnt += l_id[id];
                        vl.insert(id); // ！ 先判断再插入！
                    }
                    ans = max(ans, cnt);
                }
            }
        }

        ans = (ans == 0) ? n * m : ans;
        cout << ans << "\n";
    }
}

namespace dfs3 {
    // 如果题目改为可以填充2个呢，3个呢，k个呢？
    // to do:
    void dfs(int x, int y, int& cnt, int c) {
        ans = max(ans, cnt);
        for(int i = 0; i < 4; ++i) {
            int nextx = x + d[i][0];
            int nexty = y + d[i][1];
            if(nextx < 0 || nextx >= n || nexty < 0 || nexty >= m || v[nextx][nexty]) continue;
            if(c == 0 && l[nextx][nexty] == 0) continue;
            
            v[nextx][nexty] = true;
            ++cnt;
            if(l[nextx][nexty] == 0) {
                dfs(nextx, nexty, cnt, c - 1);
                --cnt; // 这只会减去本次的，若从这个节点继续dfs，cnt会得到：cnt + area(nextx, nexty)的结果，但最终只减了1（应该不是回溯，因为遍历完该点得到的可能并不是完整的岛屿，毕竟是dfs）
            }
            else dfs(nextx, nexty, cnt, c);
        }
    }

    void test() {
        int c = 1; // 可以填为陆地的个数
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                // 不需要特殊讨论为0的：最后ans跟1比较即可，
                // 改为1能跟其余岛屿连接的点，在遍历其余岛屿时已经算进去了，
                // 不能连接的改为1那最大面积为1，也不需要特殊讨论
                if(v[i][j] || l[i][j] == 0) continue; 
                v[i][j] = true;
                int cnt = 1;
                dfs(i, j, cnt, c);
            }
        }

    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    cin >> n >> m;

    l = vector<vector<int>>(n, vector<int>(m, 0));
    v = vector<vector<bool>>(n, vector<bool>(m, false));

    for(int i = 0; i < n; ++i) {
        for(int j = 0;  j< m; ++j) {
            cin >> l[i][j];
        }
    }
    
    // 暴力
    // dfs1::test();
    
    // dfs一次划分岛屿并设定编号，通过map记录对应编号岛屿面积
    dfs2::test();

    // 如果题目改为可以填充2个呢，3个呢，k个呢？
    // dfs3::test();
}

/* 
4 5
1 1 0 0 0
1 1 0 0 0
0 0 1 0 0
0 0 0 1 1

6
*/

/* 
10 10
1 0 0 0 1 0 0 0 0 0
1 1 0 1 1 0 1 0 1 0
1 0 1 1 1 0 0 1 0 0
1 0 1 1 0 0 0 1 0 0
1 1 1 1 1 0 0 1 0 0
1 0 1 1 0 0 0 1 0 0
1 1 1 0 0 1 1 0 1 1
0 1 1 0 1 1 0 0 0 1
0 0 0 1 0 0 0 0 1 1
1 1 1 0 1 0 0 0 0 0

32
*/