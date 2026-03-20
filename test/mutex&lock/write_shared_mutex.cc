
#include <atomic>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <vector>
#include <thread>
std::shared_mutex mtx;
std::mutex cnt_mutex;
// 如果不想要手写条件变量+互斥锁封装，可以用C++20的atomic::wait/notify_one/notify_all
/* 
    std::atomic<int> writeThreadCnt{0};

    // 读线程
    void readTask(int id) {
        while (writeThreadCnt.load(std::memory_order_acquire) > 0) {
            writeThreadCnt.wait(1);  // 等待值变化
        }
        // 然后再去拿 shared_mutex 的共享锁
    }

    // 写线程
    void writeTask(...) {
        writeThreadCnt.fetch_add(1, std::memory_order_acq_rel);
        // 独占写...
        writeThreadCnt.fetch_sub(1, std::memory_order_acq_rel);
        writeThreadCnt.notify_all();
    }
*/

// 或者
/* 
    要么 自旋 busy-wait：
        反复 while (writeThreadCnt.load() > 0) { }  : CPU 空转浪费性能；
    要么用 sleep 轮询：
        while (writeThreadCnt.load() > 0) std::this_thread::sleep_for(...); 响应变慢且不精确。
*/
std::condition_variable can_read;
int writeThreadCnt = 0;
int shared_num = 0;

void readTask(int id) {
    {
        std::unique_lock<std::mutex> lock1(cnt_mutex);
        can_read.wait(lock1, [](){ return writeThreadCnt == 0; });
    }
    std::shared_lock<std::shared_mutex> lock2(mtx);
    std::cout << "thread" << id << " read shared_num : " << shared_num << std::endl; 
}

void writeTask(int id, int num) {
    {
        std::lock_guard<std::mutex> lock1(cnt_mutex);
        writeThreadCnt++;
    }
    
    std::unique_lock<std::shared_mutex> lock2(mtx);
    shared_num = num;
    std::cout << "thread" << id << "write shared_num : " << shared_num << std::endl;

    {
        std::lock_guard<std::mutex> lock1(cnt_mutex);
        writeThreadCnt--;
        can_read.notify_all();
    }
}

int main() {
    std::vector<std::thread> ths;
    ths.emplace_back(readTask, 0);
    ths.emplace_back(readTask, 1);
    ths.emplace_back(writeTask, 2, 100);
    ths.emplace_back(readTask, 3);
    ths.emplace_back(readTask, 4);
    ths.emplace_back(readTask, 5);
    ths.emplace_back(readTask, 6);
    ths.emplace_back(readTask, 7);
    ths.emplace_back(readTask, 8);

    for(auto& th : ths) th.join();
}