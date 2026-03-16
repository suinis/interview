#include <bits/stdc++.h>

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

ListNode* reverseList(ListNode* head) {
    ListNode* pre = nullptr;
    ListNode* cur = head;
    while(cur != nullptr) {
        ListNode* next = cur->next;
        cur->next = pre;
        pre = cur;
        cur = next;
    }
    return pre;
}