#include <bits/stdc++.h>
#include <cstdlib>
#include <ctime>
using namespace std;

int partition(vector<int>& nums, int left, int right) {
    // 随机选 pivot，与 left 交换，后续仍以 nums[left] 为基准
    int randIdx = left + rand() % (right - left + 1);
    swap(nums[left], nums[randIdx]);
    int pivot = nums[left];      // 基准值
    int l = left, r = right;
    while (l < r) {              // 双重 while 版本
        // 先从右侧开始
        while (l < r && nums[r] >= pivot) --r;
        nums[l] = nums[r];
        while (l < r && nums[l] <= pivot) ++l;
        nums[r] = nums[l];
    }
    nums[l] = pivot;
    return l;
}

void quickSort(vector<int>& nums, int left, int right) {
    if(left >= right) return;

    int p = partition(nums, left, right);
    quickSort(nums, left, p - 1);
    quickSort(nums, p + 1, right);
}


int main() {
    srand((unsigned)time(nullptr));  // 随机种子，每次运行不同
    vector<int> in {4, 1, 3, 5,2, 3, 7, 0, 10, 8};
    quickSort(in, 0, in.size() - 1);
    for_each(in.begin(), in.end(), [](int elem){cout << elem << " ";});
}
// 4 1 3 5 2