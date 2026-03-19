#include <iostream>
#include <thread>
#include <semaphore>  // C++20 核心头文件
#include <vector>
#include <chrono>

// 定义计数信号量：最多允许 2 个线程同时访问资源
std::counting_semaphore<2> sem(2);  // 模板参数是最大计数值，构造参数是初始计数值

// 线程任务：访问受限资源
void task(int id) {
    // 1. 获取信号量（计数器减 1，若为 0 则阻塞）
    sem.acquire();
    std::cout << "线程 " << id << " 进入临界区（当前可用资源数：" << sem.max() - sem.count() << "）\n";
    
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