/*
* @Author: chenyizhuo.yizhuoc
* @Date:   2020-12-16 12:11:01
* @Last Modified by:   chenyizhuo.yizhuoc
* @Last Modified time: 2020-12-21 11:37:30
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp(const void *n1, const void *n2) {
	return *(int *)n1 - *(int *)n2;
}

int *copy(int *nums, int size) {
	int *result = (int *)malloc(sizeof(int) * size);
	memcpy(result, nums, sizeof(int) * size);
	return result;
}

void backtracking(int *nums, int numsSize, int target, int i, int *currentNums, int currentNumSize, int ***result, int *capacity, int *size, int **columnSizes) {
	if (target == 0) {
		if (*capacity == *size) {
			int newCapacity = *capacity * 2;
			*result = (int **)realloc(*result, sizeof(int **) * newCapacity);
			*columnSizes = (int *)realloc(*columnSizes, sizeof(int *) * newCapacity);
			*capacity = newCapacity;
		}
		(*result)[*size] = copy(currentNums, currentNumSize);
		(*columnSizes)[*size] = currentNumSize;
		*size += 1;
		return;
	} else if (target < 0) {
		return;
	}

	for (int j = i; j < numsSize; j++) {
		if (j > i && nums[j] == nums[j - 1]) {
			continue;
		}

		currentNums[currentNumSize++] = nums[j];
		backtracking(nums, numsSize, target - nums[j], j + 1, currentNums, currentNumSize, result, capacity, size, columnSizes);
		currentNumSize--;
	}
}


int **combinationSum2(int *candidates, int candidatesSize, int target, int *returnSize, int **returnColumnSizes) {
	int capacity = 16;
	int **result = (int **)malloc(sizeof(int *) * capacity);
	int *columnSizes = (int *)malloc(sizeof(int) * capacity);
	int size = 0;

	int *currentNums = (int *)malloc(sizeof(int) * candidatesSize);

	qsort(candidates, candidatesSize, sizeof(int), cmp);

	backtracking(candidates, candidatesSize, target, 0, currentNums, 0, &result, &capacity, &size, &columnSizes);

	*returnSize = size;
	*returnColumnSizes = columnSizes;
	return result;
}

int main() {
	// int nums[] = {10,1,2,7,6,1,5};
	// int size = sizeof(nums) / sizeof(nums[0]);
	// int target = 8;
	int nums[] = {2,5,2,1,2};
	int size = sizeof(nums) / sizeof(nums[0]);
	int target = 5;

	int returnSize = 0;
	int *returnColumnSizes;
	int **result = combinationSum2(nums, size, target, &returnSize, &returnColumnSizes);

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