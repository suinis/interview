#include <iostream>
#include <vector>
using namespace std;

int main(){
    int n, sum = 0;
    scanf("%d", &n);
    vector<int> inputvec(n);
    vector<int> presum(n);
    for(int i = 0; i < n; ++i) {
        scanf("%d", &inputvec[i]);
        sum += inputvec[i];
        presum[i] = sum;
        // printf("%d\n", presum[i]);
    }

    int left = 0, right = 0;
    // printf("scanf返回值：%d\n", scanf("%d %d", &left, &right));
    while(scanf("%d %d", &left, &right) == 2) {
        if(left == 0) printf("%d\n", presum[right]);
        else printf("%d\n", presum[right] - presum[left - 1]);
    }
    return 0;
}