#include <mutex>
using namespace std;

class Singleton {
private:
    Singleton() = default; // 私有构造
    ~Singleton() = default;
    Singleton(const Singleton&) = delete; // 禁用拷贝
    Singleton& operator=(const Singleton&) = delete; // 禁用赋值
    
    static mutex mtx;
    static Singleton* instance;
public:
    static Singleton* getInstance() {
        if (instance == nullptr) { // 双重检查，减少锁竞争
            lock_guard<mutex> lock(mtx);
            if (instance == nullptr) {
                instance = new Singleton();
            }
        }
        return instance;
    }
    
    // 释放资源（可选）
    static void release() {
        lock_guard<mutex> lock(mtx);
        if (instance != nullptr) {
            delete instance;
            instance = nullptr;
        }
    }
};

// 静态成员初始化
Singleton* Singleton::instance = nullptr;
mutex Singleton::mtx;