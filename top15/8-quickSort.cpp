/* 
    swap的快排方法
    1.0 ： 给一个数a，根据这个数把数组分为<a，和>a两部分 
    2.0 ： 末尾选定一个数a，把数组分为<a、==a、>a，三部分 // 这样可以把partition定为[left, right]==a的区域，可以进一步缩短时间
    3.0 ： 随机选定数组中值跟末尾值交换，再执行2.0，// 引入随机值[会导致每种可能的情况（最坏、一般）概率都为1/n]根据数学证明，可得到时间复杂度为O(N * logN)

    时间复杂度：O(N * logN) 
    空间复杂度：O(logN) 递归栈深度
    不稳定
*/

#include <vector>
#include <random>
using namespace std;

// 分区函数
int partition(vector<int>& nums, int left, int right) {
    // 随机选基准，避免有序数组最坏情况
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(left, right);
    int pivotIdx = dis(gen);
    swap(nums[pivotIdx], nums[left]);
    
    int pivot = nums[left];
    int l = left + 1, r = right;
    while (l <= r) {
        if (nums[l] > pivot && nums[r] < pivot) {
            swap(nums[l], nums[r]);
            l++; r--;
        }
        if (nums[l] <= pivot) l++;
        if (nums[r] >= pivot) r--;
    }
    swap(nums[left], nums[r]);
    return r;
}

void quickSort(vector<int>& nums, int left, int right) {
    if (left >= right) return;
    // 小数据量用插入排序，提升性能
    if (right - left < 10) {
        for (int i = left + 1; i <= right; ++i) {
            int val = nums[i];
            int j = i - 1;
            while (j >= left && nums[j] > val) {
                nums[j+1] = nums[j];
                j--;
            }
            nums[j+1] = val;
        }
        return;
    }
    int p = partition(nums, left, right);
    quickSort(nums, left, p - 1);
    quickSort(nums, p + 1, right);
}