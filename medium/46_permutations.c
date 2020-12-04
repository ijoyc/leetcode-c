/*
* @Author: chenyizhuo.yizhuoc
* @Date:   2020-12-04 11:10:05
* @Last Modified by:   chenyizhuo.yizhuoc
* @Last Modified time: 2020-12-04 11:40:08
*/

#include <stdio.h>
#include <stdlib.h>

int *copy(int *current, int currentSize) {
	int *nums = (int *)malloc(sizeof(int) * currentSize);
	for (int i = 0; i < currentSize; i++) {
		nums[i] = current[i];
	}
	return nums;
}

void backtracking(int *nums, int numsSize, int left, int *used, int *current, int currentSize, int **result, int *size, int *columnSizes) {

	if (left == 0) {
		int *nums = copy(current, currentSize);
		result[*size] = nums;
		columnSizes[*size] = currentSize;
		*size += 1;
		return;
	}

	for (int i = 0; i < numsSize; i++) {
		if (used[i]) {
			continue;
		}
		used[i] = 1;
		current[currentSize++] = nums[i];
		backtracking(nums, numsSize, left - 1, used, current, currentSize, result, size, columnSizes);
		currentSize--;
		used[i] = 0;
	}
}

int **permute(int *nums, int numsSize, int *returnSize, int **returnColumnSizes) {
	int total = 1;
	for (int i = 2; i <= numsSize; i++) {
		total *= i;
	}
	int **result = (int **)malloc(sizeof(int *) * total);
	int *columnSizes = (int *)malloc(sizeof(int) * total);
	int size = 0;

	int *used = (int *)calloc(numsSize, sizeof(int));
	int *current = (int *)malloc(sizeof(int) * numsSize);

	backtracking(nums, numsSize, numsSize, used, current, 0, result, &size, columnSizes);

	free(used);
	free(current);
	*returnSize = size;
	*returnColumnSizes = columnSizes;
	return result;
}

int main() {
	int nums[] = {1, 2, 3, 4};
	int size = sizeof(nums) / sizeof(nums[0]);

	int returnSize = 0;
	int *returnColumnSizes;
	int **result = permute(nums, size, &returnSize, &returnColumnSizes);

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