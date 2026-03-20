// n 个线程交替打印，共推进 m 次（0..m-1）
// 题目「不加锁」：指业务协调（轮次）用 atomic + CAS，不用 mutex 控制 turn。
// 或单线程打印（见下文注释）。
#include <atomic>
#include <cstdio>
#include <iostream>
#include <thread>
#include <vector>

const int N = 10;  // 线程数
const int M = 15;  // 总打印次数

std::atomic<int> turn{0};

void workthread(int id) {
    while (true) {
        int curr = turn.load(std::memory_order_acquire);
        if (curr >= M) {
            break;
        }
        // 只有「当前轮到」的线程尝试把 turn 从 curr 推进到 curr+1
        if (curr % N != id) {
            std::this_thread::yield();
            continue;
        }
        int nxt = curr + 1;
        if (turn.compare_exchange_strong(curr, nxt)) {
            // CAS 成功：本轮一定由本线程独占推进
            std::cout << "thread " << id << " (step " << curr << ")\n";
        }
        // CAS 失败：curr 已被写成最新值，下一轮重试
    }
}

int main() {
    std::vector<std::thread> ths;
    for (int i = 0; i < N; ++i) {
        ths.emplace_back(workthread, i);
    }
    for (auto& th : ths) {
        th.join();
    }
    return 0;
}
