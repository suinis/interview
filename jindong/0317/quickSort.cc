
#include <bits/stdc++.h>
using namespace std;

int partition(vector<int>& in, int l ,int r) {
    int randIdx = l + rand() % (r - l + 1);
    swap(in[l], in[randIdx]);
    int pivot = in[l];
    while(l < r ){
        while(l < r && in[r] >= pivot) --r;
        in[l] = in[r];
        while(l < r && in[l] <= pivot) ++l;
        in[r] = in[l];
    }
    in[l] = pivot;
    return l;
}

void quick_sort(vector<int>& in, int left, int right) {
    if(left > right) return;

    int index = partition(in, left, right);
    quick_sort(in, left, index - 1);
    quick_sort(in, index + 1, right);
}

int main() {
    srand((unsigned)time(nullptr));
    vector<int> in {2,3,4,5,5,54,345,45};
    quick_sort(in, 0, in.size() - 1);
    for_each(in.begin(), in.end(), [](int num){cout << num << " ";});
    cout << endl;
}