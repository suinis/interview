/* 
    归并排序变种：小和
    其他变种：逆序对数
*/
#include <algorithm>
#include <bits/stdc++.h>
#include <vector>
using namespace std;

// 1112226   1112234457
int myMerge(vector<int>& in, int l, int m, int mr, int r) {
    vector<int> tmp(r - l + 1);
    int ts = 0, s = l, res = 0;
    while(l <= m && mr <= r) {
        // if(in[l] == in[mr]) tmp[ts++] = in[mr++];
        // else if(in[l] < in[mr]) {
        //     res += (r - mr + 1) * in[l];
        //     tmp[ts++] = in[l++];
        // } else {
        //     tmp[ts++] = in[mr++];
        // }
        res += (in[l] < in[mr]) ? (r - mr + 1) * in[l] : 0;
        tmp[ts++] = (in[l] < in[mr]) ? in[l++] : in[mr++]; // 注意这里跟mergeSort.cc的区别，是'<'
        // in[l] == in[mr]时,要先取右侧的，如[1112226] 和 [1112234457]
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
    return res;
}

int process(vector<int>& in, int l, int r) {
    if(l == r) return 0;
    int mid = l + ((r - l) >> 1);
    return process(in, l, mid) + 
    process(in, mid + 1, r) + 
    myMerge(in, l, mid, mid + 1, r);
}

void smallSum(vector<int>& in) {
    int smallsum = process(in, 0, in.size() - 1);
    cout << smallsum << endl;
}

int main() {
    vector<int> in {1, 1, 5};
    smallSum(in);
    for(auto& num : in) {
        cout << num << " ";
    }
    cout << endl;
}