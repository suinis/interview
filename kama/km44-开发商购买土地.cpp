// row: 6 12 18
// col: 4 9 18
#include<iostream>
#include<vector>
#include<climits>
#include <numeric>
using namespace std;

int main(){
    int row = 0, col = 0, sum = 0;
    scanf("%d%d", &row, &col);
    vector<vector<int>> matrix(row, vector<int>(col, 0));
    vector<int> rowpresum(row, 0);
    vector<int> colpresum(col, 0);
    for(int i = 0; i < row; ++i) {
        for(int j = 0; j < col; ++j) {
            scanf("%d", &matrix[i][j]);
            sum += matrix[i][j];
        }
        rowpresum[i] = sum;
    }

    sum = 0;
    for(int j = 0; j < col; ++j) {
        for(int i = 0; i < row; ++i) {
            sum += matrix[i][j];
        }
        colpresum[j] = sum;
    }

    int minCut = INT_MAX;
    for(int i = 0; i < row - 1; ++i) {
        minCut = min(minCut, abs(rowpresum[row - 1] - rowpresum[i] * 2));
    }

    for(int j = 0; j < col - 1; ++j) {
        minCut = min(minCut, abs(colpresum[col - 1] - colpresum[j] * 2));
    }
    printf("%d", minCut);

    accumulate(rowpresum.begin(), rowpresum.end(), 0);
}

