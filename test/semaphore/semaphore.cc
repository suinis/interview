#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <mutex>
#include <condition_variable>

// 简单计数信号量实现，兼容不支持 <semaphore> 的编译器
class SimpleSemaphore {
public:
    explicit SimpleSemaphore(int count = 0)
        : count_(count) {}

    void acquire() {
        std::unique_lock<std::mutex> lock(mtx_);
        cv_.wait(lock, [&] { return count_ > 0; });
        --count_;
    }

    void release() {
        {
            std::lock_guard<std::mutex> lock(mtx_);
            ++count_;
        }
        cv_.notify_one();
    }

private:
    std::mutex mtx_;
    std::condition_variable cv_;
    int count_;
};

// 定义计数信号量：最多允许 2 个线程同时访问资源
SimpleSemaphore sem(2);

// 线程任务：访问受限资源
void task(int id) {
    // 1. 获取信号量（计数器减 1，若为 0 则阻塞）
    sem.acquire();
    std::cout << "线程 " << id << " 进入临界区\n";
    
    // 模拟耗时操作
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    
    // 2. 释放信号量（计数器加 1，唤醒等待线程）
    std::cout << "线程 " << id << " 退出临界区\n";
    sem.release();
}

int main() {
    // 创建 5 个线程（但最多 2 个同时执行临界区代码）
    std::vector<std::thread> threads;
    for (int i = 1; i <= 5; ++i) {
        threads.emplace_back(task, i);
    }

    // 等待所有线程完成
    for (auto& t : threads) {
        t.join();
    }

    return 0;
}