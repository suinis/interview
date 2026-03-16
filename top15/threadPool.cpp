#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
using namespace std;

class ThreadPool {
private:
    vector<thread> workers;      // 工作线程池
    queue<function<void()>> tasks; // 任务队列（函数对象）
    mutex mtx;                   // 保护任务队列
    condition_variable cv;       // 唤醒线程
    bool stop;                   // 线程池停止标志

public:
    // 构造：创建n个工作线程
    explicit ThreadPool(size_t num_threads) : stop(false) {
        for (size_t i = 0; i < num_threads; ++i) {
            workers.emplace_back([this]() {
                // 线程循环取任务
                while (true) {
                    function<void()> task;
                    // 加锁取任务
                    {
                        unique_lock<mutex> lock(this->mtx);
                        // 等待：队列非空 或 线程池停止
                        this->cv.wait(lock, [this]() {
                            return this->stop || !this->tasks.empty();
                        });
                        // 线程池停止且队列为空，退出
                        if (this->stop && this->tasks.empty()) return;
                        // 取任务
                        task = move(this->tasks.front());
                        this->tasks.pop();
                    }
                    // 执行任务（解锁后执行，提升并发）
                    task();
                }
            });
        }
    }

    // 添加任务（万能引用+完美转发，支持任意函数/参数）
    template <typename F, typename... Args>
    void enqueue(F&& f, Args&&... args) {
        // 包装任务
        function<void()> task = bind(forward<F>(f), forward<Args>(args)...);
        // 加锁入队
        {
            lock_guard<mutex> lock(mtx);
            if (stop) throw runtime_error("enqueue on stopped ThreadPool");
            tasks.emplace(move(task)); // 移动语义，减少拷贝
        }
        // 唤醒一个线程执行任务
        cv.notify_one();
    }

    // 析构：停止线程池+等待所有线程退出
    ~ThreadPool() {
        {
            lock_guard<mutex> lock(mtx);
            stop = true;
        }
        // 唤醒所有线程
        cv.notify_all();
        // 等待所有线程结束
        for (thread& worker : workers) {
            worker.join();
        }
    }

    // 禁用拷贝
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;
};