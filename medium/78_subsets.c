/*
* @Author: chenyizhuo.yizhuoc
* @Date:   2020-12-03 18:00:36
* @Last Modified by:   chenyizhuo.yizhuoc
* @Last Modified time: 2020-12-03 18:12:06
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int *Copy(int *current, int currentSize) {
	int *nums = (int *)malloc(sizeof(int) * currentSize);
	for (int i = 0; i < currentSize; i++) {
		nums[i] = current[i];
	}
	return nums;
}

void backtracking(int *nums, int index, int numsSize, int *current, int currentSize, int **result, int *size, int *columnSizes) {
	int *copy = Copy(current, currentSize);
	result[*size] = copy;
	columnSizes[*size] = currentSize;
	*size += 1;

	for (int i = index; i < numsSize; i++) {
		current[currentSize++] = nums[i];
		backtracking(nums, i + 1, numsSize, current, currentSize, result, size, columnSizes);
		currentSize--;
	}
}

int **subsets(int *nums, int numsSize, int *returnSize, int **returnColumnSizes) {
	int count = pow(2, numsSize);
	int **result = (int **)malloc(sizeof(int *) * count);
	int *columnSizes = (int *)malloc(sizeof(int) * count);
	int size = 0;
	int *current = (int *)malloc(sizeof(int) * numsSize);

	backtracking(nums, 0, numsSize, current, 0, result, &size, columnSizes);

	free(current);
	*returnSize = size;
	*returnColumnSizes = columnSizes;
	return result;
}

int main() {
	int nums[] = {1, 2, 3};
	int size = sizeof(nums) / sizeof(nums[0]);

	int returnSize = 0;
	int *returnColumnSizes;
	int **result = subsets(nums, size, &returnSize, &returnColumnSizes);

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