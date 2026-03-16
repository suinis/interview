#include <bits/stdc++.h>
#include <list>
#include <unordered_map>
#include <utility>
// 最近未使用缓存策略
class LRU {
    LRU(int maxlen) : maxLength(maxlen){}

    int get(int key) {
        if(unmap.find(key) != unmap.end()) {
            klist.erase(unmap[key].second);
            klist.push_front(key);
            unmap[key].second = klist.begin();
            return unmap[key].first;
        }
        return -1;
    }

    void put(int key, int val) {
        if(unmap.find(key) != unmap.end()) {
            klist.erase(unmap[key].second);
            klist.push_front(key);
            unmap[key] = {val, klist.begin()};
            return;
        }
        // not found 
        if(klist.size() >= maxLength) {
            int old_key = klist.back();
            klist.pop_back();
            unmap.erase(old_key);
        }
        // 队尾删除，新数据插入队头
        klist.push_front(key);
        unmap[key] = {val, klist.begin()};
        return;
    }
    
    // 底层数据结构
    std::pmr::unordered_map<int , std::pair<int, std::pmr::list<int>::iterator>> unmap;
    std::pmr::list<int> klist;
    int maxLength;
};

// 2： 3