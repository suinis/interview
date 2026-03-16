#include <cstdlib>
#include <mutex>
using namespace std;

// 内存块节点
struct MemBlock {
    MemBlock* next;
    char data[0]; // 柔性数组，节省空间
};

class MemoryPool {
private:
    MemBlock* free_list; // 空闲块链表
    size_t block_size;   // 块大小
    mutex mtx;           // 线程安全锁
public:
    MemoryPool(size_t size) : block_size(size), free_list(nullptr) {}
    
    // 分配内存
    void* allocate() {
        lock_guard<mutex> lock(mtx);
        if (free_list == nullptr) {
            // 申请一大块内存，拆分多个小块
            size_t alloc_size = 10 * (block_size + sizeof(MemBlock));
            MemBlock* new_block = (MemBlock*)malloc(alloc_size);
            // 拼接空闲链表
            for (int i = 0; i < 10; ++i) {
                MemBlock* p = (MemBlock*)((char*)new_block + i * (block_size + sizeof(MemBlock)));
                p->next = free_list;
                free_list = p;
            }
        }
        // 从空闲链表取一块
        MemBlock* res = free_list;
        free_list = free_list->next;
        return res->data;
    }
    
    // 释放内存
    void deallocate(void* ptr) {
        lock_guard<mutex> lock(mtx);
        MemBlock* block = (MemBlock*)((char*)ptr - sizeof(MemBlock));
        block->next = free_list;
        free_list = block;
    }
    
    ~MemoryPool() {
        lock_guard<mutex> lock(mtx);
        while (free_list != nullptr) {
            MemBlock* next = free_list->next;
            free(free_list);
            free_list = next;
        }
    }
};