#include <bits/stdc++.h>
using namespace std;

void printList(list<int>& list) {
    for(int num : list) {
        cout << num  << " ";
    }
    cout << "\n";
}

class LRU {
public:
    LRU(int maxcnt) : _max_cnt(maxcnt), _cur_cnt(0) {}

    int get(int key) {
        // exist: 1. erase, push_back 2. return value
        if(_kv.find(key) != _kv.end()) {
            _key_list.erase(find(_key_list.begin(), _key_list.end(), key)); // O(N)时间复杂度，违背LRU的设计原则
            _key_list.push_back(key);

            return _kv[key];
        }

        // no: return -1
        return -1;
    }

    void put(int key, int value) {
        // exist: erase, push_front, (_kv)update
        if(_kv.find(key) != _kv.end()) {
            _key_list.erase(find(_key_list.begin(), _key_list.end(), key));
            _key_list.push_back(key);

            _kv[key] = value;
            return;
        }
    
        // no:  < max : push_back, (_kv)insert  
        //      >= max : pop_front, (_kv)erase, push_back, (_kv)insert
        if(_cur_cnt >= _max_cnt) {
            int front_key = _key_list.front();
            _key_list.pop_front();
            _kv.erase(front_key);
            --_cur_cnt;
        }
        _key_list.push_back(key);
        _kv.insert(make_pair(key, value));
        ++_cur_cnt;
    }

    unordered_map<int, int> _kv;
    list<int> _key_list;
    int _max_cnt;
    int _cur_cnt;
};

int main() {
    LRU lru(2);
    lru.put(1, 1);
    printList(lru._key_list);
    lru.put(2, 2);
    // cout << "before get(1) : ";
    printList(lru._key_list);
    cout << "get(1) : " << lru.get(1) << "\n";
    // cout << "after get(1) : ";
    printList(lru._key_list);

    lru.put(3, 3);
    printList(lru._key_list);
    cout << "get(2) : " << lru.get(2) << "\n";
    printList(lru._key_list);
    lru.put(1, 11);
    printList(lru._key_list);
}

/* 
push(1, 1)
push(2, 2) // 1, 2
get(1)      // 2, 1
push(3, 3); // 1, 3
get(2) 

*/