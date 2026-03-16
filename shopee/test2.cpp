#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    /**
     * Note: 类名、方法名、参数名已经指定，请勿修改
     *
     * 
     * 
     * @param source_string string字符串  给定的一个列表，只包含整数，如"[3,5,7,1,9]"
     * @return string字符串
     */

    using ll = long long;

    int myQuickSortInner(vector<ll>& input, int left, int right) {
        int shaonum = input[left];
        while (left < right) {
            while(left < right && input[right] >= shaonum) --right;
            input[left] = input[right];

            while(left < right && input[left] <= shaonum) ++left;
            input[right] = input[left];
        }
        input[left] = shaonum;

        return left;
    }

    void myQuickSort(vector<ll>& input, int left, int right) {
        while(left < right) {
            ll shao = myQuickSortInner(input, left, right);
            myQuickSort(input, left, shao - 1);
            myQuickSort(input, shao + 1, right);
            return;
        }
    }
    
    string sort_by_num(string source_string) {
        // write code here
        source_string.pop_back();
        source_string.erase(0, 1);

        stringstream ss(source_string);
        string num;
        vector<ll> input;
        input.reserve(100000);
        while(getline(ss, num, ',')) {
            input.push_back(stoll(num));
        }

        myQuickSort(input, 0, input.size() - 1);

        // for(int i = 0; i < input.size(); ++i) {
        //     cout << input[i] << " ";
        // }
        string ret = "[";
        for(int i = 0; i < input.size() - 1; ++i) {
            ret += to_string(input[i]) + ',';
        }
        ret += to_string(input.back()) + "]";

        return ret;
    }
};

int main() {
    Solution sol;
    cout << sol.sort_by_num("[3,5,7,1,9]") << "\n";
}

// string nexts = source_string;
// int cnt = 6;
// while(cnt--) {
//     int index = nexts.find(',');
//     string cuts = nexts.substr(0, index);
//     cout << cuts << "  ";
//     nexts = nexts.substr(index + 1);
//     cout << nexts << "\n";
//     if(nexts.empty()) break;
// }

// static void myQuickSort(vector<ll>& input) {
    //     for(int i = 0; i < input.size() - 1; ++i) {
    //         ll cutmin = input[i];
    //         int cutminindex = i;
    //         for(int j = i + 1; j < input.size(); ++j) {
    //             if(input[j] < cutmin) {
    //                 cutmin = input[j];
    //                 cutminindex = j;
    //             }
    //         }
    //         swap(input[i], input[cutminindex]);
    //     }
    // }