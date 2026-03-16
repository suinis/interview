/* 
    priority_queue优先队列，可以理解为黑盒的堆排序：对外提供push/pop方法，不允许任意修改堆结构
    
    对于有修改堆中数据，（需要调整堆结构）的需求，就需要自己实现堆，不要用priority_queue。
*/

#include <bits/stdc++.h>
#include <functional>
#include <queue>
#include <vector>
using namespace std;

int main() {
    vector<int> in{0, 4,6, 3, 1, 0 ,9, 3, 6};
    priority_queue<int, vector<int>, greater<int>> prique;
    for(int num : in) {
        prique.emplace(num);
    }
    while(!prique.empty()) {
        cout << prique.top() << " ";
        prique.pop();
    }
}