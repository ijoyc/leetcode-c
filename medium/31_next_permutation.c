/*
* @Author: chenyizhuo.yizhuoc
* @Date:   2020-12-02 17:25:01
* @Last Modified by:   chenyizhuo.yizhuoc
* @Last Modified time: 2020-12-02 18:14:48
*/

#include <stdio.h>
#include <stdlib.h>

void swap(int *num1, int *num2) {
	int tmp = *num1;
	*num1 = *num2;
	*num2 = tmp;
}

void inverse(int *nums, int numsSize) {
	for (int i = 0; i < numsSize / 2; i++) {
		swap(&nums[i], &nums[numsSize - i - 1]);
	}
}

int cmp(const void *n1, const void *n2) {
	return *(int *)n1 - *(int *)n2;
}

void nextPermutation(int *nums, int numsSize) {
	int foundReverse = 0;
	// 1. find reverse order
	int startIndex = 0;
	for (int i = numsSize - 1; i > 0; i--) {
		if (nums[i] > nums[i - 1]) {
			startIndex = i - 1;
			foundReverse = 1;
			break;
		}
	}
	if (!foundReverse) {
		inverse(nums, numsSize);
		return;
	}

	// 2. find and exchange with next greater bit
	int nextIndex = startIndex + 1;
	for (int i = startIndex + 2; i < numsSize; i++) {
		if (nums[i] > nums[startIndex] && nums[i] < nums[nextIndex]) {
			nextIndex = i;
		}
	}
	swap(&nums[startIndex], &nums[nextIndex]);

	// 3. sort numbers [startIndex + 1, numsSize)
	qsort(nums + startIndex + 1, numsSize - startIndex - 1, sizeof(int), cmp);
}

int main() {
	int nums[] = { 7, 9, 8, 5, 2 };
	int size = sizeof(nums) / sizeof(nums[0]);
	nextPermutation(nums, size);
	for (int i = 0; i < size; i++) {
		printf("%d ", nums[i]);
	}
	printf("\n");
	return 0;
}