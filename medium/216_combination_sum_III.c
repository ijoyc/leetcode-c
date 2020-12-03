/*
* @Author: chenyizhuo.yizhuoc
* @Date:   2020-12-03 16:35:08
* @Last Modified by:   chenyizhuo.yizhuoc
* @Last Modified time: 2020-12-03 17:29:36
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int value;
	struct Node *next;
} Node;

typedef struct {
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
	Node *p = list->head;
	list->head = list->head->next;
	free(p);
	list->size--;
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

void backtracking(int index, int target, int k, List *current, int **result, int *size, int *columnSizes) {
	if (target == 0 && k == 0) {
		result[*size] = ListToArray(current);
		columnSizes[*size] = current->size;
		*size += 1;
		return;
	} else if (target <= 0 || k < 0 || target < index) {
		return;
	}

	for (int i = index; i < 10; i++) {
		ListAdd(current, i);
		backtracking(i + 1, target - i, k - 1, current, result, size, columnSizes);
		ListRemoveFirst(current);
	}
}

int **combinationSum3(int k, int n, int *returnSize, int **returnColumnSizes) {
	int limit = 150;
	int **result = (int **)malloc(sizeof(int *) * limit);
	int *columnSizes = (int *)malloc(sizeof(int) * limit);
	int size = 0;
	List *list = ListNew();

	backtracking(1, n, k, list, result, &size, columnSizes);

	*returnSize = size;
	*returnColumnSizes = columnSizes;
	return result;
}

int main() {
	int k = 3;
	int n = 7;

	int size = 0;
	int *returnColumnSizes;
	int **result = combinationSum3(k, n, &size, &returnColumnSizes);
	printf("result: %d\n", size);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < returnColumnSizes[i]; j++) {
			printf("%d ", result[i][j]);
		}
		printf("\n");
	}

	return 0;
}