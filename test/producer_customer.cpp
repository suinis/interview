#include <bits/stdc++.h>
using namespace std;

/* 
    多生产者多消费者模型
    注意：
    1. notify_all
    2. 消费者线程中的not_empty.notify_one
    3. 消费者线程中的优雅推出
*/

// 有界队列容量
const int MAX_TASK = 5;
// 生产者 / 消费者数量
const int PRODUCER_COUNT = 2;
const int CONSUMER_COUNT = 2;
// 每个生产者生产多少个任务
const int TASKS_PER_PRODUCER = 10;
// 结束标记
const int END_FLAG = -1;

mutex mtx;
condition_variable not_full;
condition_variable not_empty;
queue<int> q;

void Producer(int id) {
    for (int i = 0; i < TASKS_PER_PRODUCER; ++i) {
        unique_lock<mutex> lock(mtx);
        // 队列满了就等
        not_full.wait(lock, [] { return q.size() < MAX_TASK; });
        int task = id * 100 + i;  // 区分不同生产者的任务
        q.push(task);
        cout << "producer " << id << " produce: " << task << endl;
        lock.unlock();
        not_empty.notify_one();   // 唤醒一个消费者
    }
}

void Consumer(int id) {
    while (true) {
        unique_lock<mutex> lock(mtx);
        // 队列空就等
        not_empty.wait(lock, [] { return !q.empty(); });
        int val = q.front();
        q.pop();
        if (val == END_FLAG) {    // 收到结束标记，退出
            cout << "consumer " << id << " exit." << endl;
            lock.unlock();
            // 主线程会为每个消费者各放一个结束标记
            not_empty.notify_one();  // 继续唤醒其他可能在等的消费者
            break;
        }
        cout << "consumer " << id << " use: " << val << endl;
        lock.unlock();
        not_full.notify_one();    // 唤醒一个生产者
    }
}

int main() {
    vector<thread> producers;
    vector<thread> consumers;

    // 启动多个消费者
    for (int i = 0; i < CONSUMER_COUNT; ++i) {
        consumers.emplace_back(Consumer, i + 1);
    }

    // 启动多个生产者
    for (int i = 0; i < PRODUCER_COUNT; ++i) {
        producers.emplace_back(Producer, i + 1);
    }

    // 等所有生产者结束
    for (auto& t : producers) t.join();

    // 所有任务都生产完后，投递结束标记，让消费者优雅退出
    {
        unique_lock<mutex> lock(mtx);
        for (int i = 0; i < CONSUMER_COUNT; ++i) {
            // 如果队列已满，等空间
            not_full.wait(lock, [] { return q.size() < MAX_TASK; });
            q.push(END_FLAG);
        }
    }
    not_empty.notify_all();  // 唤醒所有消费者，让他们拿到结束标记退出

    // 等所有消费者结束
    for (auto& t : consumers) t.join();

    return 0;
}