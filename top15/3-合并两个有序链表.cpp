ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    ListNode dummy(0); // 哑节点，避免头节点处理逻辑
    ListNode* cur = &dummy;
    while (list1 != nullptr && list2 != nullptr) {
        if (list1->val < list2->val) {
            cur->next = list1;
            list1 = list1->next;
        } else {
            cur->next = list2;
            list2 = list2->next;
        }
        cur = cur->next;
    }
    // 拼接剩余节点
    cur->next = list1 != nullptr ? list1 : list2;
    return dummy.next;
}