/* 
    堆排序思考流程：
    1. 理解堆定义：数组形式的完全二叉树
    2. heapinsert：插入数据（上滤）
    3. heapify：取出数据（下渗）// 如果只是单纯的获取最大值，则无需调整
    4. 如果有修改堆中数据的要求：记住堆排序的核心，判断新值跟旧值得大小，根据大小关系决定核心操作

    堆排序最核心的点就是：heapinsert上滤，heapify下渗

    时间复杂度：O(N * logN) 
    空间复杂度：O(1)
    不稳定
*/

#include <algorithm>
#include <bits/stdc++.h>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

void heapinsert(vector<int>& in, int index) {
    // (0 - 1) / 2 == 0， (0 - 1) >> 1 == -1 ，注意！
    // 到顶index[0] > index[(0 - 1) / 2] 不成立，必定退出，可以不必加index == 0条件
    while(in[index] > in[(index - 1) / 2]) {
        swap(in[index], in[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

// 4 7 7 5 4 3 6 2 | 45
// 2 4 7 5 4 3 6 7 | 45
void heapify(vector<int>& in, int index, int heapsize) {
    int left = 2 * index + 1;
    while(left < heapsize) {
        int largest_index = ((left + 1 < heapsize) && (in[left + 1] > in[left])) ? left + 1 : left;
        largest_index = (in[largest_index] > in[index]) ? largest_index : index;

        if(largest_index == index) break;
        swap(in[index], in[largest_index]); // 
        index = largest_index;
        left = 2 * index + 1;
    }
}

void heapSort(vector<int>& in) {
    int heapsize = in.size();

    // 1. 用上滤构造大根堆
    // for(int i = 0; i < in.size(); ++i) {
    //     heapinsert(in, i);
    // }

    // 2. 直接用下渗调整大根堆 （更快一点）
    {
        for(int i = in.size() - 1; i >= 0; --i) {
            heapify(in, i, in.size());
        }
    }

    swap(in[0], in[--heapsize]);
    while(heapsize > 1) {        
        heapify(in, 0, heapsize);
        swap(in[0], in[--heapsize]);
    }
}

int main() {
    vector<int> in {2,3,4,5,6,7,7,45,4};
    heapSort(in);
    for_each(in.begin(), in.end(), [](int num){
        cout << num << " ";
    });
    cout << endl;

    // cout << ((0 - 1) >> 1) << endl;
}