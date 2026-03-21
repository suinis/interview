#include <bits/stdc++.h>
using namespace std;

// LeetCode 33：搜索旋转排序数组（元素互不相同）
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int l = 0, r = (int)nums.size() - 1;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (nums[mid] == target) return mid;

            if (nums[l] <= nums[mid]) {
                // 左段 [l, mid] 单调递增
                if (nums[l] <= target && target < nums[mid]) r = mid - 1;
                else l = mid + 1;
            } else {
                // 右段 [mid, r] 单调递增（断点在左侧）
                if (nums[mid] < target && target <= nums[r]) l = mid + 1;
                else r = mid - 1;
            }
        }
        return -1;
    }
};

#ifdef LOCAL
int main() {
    Solution sol;
    vector<int> a = {4, 5, 6, 7, 0, 1, 2};
    assert(sol.search(a, 0) == 4);
    assert(sol.search(a, 3) == -1);
    vector<int> b = {1};
    assert(sol.search(b, 0) == -1);
    assert(sol.search(b, 1) == 0);
    vector<int> c = {3, 1};
    assert(sol.search(c, 1) == 1);
    cout << "ok\n";
    return 0;
}
#endif
