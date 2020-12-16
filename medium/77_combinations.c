/*
* @Author: chenyizhuo.yizhuoc
* @Date:   2020-12-11 16:56:46
* @Last Modified by:   chenyizhuo.yizhuoc
* @Last Modified time: 2020-12-16 11:28:11
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *copy(int *current, int currentSize) {
	int *nums = (int *)malloc(sizeof(int) * currentSize);
	memcpy(nums, current, sizeof(int) * currentSize);
	return nums;
}

void backtracking(int n, int i, int k, int *current, int currentSize, int ***result, int *size, int *capacity) {
	if (k == currentSize) {
		if (*size == *capacity) {
			int newCapacity = *capacity * 2;
			*result = (int **)realloc(*result, sizeof(int *) * newCapacity);
			*capacity = newCapacity;
		}
		(*result)[*size] = copy(current, currentSize);
		*size += 1;
		return;
	}

	for (; i <= n; i++) {
		current[currentSize++] = i;
		backtracking(n, i + 1, k, current, currentSize, result, size, capacity);
		currentSize--;
	}
}

int **combine(int n, int k, int *returnSize, int **returnColumnSizes) {
	if (n < k) {
		return NULL;
	}
	
	int capacity = 16;
	int **result = (int **)malloc(sizeof(int *) * capacity);
	int size = 0;
	int *current = (int *)malloc(sizeof(int) * k);

	backtracking(n, 1, k, current, 0, &result, &size, &capacity);

	int *columnSizes = (int *)malloc(sizeof(int) * size);
	for (int i = 0; i < size; i++) {
		columnSizes[i] = k;
	}

	*returnColumnSizes = columnSizes;
	*returnSize = size;
	return result;
}

int main() {
	int n = 8;
	int k = 5;

	int returnSize = 0;
	int *returnColumnSizes;
	int **result = combine(n, k, &returnSize, &returnColumnSizes);

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