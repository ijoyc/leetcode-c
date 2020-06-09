/*
 * Created Date: Monday June 8th 2020
 * Author: yizhuoc
 */

#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode *removeNthFromEnd(struct ListNode *head, int n) {
    if (!head) {
        return NULL;
    }

    struct ListNode *p = head;
    struct ListNode *q = head;
    for (int i = 0; i < n; i++) {
        p = p->next;
        if (!p) {
            q = head->next;
            free(head);
            return q;
        }
    }

    p = p->next;
    while (p) {
        p = p->next;
        q = q->next;
    }
    p = q->next;
    q->next = p->next;
    free(p);
    return head;
}