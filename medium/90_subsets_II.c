/*
* @Author: chenyizhuo.yizhuoc
* @Date:   2020-12-03 18:35:04
* @Last Modified by:   chenyizhuo.yizhuoc
* @Last Modified time: 2020-12-04 11:03:43
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct Node {
	int value;
	struct Node *next;
} Node;

typedef struct List {
	Node *head;
	int size;
} List;

List *NewList() {
	List *list = (List *)malloc(sizeof(List));
	list->size = 0;
	list->head = NULL;
	return list;
}

void ListAdd(List *list, int value) {
	Node *node = (Node *)malloc(sizeof(Node));
	node->value = value;
	node->next = list->head;
	list->head = node;
	list->size++;
}

List *CopyList(List *l) {
	List *list = NewList();
	Node *p = l->head;
	while (p) {
		ListAdd(list, p->value);
		p = p->next;
	}
	return list;
}

int *ListToArray(List *list) {
	int *nums = (int *)malloc(sizeof(int) * list->size);
	Node *p = list->head;
	for (int i = 0; i < list->size; i++) {
		nums[i] = p->value;
		p = p->next;
	}
	return nums;
}

typedef struct LList {
	List **lists;
	int size;
	int capacity;
} LList;

LList *NewLList(int capacity) {
	LList *llist = (LList *)malloc(sizeof(LList));
	llist->size = 0;
	llist->capacity = capacity;
	llist->lists = (List **)malloc(sizeof(List *) * capacity);
	for (int i = 0; i < capacity; i++) {
		llist->lists[i] = NULL;
	}
	return llist;
}

void LListAdd(LList *llist, List *value) {
	if (llist->size == llist->capacity) {
		int newCapacity = llist->capacity * 2;
		llist->lists = (List **)realloc(llist->lists, sizeof(List *) * newCapacity);
		llist->capacity = newCapacity;
	}
	llist->lists[llist->size++] = value;
}

int cmp(const void *n1, const void *n2) {
	return *(int *)n1 - *(int *)n2;
}

int **subsetsWithDup(int *nums, int numsSize, int *returnSize, int **returnColumnSizes) {
	int count = pow(2, numsSize);
	int **result = (int **)malloc(sizeof(int *) * count);
	int *columnSizes = (int *)malloc(sizeof(int) * count);
	
	qsort(nums, numsSize, sizeof(int), cmp);
	LList *llist = NewLList(count);
	LListAdd(llist, NewList());

	int start = 0;
	int end = 0;
	for (int i = 0; i < numsSize; i++) {
		start = 0;
		if (i > 0 && nums[i] == nums[i - 1]) {
			start = end + 1;
		}
		end = llist->size - 1;
		for (int j = start; j <= end; j++) {
			List *newList = CopyList(llist->lists[j]);
			ListAdd(newList, nums[i]);
			LListAdd(llist, newList);
		}
	}

	*returnSize = llist->size;
	for (int i = 0; i < llist->size; i++) {
		List *list = llist->lists[i];
		result[i] = ListToArray(list);
		columnSizes[i] = list->size;
	}
	*returnColumnSizes = columnSizes;

	return result;
}

int main() {
	int nums[] = {1, 2, 2};
	int size = sizeof(nums) / sizeof(nums[0]);

	int returnSize = 0;
	int *returnColumnSizes;
	int **result = subsetsWithDup(nums, size, &returnSize, &returnColumnSizes);

	printf("result: %d\n", returnSize);
	for (int i = 0; i < returnSize; i++) {
		if (returnColumnSizes[i] == 0) {
			printf("[]\n");
			continue;
		}

		for (int j = 0; j < returnColumnSizes[i]; j++) {
			printf("%d ", result[i][j]);
		}
		printf("\n");
	}
	return 0;
}