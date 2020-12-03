/*
* @Author: chenyizhuo.yizhuoc
* @Date:   2020-12-02 21:49:33
* @Last Modified by:   chenyizhuo.yizhuoc
* @Last Modified time: 2020-12-03 14:59:31
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int value;
	struct Node *next;
} Node;

typedef struct List {
	Node *head;
	int size;
} List;

List *ListNew() {
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

void ListRemoveFirst(List *list) {
	if (list->head == NULL) {
		return;
	}
	Node *p = list->head;
	list->head = p->next;
	list->size--;
	free(p);
}

int *ListToArray(List *list) {
	int *array = (int *)malloc(sizeof(int) * list->size);
	Node *p = list->head;
	for (int i = 0; i < list->size; i++) {
		array[i] = p->value;
		p = p->next;
	}
	return array;
}

void resolve(int *nums, int index, int size, int target, List *current, int **result, int *resultSize, int *returnColumnSizes) {
	if (target == 0) {
		result[*resultSize] = ListToArray(current);
		returnColumnSizes[*resultSize] = current->size;
		*resultSize += 1;
		return;
	} else if (target < 0) {
		return;
	}

	for (int i = index; i < size; i++) {
		ListAdd(current, nums[i]);
		resolve(nums, i, size, target - nums[i], current, result, resultSize, returnColumnSizes);
		ListRemoveFirst(current);
	}
}

int **combinationSum(int *candidates, int candidatesSize, int target, int *returnSize, int **returnColumnSizes) {
	const int limit = 150;
	int **result = (int **)malloc(sizeof(int *) * limit);
	int *columnSizes = (int *)malloc(sizeof(int) * limit);
	int size = 0;

	List *list = ListNew();
	resolve(candidates, 0, candidatesSize, target, list, result, &size, columnSizes);

	*returnSize = size;
	*returnColumnSizes = columnSizes;
	return result;
}

int main() {
	int nums[] = { 2, 3, 6, 7 };
	int target = 7;
	int size = sizeof(nums) / sizeof(nums[0]);

	int returnSize;
	int *returnColumnSizes;
	int **result = combinationSum(nums, size, target, &returnSize, &returnColumnSizes);

	printf("returnSize: %d\n", returnSize);

	for (int i = 0; i < returnSize; i++) {
		for (int j = 0; j < returnColumnSizes[i]; j++) {
			printf("%d ", result[i][j]);
		}
		printf("\n");
	}
	return 0;
}