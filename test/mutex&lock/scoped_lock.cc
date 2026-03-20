#include <mutex>
#include <thread>

std::mutex mtx1, mtx2;

// 错误写法：两个线程加锁顺序相反，易死锁
// void bad_task1() { mtx1.lock(); mtx2.lock(); ... }
// void bad_task2() { mtx2.lock(); mtx1.lock(); ... }

// 正确写法：用 scoped_lock 批量加锁
void safe_task1() {
    std::scoped_lock lock(mtx1, mtx2);  // 自动按安全顺序加锁
    // 临界区：同时操作 mtx1 和 mtx2 保护的资源
}

void safe_task2() {
    std::scoped_lock lock(mtx2, mtx1);  // 顺序无关，底层自动调整
    // 临界区
}