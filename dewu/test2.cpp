#include <bits/stdc++.h>
using namespace std;

// typedef long long ll;
static int a, b;

// int countsize(ll i) {
//     int size = 0;
//     while(i) {
//         i /= 10;
//         ++size;
//     }
//     return size;
// }

// // mul后得到后size位
// ll commul_size(ll a, ll b, int size) {
//     ll cutmul = a * b;
//     ll ret = 0;
//     int cnt = 0;
//     while(size--) {
//         ret += (cutmul % 10) * pow(10, cnt);
//         cutmul /= 10;
//         ++cnt;
//     }  
//     return ret;
// }

// bool isthree(ll i) {
//     int size = countsize(i);
    
//     ll cutmul = commul_size(i , i, size);
//     cutmul = commul_size(cutmul, i, size);
//     return cutmul == i;
// }

// int main() {
//     cin.tie(nullptr);
//     ios::sync_with_stdio(false);

//     cin >> a >> b;
//     int ans = 0;
//     for(ll i = a; i <= b; ++i) {
//         if(isthree(i)) {
//             cout << fixed << setprecision(2) << pow(i, 3) << "\n";
//             ++ans;
//         }
//     }
//     cout << ans << "\n";
// }


int main() {
    cin >> a >> b;
    int ans = 0;
    int arr[25] = {1, 64, 125, 216, 729, 13824, 15625, 117649, 132651
                , 421875, 438976, 970299, 1953125, 15438249, 15813251
                , 52734375, 53157376, 124251499, 125751501, 242970624
                , 244140625, 420189749, 423564751, 669921875, 997002999};
    
    for(int i = 0 ; i < 25; ++i) {
        if(arr[i] < a) continue;
        if(arr[i] > b) break;
        ++ans;
    }
    cout << ans << "\n";
}

/* 
1 200 

3
*/

/* 
1
64
125
216
729
13824
15625
117649
132651
421875
438976
970299
1953125
15438249
15813251
52734375
53157376
124251499
125751501
242970624
244140625
420189749
423564751
669921875
997002999

*/