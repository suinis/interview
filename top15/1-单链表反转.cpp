struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

ListNode* reverseList(ListNode* head) {
    ListNode* pre = nullptr;
    ListNode* cur = head;
    while (cur != nullptr) {
        ListNode* next = cur->next; // 保存下一个节点，避免断链
        cur->next = pre;            // 反转当前节点指针
        pre = cur;                  // pre指针后移
        cur = next;                 // cur指针后移
    }
    return pre; // 最终pre指向新头节点
}