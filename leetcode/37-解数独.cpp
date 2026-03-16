#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<vector<bool>> rownum{};
    vector<vector<bool>> colnum{};
    vector<vector<vector<bool>>> ninenum{};

    void printmatrix(const vector<vector<char>> board) {
        for(int i = 0; i < 9; ++i) {
            for(int j = 0; j < 9; ++j) {
                cout << board[i][j] << " ";
            }
            cout << "\n";
        }
    }

    bool backtracking(vector<vector<char>> &board, int starti, int startj)
    {
        if (starti == 9)
            return true;

        if (board[starti][startj] == '.')
        {
            for (int num = 1; num <= 9; ++num)
            {
                if (!rownum[starti][num] && !colnum[startj][num] && !ninenum[starti / 3][startj / 3][num])
                {
                    board[starti][startj] = num + '0';
                    rownum[starti][num] = true;
                    colnum[startj][num] = true;
                    ninenum[starti / 3][startj / 3][num] = true;
                    int newstarti = (startj == 8) ? starti + 1 : starti;
                    int newstartj = (startj + 1) % 9;
                    printmatrix(board);
                    cout << "\n";

                    if(backtracking(board, newstarti, newstartj)) return true;

                    rownum[starti][num] = false;
                    colnum[startj][num] = false;
                    ninenum[starti / 3][startj / 3][num] = false;
                    board[starti][startj] = '.';
                }
            }
            return false;
        }

        int newstarti = (startj == 8) ? starti + 1 : starti;
        int newstartj = (startj + 1) % 9;
        if(backtracking(board, newstarti, newstartj)) return true;
        
        return false;
    }

    void solveSudoku(vector<vector<char>> &board)
    {
        int n = board.size();
        rownum.resize(n, vector<bool>(10, false));
        colnum.resize(n, vector<bool>(10, false));
        ninenum.resize(3, vector<vector<bool>>(3, vector<bool>(10, false)));

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (board[i][j] != '.')
                {
                    int num = board[i][j] - '0';
                    rownum[i][num] = true;
                    colnum[j][num] = true;
                    ninenum[i / 3][j / 3][num] = true;
                }
            }
        }

        backtracking(board, 0, 0);
    }
};

int main()
{
    Solution sol;
    vector<vector<char>> board = {{'5', '3', '.', '.', '7', '.', '.', '.', '.'},
                                  {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
                                  {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
                                  {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
                                  {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
                                  {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
                                  {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
                                  {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
                                  {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};
    sol.solveSudoku(board);
}