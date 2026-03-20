#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <chrono>
#include <shared_mutex>  // 仅用于兼容 shared_lock/unique_lock 接口

// 写优先的读写锁实现
class WritePrioritySharedMutex {
private:
    std::mutex mtx_;                          // 保护内部状态的基础锁
    std::condition_variable_any cv_;          // 条件变量，用于线程等待/唤醒
    int active_readers_ = 0;                  // 活跃读线程数
    int waiting_writers_ = 0;                 // 等待的写线程数
    bool active_writer_ = false;              // 是否有活跃写线程

public:
    // 构造/析构（默认即可）
    WritePrioritySharedMutex() = default;
    ~WritePrioritySharedMutex() = default;

    // 禁止拷贝和移动（互斥锁不可拷贝）
    WritePrioritySharedMutex(const WritePrioritySharedMutex&) = delete;
    WritePrioritySharedMutex& operator=(const WritePrioritySharedMutex&) = delete;
    WritePrioritySharedMutex(WritePrioritySharedMutex&&) = delete;
    WritePrioritySharedMutex& operator=(WritePrioritySharedMutex&&) = delete;

    // ========== 写锁操作（独占） ==========
    // 获取写锁（阻塞直到获取）
    void lock() {
        std::unique_lock<std::mutex> lock(mtx_);
        waiting_writers_++;  // 标记有写线程等待
        // 等待条件：无活跃读、无活跃写
        cv_.wait(lock, [this]() {
            return active_readers_ == 0 && !active_writer_;
        });
        waiting_writers_--;
        active_writer_ = true;  // 标记有活跃写线程
    }

    // 释放写锁
    void unlock() {
        std::lock_guard<std::mutex> lock(mtx_);
        active_writer_ = false;  // 清除活跃写标记
        cv_.notify_all();        // 唤醒所有等待的读/写线程
    }

    // ========== 读锁操作（共享） ==========
    // 获取读锁（阻塞直到获取，且优先让写线程执行）
    void lock_shared() {
        std::unique_lock<std::mutex> lock(mtx_);
        // 写优先核心：有写线程等待 或 有活跃写线程时，读线程等待
        cv_.wait(lock, [this]() {
            return waiting_writers_ == 0 && !active_writer_;
        });
        active_readers_++;  // 增加活跃读线程数
    }

    // 释放读锁
    void unlock_shared() {
        std::lock_guard<std::mutex> lock(mtx_);
        active_readers_--;  // 减少活跃读线程数
        if (active_readers_ == 0) {
            cv_.notify_all();  // 无活跃读时，唤醒等待的写线程
        }
    }

    // ========== 可选：超时尝试加锁（简化版，核心功能已实现） ==========
    bool try_lock() {
        std::lock_guard<std::mutex> lock(mtx_);
        if (active_readers_ == 0 && !active_writer_) {
            active_writer_ = true;
            return true;
        }
        return false;
    }

    bool try_lock_shared() {
        std::lock_guard<std::mutex> lock(mtx_);
        if (waiting_writers_ == 0 && !active_writer_) {
            active_readers_++;
            return true;
        }
        return false;
    }
};

// ========== 测试代码 ==========
WritePrioritySharedMutex rw_mtx;  // 写优先读写锁
int shared_data = 0;              // 共享资源

// 读线程函数（模拟高频读）
void reader_thread(int id) {
    for (int i = 0; i < 5; ++i) {
        std::shared_lock<WritePrioritySharedMutex> lock(rw_mtx);  // 读锁
        std::cout << "[读线程 " << id << "] 读取数据：" << shared_data 
                  << " (活跃读线程数：" << i << ")\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(10));  // 模拟读耗时
        // 锁自动释放
    }
}

// 写线程函数（模拟写操作）
void writer_thread(int id, int value) {
    std::unique_lock<WritePrioritySharedMutex> lock(rw_mtx);  // 写锁
    std::cout << "\033[31m[写线程 " << id << "] 修改数据为：" << value << "\033[0m\n";
    shared_data = value;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));  // 模拟写耗时
    // 锁自动释放
}

int main() {
    // 创建 5 个读线程（模拟读密集）
    std::vector<std::thread> readers;
    for (int i = 1; i <= 5; ++i) {
        readers.emplace_back(reader_thread, i);
    }

    // 创建 2 个写线程（验证写优先）
    std::vector<std::thread> writers;
    writers.emplace_back(writer_thread, 1, 100);
    writers.emplace_back(writer_thread, 2, 200);

    // 等待所有读线程完成
    for (auto& t : readers) {
        t.join();
    }
    // 等待所有写线程完成
    for (auto& t : writers) {
        t.join();
    }

    std::cout << "\n最终数据：" << shared_data << std::endl;
    return 0;
}