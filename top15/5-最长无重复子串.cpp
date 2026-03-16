#include <string>
#include <unordered_map>
using namespace std;

int lengthOfLongestSubstring(string s) {
    unordered_map<char, int> map; // 字符->最新下标
    int left = 0, maxLen = 0;
    for (int right = 0; right < s.size(); ++right) {
        if (map.count(s[right]) && map[s[right]] >= left) {
            left = map[s[right]] + 1; // 左边界右移，排除重复
        }
        map[s[right]] = right;
        maxLen = max(maxLen, right - left + 1);
    }
    return maxLen;
}