#include <bits/stdc++.h>
using namespace std;

void printvec(const vector<int>& dp) {
    for(int i = 0; i < dp.size(); ++i) {
        cout << dp[i] << " ";
    }
    cout << "\n";
}

void two_dimensional_array(int n, int bagSpace, const vector<int>& space, const vector<int>& value) {
    vector<vector<int>> dp(n, vector<int>(bagSpace + 1));
    for(int j = space[0]; j <= bagSpace; ++j) {
        dp[0][j] = value[0];
    }


    // 二维dp,可以改变bagSpace和n的顺序
    // 主要是二维保存了前面的副本,而一维靠自身维护,而dp[i][j]又依赖左上方/正上方结果
    // 故变为一维只能从后往前计算,且不能调换bagSpace和n的两层遍历顺序
    for(int i = 1; i < n; ++i) {
        for(int j = 1; j <= bagSpace; ++j) {
            if(j < space[i]) {
                dp[i][j] = dp[i - 1][j];
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - space[i]] + value[i]);
            }
        }
    }

    
    // for(int j = 1; j <= bagSpace; ++j) {
    //     for(int i = 1; i < n; ++i) {
    //         if(j < space[i]) {
    //             dp[i][j] = dp[i - 1][j];
    //         } else {
    //             dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - space[i]] + value[i]);
    //         }
    //     }
    // }


    cout << dp[n - 1][bagSpace] << endl;
}

void one_dimensional_array(int n, int bagSpace, const vector<int>& space, const vector<int>& value) {
    vector<int> dp(bagSpace + 1, 0);

    for(int i = 0; i < n; ++i) {
        for(int j = bagSpace; j > 0; --j) {
            if(j >= space[i]) {
                dp[j] = max(dp[j], dp[j - space[i]] + value[i]);
            }
        }
        printvec(dp);
    }
    /* 
    0 15 15 15 15 
    0 15 15 20 35 
    0 15 15 20 35
    */
    
    // 一维dp，不可改变遍历顺序
    // for(int j = bagSpace; j >= 0; --j) {
    //     for(int i = 0; i < n; ++i) {
    //         if(j >= space[i]) {
    //             dp[j] = max(dp[j], dp[j - space[i]] + value[i]);
    //         }
    //     }
    //     printvec(dp);
    // }
    /* 
    0 0 0 0 30 
    0 0 0 20 30 
    0 0 15 20 30 
    0 15 15 20 30 
    0 15 15 20 30
    */


    // for(int j = 1; j <= bagSpace; ++j) {
    //     for(int i = 0; i < n; ++i) {
    //         if(j >= space[i]) {
    //             dp[j] = max(dp[j], dp[j - space[i]] + value[i]);
    //         }
    //     }
    //     printvec(dp);
    // }
    /* 
    0 15 0 0 0 
    0 15 30 0 0 
    0 15 30 45 0 
    0 15 30 45 60   
    */
    cout << dp[bagSpace] << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int n, bagSpace;
    vector<int> space(n);
    vector<int> value(n);

    cin >> n >> bagSpace;
    for(int i = 0; i < n; ++i) {
        cin >> space[i];
    }
    for(int i = 0; i < n; ++i) {
        cin >> value[i];
    }

    two_dimensional_array(n, bagSpace, space, value);
    
    // one_dimensional_array(n, bagSpace, space, value);
}   

/* 
6 1
2 2 3 1 5 2
2 3 1 5 4 3

5
=================
3 4
1 3 4
15 20 30

35
*/