/*
 * Created Date: Friday June 12th 2020
 * Author: yizhuoc
 */

#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

int isListLessThanK(struct ListNode *node, int k) {
    int i = 0;
    for (struct ListNode *p = node; p; p = p->next) {
        i++;
    }
    return i < k;
}

struct ListNode *reverseK(struct ListNode *node, int k, struct ListNode **next, struct ListNode **first, int *isLast) {
    if (!node || k <= 1 || isListLessThanK(node, k)) {
        *next = NULL;
        *first = node;
        *isLast = 0;
        return node;
    }

    struct ListNode *prev = node;
    struct ListNode *p = node->next;
    for (int i = 1; i < k; i++) {
        struct ListNode *next = p->next;
        p->next = prev;
        prev = p;
        p = next;
    }

    *next = p;
    *first = prev;
    *isLast = p == NULL;
    return node;
}

struct ListNode *reverseKGroup(struct ListNode *head, int k) {
    struct ListNode *node = NULL;
    struct ListNode *next = head;
    struct ListNode *first = NULL;
    int isLast = 0;

    while (next) {
        struct ListNode *p = reverseK(next, k, &next, &first, &isLast);
        if (node) {
            node->next = first;
        } else {
            head = first;
        }
        node = p;
    }
    if (node && isLast) {
        node->next = NULL;
    }

    return head;
}