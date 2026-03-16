#include <iostream>
#include <vector>
#include <queue>
#include <random>
using namespace std;

struct TreeNode {
    int id;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : id(x), left(nullptr), right(nullptr) {}
};

vector<pair<int, int>> generate_binary_tree(int n) {
    vector<pair<int, int>> edges;
    if (n <= 0) return edges;
    
    queue<TreeNode*> q;
    TreeNode* root = new TreeNode(1);
    q.push(root);
    
    int next_id = 2;
    
    while (!q.empty() && next_id <= n) {
        TreeNode* curr = q.front();
        q.pop();
        
        // 添加左孩子
        if (next_id <= n) {
            curr->left = new TreeNode(next_id);
            edges.push_back({curr->id, next_id});
            q.push(curr->left);
            next_id++;
        }
        
        // 添加右孩子
        if (next_id <= n) {
            curr->right = new TreeNode(next_id);
            edges.push_back({curr->id, next_id});
            q.push(curr->right);
            next_id++;
        }
    }
    
    return edges;
}

int main() {
    int n = 100000;  // 节点数量
    int m = 100000;   // 查询次数
    
    cout << n << " " << m << endl;
    
    // 生成二叉树边
    vector<pair<int, int>> edges = generate_binary_tree(n);
    
    // 输出边（确保是二叉树结构）
    for (auto edge : edges) {
        cout << edge.first << " " << edge.second << endl;
    }
    
    // 输出查询
    srand(time(0));
    for (int i = 0; i < m; i++) {
        int u = rand() % n + 1;
        cout << u << endl;
    }
    
    return 0;
}