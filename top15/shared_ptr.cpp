#include <atomic> // 原子操作保证引用计数线程安全
using namespace std;

template <typename T>
class SharedPtr {
private:
    T* ptr;                // 裸指针
    atomic<int>* ref_count;// 引用计数（动态分配，共享）
    // 自定义删除器（简化版）
    void (*deleter)(T*) = [](T* p) { delete p; };

    // 释放当前对象（核心）
    void release() {
        if (ref_count && --(*ref_count) == 0) {
            deleter(ptr);    // 释放对象
            delete ref_count;// 释放引用计数
        }
        ptr = nullptr;
        ref_count = nullptr;
    }
public:
    // 构造函数
    explicit SharedPtr(T* p = nullptr) : ptr(p) {
        ref_count = new atomic<int>(p ? 1 : 0);
    }

    // 拷贝构造（共享指针+引用计数+1）
    SharedPtr(const SharedPtr& other) {
        ptr = other.ptr;
        ref_count = other.ref_count;
        if (ref_count) (*ref_count)++;
    }

    // 赋值运算符
    SharedPtr& operator=(const SharedPtr& other) {
        if (this != &other) {
            release(); // 先释放当前
            ptr = other.ptr;
            ref_count = other.ref_count;
            if (ref_count) (*ref_count)++;
        }
        return *this;
    }

    // 析构函数
    ~SharedPtr() {
        release();
    }

    // 常用接口
    T* get() const { return ptr; }
    int use_count() const { return ref_count ? *ref_count : 0; }
    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }
};