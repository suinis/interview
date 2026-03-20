#include <bits/stdc++.h>
#include <chrono>
#include <csignal>
#include <ctime>
#include <mutex>
#include <thread>
using namespace std;

timed_mutex mtx;

void task_with_timeout(int id) {
    // unique_lock配合timed_mutex实现超时等待
    unique_lock<timed_mutex> lock(mtx, defer_lock);

    if(lock.try_lock_for(chrono::seconds(1))) {
        cout << "get timed_mutex success" << endl;
        this_thread::sleep_for(chrono::milliseconds(2000));
        cout << id << " done" << endl;
        lock.unlock();
        cout << "unlock in advance" << endl;
    } else {
        cout << "get time_mutex failed" << endl;
    }
}

int main() {
    vector<thread> ths;
    auto start = chrono::steady_clock::now();
    for(int i = 0; i < 2; ++i) {
        ths.emplace_back(task_with_timeout, i);
    }

    for(int i = 0; i < 2; ++i) {
        ths[i].join();
    }
    
    auto end = chrono::steady_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "total time: " << duration << " ms" << endl;
}