/*
 * Created Date: Wednesday June 10th 2020
 * Author: yizhuoc
 */

#include <stdlib.h>
#include <limits.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

typedef struct {
    struct ListNode **nodes;
    int size;
} PriorityQueue;

PriorityQueue *NewQueue(int size) {
    PriorityQueue *queue = (PriorityQueue *)malloc(sizeof(PriorityQueue));
    queue->size = 0;
    queue->nodes = malloc(sizeof(struct ListNode *) * (size + 1));
    return queue;
}

void MinHeapify(PriorityQueue *queue, int index) {
    int left = index << 1;
    int right = left + 1;
    int min = index;
    if (left <= queue->size && queue->nodes[index]->val > queue->nodes[left]->val) {
        min = left;
    }
    if (right <= queue->size && queue->nodes[min]->val > queue->nodes[right]->val) {
        min = right;
    }
    if (min != index) {
        struct ListNode *tmp = queue->nodes[index];
        queue->nodes[index] = queue->nodes[min];
        queue->nodes[min] = tmp;

        MinHeapify(queue, min);
    }
}

struct ListNode *ExtractMin(PriorityQueue *queue) {
    struct ListNode *node = queue->nodes[1];
    queue->nodes[1] = queue->nodes[queue->size];
    queue->size--;
    MinHeapify(queue, 1);
    return node;
}

void DecreaseKey(PriorityQueue *queue, int index, int val) {
    if (val > queue->nodes[index]->val) {
        printf("error: cannot assign a bigger key to node %d which has value %d\n", index, queue->nodes[index]->val);
        return;
    }
    queue->nodes[index]->val = val;
    int parent;
    while (index > 1 && queue->nodes[(parent = index >> 1)]->val > queue->nodes[index]->val) {
        struct ListNode *tmp = queue->nodes[index];
        queue->nodes[index] = queue->nodes[parent];
        queue->nodes[parent] = tmp;
        index = parent;
    }
}

void Insert(PriorityQueue *queue, struct ListNode *node) {
    queue->size++;
    int original = node->val;
    node->val = INT_MAX;
    queue->nodes[queue->size] = node;
    DecreaseKey(queue, queue->size, original);
}

struct ListNode *mergeKLists(struct ListNode **lists, int listsSize) {
    PriorityQueue *queue = NewQueue(listsSize);
    for (int i = 0; i < listsSize; i++) {
        if (lists[i]) {
            Insert(queue, lists[i]);
        }
    }
    struct ListNode *head = NULL;
    struct ListNode *p = NULL;
    while (queue->size) {
        struct ListNode *min = ExtractMin(queue);
        
        struct ListNode *q = malloc(sizeof(struct ListNode));
        q->val = min->val;
        q->next = NULL;
        if (p) {
            p->next = q;
        }
        p = q;
        
        if (!head) {
            head = p;
        }
        if (min->next) {
            Insert(queue, min->next);
        }
    }
    return head;
}