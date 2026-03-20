#include <atomic>
#include <cstddef>
#include <cstdlib>
#include <mutex>
#include <pthread.h>
class SingleTon {
private:
    SingleTon() = default;
    SingleTon(const SingleTon&) = delete;
    SingleTon& operator=(const SingleTon&) = delete;
    SingleTon(SingleTon&&) = delete;
    SingleTon& operator=(SingleTon&&) = delete;

    static std::mutex mtx;
    static std::atomic<SingleTon*> instance;

    static void release() {
        if(instance != nullptr) {
            delete instance;
            instance = nullptr;
        }
    }

public:
    static SingleTon* getInstance() {
        // {// 第一次“无锁”读指针，只保证指针本身是原子的
        //     SingleTon* tmp = instance.load(std::memory_order_relaxed);
        // // acquire 屏障：如果刚才读到的是已经发布过的指针，
        // // 那么之后访问对象时，能看到构造线程 release 之前的所有写
        //     std::atomic_thread_fence(std::memory_order_acquire);  // 跟其他线程的release写对应，实现同步
        // }
        //等价于：

        /* 
            release 栅栏 + store 指针：钉住“先构造完、再发布指针”的顺序。
            acquire 读指针：一旦读到非空，就和那次 release 同步，保证你后面用对象时，构造的写已经对你可见。
        */
        SingleTon* tmp = instance.load(std::memory_order_acquire);
        if(tmp == nullptr) {
            std::lock_guard<std::mutex> lock(mtx);
            // 加锁后再次读取，避免多个线程同时 new。（因为tmp是前一次读取的值，本身并不会变化，要检查的是instance的当前状态）
            tmp = instance.load(std::memory_order_relaxed);
            if(tmp == nullptr) {
                tmp = new SingleTon();
                // release 屏障：先“提交”构造中的所有写，再把指针对外发布
                std::atomic_thread_fence(std::memory_order_release);
                // relaxed 写指针值本身；可见性由上面的 release/acquire 保证
                instance.store(tmp, std::memory_order_relaxed);
                atexit(release);
            }
        }
        return tmp; // instance 是原子类型，这里返回普通指针 tmp
    }
    
};

/* 
std::atomic<SingleTon*> instance 只保证 “指针这个变量的读写是原子/不撕裂”，
并不能把 new SingleTon() 这一整套“申请内存 + 调构造 + 写成员”的过程，变成一个“不可分割的大原子操作”。
*/
std::atomic<SingleTon*> SingleTon::instance = nullptr;
std::mutex SingleTon::mtx;