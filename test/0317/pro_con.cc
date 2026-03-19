#include <bits/stdc++.h>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <thread>
#include <vector>
using namespace std;

struct Task {
    string msg;              // 要打印的内容（与执行解耦）
    function<void()> work;   // 任务实际工作（可选）
};

queue<Task> taskqueue;
condition_variable not_full, not_empty;
mutex mtx;
const int loop = 10;
const int maxcnt = 5;
const int producercnt = 2;
const int consumercnt = 2;

// 严格按“出队(pop)顺序”打印
mutex print_mtx;
size_t pop_seq = 0;
size_t next_seq_to_print = 0;
unordered_map<size_t, string> pending_print;

static void publish_and_print_in_order(size_t seq, string out) {
    lock_guard<mutex> lk(print_mtx);
    pending_print.emplace(seq, std::move(out));
    while (true) {
        auto it = pending_print.find(next_seq_to_print);
        if (it == pending_print.end()) break;
        cout << it->second << flush;
        pending_print.erase(it);
        ++next_seq_to_print;
    }
}

void producer(int id) {
    for(int i = 0; i < loop; ++i) {
        unique_lock<mutex> lock(mtx);
        not_full.wait(lock, [](){return taskqueue.size() < maxcnt;});
        Task t;
        t.msg = "produce" + to_string(id) + " task : " + to_string(i) + "\n";
        t.work = []() {};
        taskqueue.emplace(std::move(t));
        lock.unlock();
        not_empty.notify_one();
    }
}

void consumer(int id) {
    while(true) {
        unique_lock<mutex> lock(mtx);
        not_empty.wait(lock, [](){return !taskqueue.empty();});
        Task t = std::move(taskqueue.front());
        taskqueue.pop();
        size_t my_seq = pop_seq++;
        lock.unlock();
        not_full.notify_one();
        // 放在unlock,notify_one之后执行，
        t.work();

        string out;
        out.reserve(t.msg.size() + 64);
        out += t.msg;
        out += "consumer" + to_string(id) + " running\n\n";
        publish_and_print_in_order(my_seq, std::move(out));
    }
}

int main() {
    vector<thread> producers;
    vector<thread> consumers;
    for(int i = 0; i < producercnt; ++i) {
        producers.emplace_back(producer, i);
    }

    for(int i = 0; i < consumercnt; ++i) {
        consumers.emplace_back(consumer, i);
    }

    for(auto& thread : producers) thread.join();

    for(auto& thread : consumers) thread.join();
} 