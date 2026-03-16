/* 
1. 核心定义
LRU 是缓存淘汰策略：当缓存容量满时，淘汰「最近最少使用」的元素，保证缓存中都是高频访问的数据，天美后台用它做：
玩家临时数据缓存（如登录态、战斗数据）；
游戏配置缓存（如道具表、地图数据）；
减少数据库 / 磁盘访问，提升游戏响应速度。
2. 核心要求（面试必实现的功能）
get(key)：获取 key 对应的 value，若 key 不存在返回 - 1；访问后将该 key 标记为「最新使用」；
put(key, value)：插入 / 更新 key-value，若容量满则淘汰「最久未使用」的 key，再插入新 key。
3. 性能要求（天美重点关注）
操作时间复杂度必须 O (1)（否则面试官会追问优化）；
工程上要考虑线程安全（天美后台高并发场景）。
*/


#include <unordered_map>
#include <list>
using namespace std;

class LRUCache {
private:
    int capacity;
    // 双向链表：保存key，按访问顺序排列（头=最新，尾=最旧）
    list<int> cache_list;
    // 哈希表：key -> (value, 链表迭代器)
    unordered_map<int, pair<int, list<int>::iterator>> cache_map;
public:
    LRUCache(int cap) : capacity(cap) {}
    
    int get(int key) {
        if (cache_map.find(key) == cache_map.end()) return -1;
        // 移到链表头部（标记为最新访问）
        cache_list.erase(cache_map[key].second);
        cache_list.push_front(key);
        cache_map[key].second = cache_list.begin();
        return cache_map[key].first;
    }
    
    void put(int key, int value) {
        if (cache_map.find(key) != cache_map.end()) {
            // 已存在，更新值并移到头部
            cache_list.erase(cache_map[key].second);
            cache_list.push_front(key);
            cache_map[key] = {value, cache_list.begin()};
        } else {
            // 不存在，检查容量
            if (cache_list.size() == capacity) {
                // 删除最久未使用的
                int old_key = cache_list.back();
                cache_list.pop_back();
                cache_map.erase(old_key);
            }
            // 插入新值
            cache_list.push_front(key);
            cache_map[key] = {value, cache_list.begin()};
        }
    }
};