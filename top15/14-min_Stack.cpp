#include <stack>
using namespace std;

class MinStack {
private:
    stack<int> data_stack; // 数据栈
    stack<int> min_stack;  // 辅助栈：保存当前最小值
public:
    MinStack() {}
    
    void push(int val) {
        data_stack.push(val);
        // 辅助栈为空，或当前值<=栈顶（重复最小值也要入栈）
        if (min_stack.empty() || val <= min_stack.top()) {
            min_stack.push(val);
        }
    }
    
    void pop() {
        if (data_stack.top() == min_stack.top()) {
            min_stack.pop();
        }
        data_stack.pop();
    }
    
    int top() {
        return data_stack.top();
    }
    
    int getMin() {
        return min_stack.top();
    }
};