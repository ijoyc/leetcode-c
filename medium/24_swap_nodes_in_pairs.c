/*
 * Created Date: Friday June 12th 2020
 * Author: yizhuoc
 */

#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode *swapPairs(struct ListNode *head) {
    if (!head) {
        return NULL;
    }
    struct ListNode *p = head;
    struct ListNode *q = p->next;
    head = q ? q : p;
    while (p && q) {
        struct ListNode *r = q->next;
        p->next = (r && r->next) ? r->next : r;
        q->next = p;
        p = r;
        if (r) {
            q = r->next;
        }
    }
    return head;
}