// arr , 打乱

//arr 0 1 2 3 4 5 6 7 8 9

#include <algorithm>
#include <bits/stdc++.h>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <list>
#include <queue>
#include <random>
#include <stack>
#include <unordered_map>
#include <utility>
#include <vector>
#include <memory_resource>

void print(const std::pmr::vector<int>& vec) {
    for(auto& num : vec) {
        std::cout << num << " ";
    }
    std::cout << "\n";
}

int main() {
    // srand(unsigned int seed)
    // std::shuffle(RAIter, RAIter, UGenerator &&);
    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 rng(seed);
    // set
    std::pmr::vector<int> vec = {0 ,1 , 2 ,3, 4, 5 ,6 ,7 ,8 ,9};

    // std::swap(vec[index], vec[vec.size() - index]);
    std::shuffle(vec.begin(), vec.end(), rng);
    print(vec);
}

