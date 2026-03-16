#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<string>> ans{};
    vector<string> cutrow{};
    vector<bool> isdraw = vector<bool>(90, false);
    vector<vector<int>> dir = {{1, 0}, {1, -1}, {1, 1}};

    void backtracking(int n, int startrow, int startcol, int cnt) {
        if (cnt == n) {
            ans.emplace_back(cutrow);
            return;
        }

        for (int j = startcol; j < n; ++j) {
            if(isdraw[startrow * 10 + j]) continue;
            vector<int> draws{};
            // 标记正下方/斜方
            for (int inneri = 0; inneri < dir.size(); ++inneri) {
                int addrow = dir[inneri][0], addcol = dir[inneri][1];
                int nextrow = startrow + addrow, nextcol = j + addcol;
                while (nextrow >= 0 && nextrow < n && nextcol >= 0 && nextcol < n) {
                    if(!isdraw[nextrow * 10 + nextcol]) {
                        draws.emplace_back(nextrow * 10 + nextcol);
                        isdraw[nextrow * 10 + nextcol] = true;
                    }
                    nextrow += addrow;
                    nextcol += addcol;
                }
            }

            string rowstr{};
            for (int inneri = 0; inneri < n; ++inneri) {
                if (inneri == j)
                    rowstr += "Q";
                else
                    rowstr += ".";
            }
            cutrow.emplace_back(rowstr);
            cout << rowstr << endl;
            for (int inneri = 0; inneri < draws.size(); ++inneri)
                cout << draws[inneri] << " ";
            cout << "\n";
            // 计算下一行选择的点
            int nextstartrow = -1, nextstartcol = -1;
            if (startrow + 1 < n) {
                int downrow = startrow + 1;
                for (int downcol = 0; downcol < n; ++downcol) {
                    if (isdraw[downrow * 10 + downcol] == false) {
                        nextstartrow = downrow;
                        nextstartcol = downcol;
                        cout << "nextrowcol:" << nextstartrow << " "
                             << nextstartcol << "\n";
                        cout << "nextcnt:" << cnt + 1 << "\n\n";
                        backtracking(n, nextstartrow, nextstartcol, cnt + 1);
                    }
                }
            } else {
                cout << "nextrowcol:" << nextstartrow << " " << nextstartcol
                     << "\n";
                cout << "nextcnt:" << cnt + 1 << "\n\n";
                backtracking(n, nextstartrow, nextstartcol, cnt + 1);
            }
            cutrow.pop_back();

            for (int inneri = 0; inneri < draws.size(); ++inneri) {
                isdraw[draws[inneri]] = false;
            }
        }
    }

    vector<vector<string>> solveNQueens(int n) {
        backtracking(n, 0, 0, 0);
        return ans;
    }
};

int main() {
    Solution sol;
    sol.solveNQueens(5);

}