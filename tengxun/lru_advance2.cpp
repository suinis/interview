#include <bits/stdc++.h>
using namespace std;

class LRU {
public:
    LRU(int maxcnt) : _max_cnt(maxcnt) {}

    int get(int key) {
        // exist: 1. erase, push_back 2. return value
        if(_cache.find(key) != _cache.end()) {
            _key_list.splice(_key_list.end(), _key_list, _cache[key].second);

            return _cache[key].first;
        }

        // no: return -1
        return -1;
    }

    void put(int key, int value) {
        // exist: erase, push_front, (_kv)update
        if(_cache.find(key) != _cache.end()) {
            _key_list.splice(_key_list.end(), _key_list, _cache[key].second);

            _cache[key].first = value;
            // _cache[key].second = --_key_list.end(); // 无需更新，splice操作只是改变节点在链表中的位置，但节点本身和指向它的迭代器仍然有效。
            return;
        }
    
        // no:  < max : push_back, (_kv)insert  
        //      >= max : pop_front, (_kv)erase, push_back, (_kv)insert
        if(_key_list.size() >= _max_cnt) {
            int front_key = _key_list.front();
            _key_list.pop_front();
            _cache.erase(front_key);
        }
        _key_list.push_back(key);

        /* 
            
            // 前向迭代器如：forward_list不可以使用prev
            题外话：next(_key_list.rbegin(), 1).base() // 指向的是最后一个元素，因为base将反向迭代器转为正向迭代器时，指向的是对应元素的后一位元素
            auto rit = next(lst.rbegin(), 1);  // 指向倒数第二个元素，但是反向迭代器，splice这里就不能传入反向迭代器
            auto it = rit.base();              // 转为正向迭代器，但指向最后一个元素
         */
        // _cache[key] = make_pair(value, --_key_list.end()); // 也可以
        _cache[key] = make_pair(value, prev(_key_list.end(), 1)); // prev第二参数默认为1，可不写 
    }

    void print() {
        for (int key : _key_list) {
            cout << key << "(" << _cache[key].first << ") ";
        }
        cout << "\n";
    }

    /* 
        链尾最近使用，链头最近未使用。
        但常见写法是：链头最近使用，链尾最近未使用
            这样就更方便如： _cache[key] = make_pair(value, _key_list.begin()); 
    */
    unordered_map<int, pair<int, list<int>::iterator>> _cache; 
    list<int> _key_list;
    int _max_cnt;
};

int main() {
    LRU lru(3);
    lru.put(1, 1);
    lru.print();
    lru.put(2, 2);
    lru.print();
    lru.put(3, 3);
    lru.print();
    cout << "get(1) : " << lru.get(1) << "\n";
    // cout << "after get(1) : ";
    lru.print();

    lru.put(4, 4);
    lru.print();
    cout << "get(2) : " << lru.get(2) << "\n";
    lru.print();
    lru.put(1, 11);
    lru.print();
}

/* 
push(1, 1)
push(2, 2) // 1, 2
get(1)      // 2, 1
push(3, 3); // 1, 3
get(2) 

*/