#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

     // 每行按照;分割
        // 再分别按照 分割
        // left为int ，
            // 再按照,分割
            // 判断等号左侧已存在 || 右侧不存在，是则改行过滤，否则插入
        // left不为int，
            // 再按照,分割
            // 判断等号左侧不存在 || 右侧不存在，是则改行过滤，否则插入

    int loop;
    cin >>loop;
    cin.ignore();
    while(loop--) {
        string s;
        getline(cin, s);
        // cout << s << "\n";

        bool countthis = true;
        // 判断是否计算本行
        int fenindex = 0;
        string nexts = s;
        // cout << nexts << "\n";
        while(1) {
            fenindex = nexts.find(';');
            // cout << fenindex << "\n";
            string cuts = nexts.substr(0, fenindex + 1);

            // cout << cuts << "\n";
            

            nexts = nexts.substr(fenindex + 1);
            if(nexts.empty()) break;;
        }

        // 计算
    }
}

/* 
6
int a=1,b;
int c=a,d=b;e=a;
b=3;int c=b;
int e;
int f=d;
int g=h,h;

a 1
b 3
c 3
e undefined
*/

// #include <bits/stdc++.h>
// using namespace std;

// int main() {
//     cin.tie(nullptr);
//     ios::sync_with_stdio(false);


// }