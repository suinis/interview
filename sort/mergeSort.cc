/* 
    master函数简单计算时间复杂度：
        a：次数
        b：几块相同的子问题
        d：每层的额外时间复杂度
        T(N) = a * T(N/b) + O(N^d)
        当log(b, a) < d：O(N^d)
        当log(b, a) == d：O(N^d * logN)
        当log(b, a) > d：O(N^log(b, a))
    归并排序为什么快：主要是可以理解做了记忆

    时间复杂度：O(N * logN)
    空间复杂度：O(N)
    稳定
*/

#include <algorithm>
#include <bits/stdc++.h>
#include <vector>
using namespace std;

void myMerge(vector<int>& in, int l, int m, int mr, int r) {
    vector<int> tmp(r - l + 1); // 额外空间O(N)
    int ts = 0, s = l;
    while(l <= m && mr <= r) {
        tmp[ts++] = (in[l] <= in[mr]) ? in[l++] : in[mr++];
    }
    while(l <= m) {
        tmp[ts++] = in[l++];
    }
    while (mr <= r) {
        tmp[ts++] = in[mr++];
    }
    for(int i= 0 ; i < tmp.size(); ++i) {
        in[s++] = tmp[i];
    }
}

void mergeSort(vector<int>& in, int l, int r) {
    if(l == r) return;
    int mid = l + ((r - l) >> 1);
    mergeSort(in, l, mid);
    mergeSort(in, mid + 1, r);
    myMerge(in, l, mid, mid + 1, r);
}

int main() {
    vector<int> in {0, 1, 5, 3, 5, 1, 2, 1, 7, 2, 9};
    mergeSort(in, 0, in.size() - 1);
    for(auto& num : in) {
        cout << num << " ";
    }
    cout << endl;
}