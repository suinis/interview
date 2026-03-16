#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int minlen = 0, slowindex = 0, fastindex = -1, cutsum = 0, n = nums.size();
        while(fastindex < n) {
            cout << "Current fastindex: " << fastindex << ", slowindex: " << slowindex << ", cutsum: " << cutsum << endl;
            if(cutsum < target) {
                cout << "get into if" << endl;
                if(fastindex >= n - 1) break;
                cutsum += nums[++fastindex];
                cout << "Added: " << nums[fastindex] << ", cutsum: " << cutsum << endl;
            } else {
                if(minlen == 0){
                    minlen = fastindex - slowindex + 1;
                    cout << "Initial minlen: " << minlen << endl;
                }
                else {
                    minlen = min(minlen, fastindex - slowindex + 1);
                    cout << "Updated minlen: " << minlen << endl;
                }
                
                cutsum -= nums[slowindex];
                ++slowindex;
            }
        }
        return minlen;
    }
};

int main() {
    Solution soluciton;
    vector<int> nums{1,4,4};
    cout << soluciton.minSubArrayLen(4, nums) << endl; // Output: 1
    return 0;
}