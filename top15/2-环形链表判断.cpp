bool hasCycle(ListNode *head) {
    if (head == nullptr || head->next == nullptr) return false;
    ListNode* slow = head;
    ListNode* fast = head->next; // 初始错开，避免直接相等
    while (slow != fast) {
        if (fast == nullptr || fast->next == nullptr) return false;
        slow = slow->next;       // 慢指针走1步
        fast = fast->next->next; // 快指针走2步
    }
    return true;
}