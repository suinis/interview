#include <vector>
#include <stack>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

vector<int> inorderTraversal(TreeNode* root) {
    vector<int> res;
    stack<TreeNode*> st;
    TreeNode* cur = root;
    while (cur != nullptr || !st.empty()) {
        // 遍历左子树
        while (cur != nullptr) {
            st.push(cur);
            cur = cur->left;
        }
        // 访问根节点
        cur = st.top();
        st.pop();
        res.push_back(cur->val);
        // 遍历右子树
        cur = cur->right;
    }
    return res;
}