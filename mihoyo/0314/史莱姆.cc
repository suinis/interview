#include <bits/stdc++.h>
#include <cstddef>
#include <ios>
#include <iostream>
#include <unordered_set>
#include <vector>

const int maxn = 1e6 + 10;
int n, a[maxn], mp[maxn];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);    

    std::cin >> n;
    for(int i = 0; i < n; ++i) {
        std::cin >> a[i];
        mp[i] = i; // 每个史莱姆位置的初始化
    }

    std::vector<int> res{};
    int loop = n;
    while(loop--) {
        std::unordered_set<int> exist_index_set;
        for(int i = 0; i < n; ++i) {
            if(a[i] == 0) {
                mp[i] = std::max(-1, mp[i] - 1);
            } else {
                mp[i] = std::min(n, mp[i] + 1);
                
            }
            // std::cout << mp[i] << " ";
            if(mp[i] >= 0 && mp[i] < n) exist_index_set.insert(mp[i]);
        }
        // std::cout << "\n";
        res.push_back(n - exist_index_set.size());
    }

    for(int empty_cnt : res) {
        std::cout << empty_cnt << " ";
    }
    std::cout << "\n";
}

/*  方法二（待验证）
    定义一个格子的状态数组status
    0 ： 表示格子为空
    1 ： 表示格子里有一个史莱姆，方向向左
    2 ： 表示格子里有一个史莱姆，方向向右
    3 ： 表示格子里右两个史莱姆，一个向左一个向右

    应该不存在一个格子里同时存在两个方向相同的史莱姆，因为起始位置不一样，每次移动格数也一样
*/

/*
史莱姆数量
每个史莱姆移动方向

输出：第i个时间没有史莱姆格子的数量
3
1 0 1

1 2 3
*/

