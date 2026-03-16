#include <stack>
using namespace std;

class MyQueue {
private:
    stack<int> in_stack;  // 入队栈
    stack<int> out_stack; // 出队栈
    // 转移数据：out_stack空时，将in_stack数据移到out_stack
    void transfer() {
        if (out_stack.empty()) {
            while (!in_stack.empty()) {
                out_stack.push(in_stack.top());
                in_stack.pop();
            }
        }
    }
public:
    MyQueue() {}
    
    void push(int x) {
        in_stack.push(x);
    }
    
    int pop() {
        transfer();
        int val = out_stack.top();
        out_stack.pop();
        return val;
    }
    
    int peek() {
        transfer();
        return out_stack.top();
    }
    
    bool empty() {
        return in_stack.empty() && out_stack.empty();
    }
};