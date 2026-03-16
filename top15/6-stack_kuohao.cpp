#include <string>
#include <stack>
using namespace std;

bool isValid(string s) {
    stack<char> st;
    for (char c : s) {
        if (c == '(' || c == '[' || c == '{') {
            st.push(c);
        } else {
            if (st.empty()) return false; // 右括号多余
            char top = st.top();
            st.pop();
            if ((c == ')' && top != '(') || 
                (c == ']' && top != '[') || 
                (c == '}' && top != '{')) {
                return false; // 括号不匹配
            }
        }
    }
    return st.empty(); // 左括号多余
}