/*
* @Author: chenyizhuo.yizhuoc
* @Date:   2020-12-02 18:29:55
* @Last Modified by:   chenyizhuo.yizhuoc
* @Last Modified time: 2020-12-02 21:43:54
*/

#include <stdlib.h>

int binarySearch(int *nums, int start, int end, int target) {
	while (start <= end) {
		int mid = (start + end) / 2;
		if (nums[mid] == target) {
			return mid;
		} else if (nums[mid] > target) {
			end = mid - 1;
		} else {
			start = mid + 1;
		}
	}
	return -1;
}

int *searchRange(int *nums, int numsSize, int target, int *returnSize) {
	*returnSize = 2;
	int *result = (int *)malloc(sizeof(int) * 2);

	int index = binarySearch(nums, 0, numsSize - 1, target);
	if (index == -1) {
		result[0] = -1;
		result[1] = -1;
		return result;
	}

	int rindexInLeft = index - 1;
	int left = index;
	while (rindexInLeft >= 0) {
		int leftIndex = binarySearch(nums, 0, rindexInLeft, target);
		if (leftIndex == -1) {
			break;
		}
		left = leftIndex;
		rindexInLeft = leftIndex - 1;
	}

	int lindexInRight = index + 1;
	int right = index;
	while (lindexInRight < numsSize) {
		int rightIndex = binarySearch(nums, lindexInRight, numsSize - 1, target);
		if (rightIndex == -1) {
			break;
		}
		right = rightIndex;
		lindexInRight = rightIndex + 1;
	}

	result[0] = left;
	result[1] = right;

	return result;
}

int main() {
	return 0;
}