
#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <vector>
#include <thread>

std::shared_mutex mtx;
int sharednum = 0;

void readTask(int id) {
    /* 
        shared_lock只能封装shared_mutex/shared_timed_mutex，这种读写锁
        且只用与读锁，写锁用unique_lock封装
    */
    std::shared_lock<std::shared_mutex> lock(mtx); 
    std::cout << "thread" <<  id << "get sharednum : " << sharednum << std::endl;
}

void writeTask(int id, int num) {
    // unique_lock可以封装mutex、timed_mutex、shared_mutex等
    std::unique_lock<std::shared_mutex> lock(mtx);
    sharednum = num;
    std::cout << "thread" << id << "write sharednum : " << sharednum << std::endl;
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