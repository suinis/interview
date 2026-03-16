#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
using namespace std;

const int MAX_QUEUE = 5;
queue<int> q;
mutex mtx;
condition_variable cv_pro;
condition_variable cv_con;

void producer(int id) {
    for (int i = 0; i < 10; ++i) {
        unique_lock<mutex> lock(mtx);
        // 队列满，等待消费者
        cv_pro.wait(lock, [](){ return q.size() < MAX_QUEUE; });
        q.push(i);
        cout << "生产者" << id << "生产：" << i << endl;
        lock.unlock(); // 为了在通知其他消费者线程前先释放锁
        cv_con.notify_one(); // 通知消费者
    }
}

void consumer(int id) {
    for (int i = 0; i < 10; ++i) {
        unique_lock<mutex> lock(mtx);
        // 队列空，等待生产者
        cv_con.wait(lock, [](){ return !q.empty(); });
        int val = q.front();
        q.pop();
        cout << "消费者" << id << "消费：" << val << endl;
        lock.unlock();
        cv_pro.notify_one(); // 通知生产者
    }
}

int main() {
    thread p1(producer, 1);
    thread c1(consumer, 1);
    p1.join();
    c1.join();
    return 0;
}