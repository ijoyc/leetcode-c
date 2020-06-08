/*
 * Created Date: Sunday June 7th 2020
 * Author: yizhuoc
 */

#include <limits.h>
#include <stdlib.h>

static inline int Abs(int a) { return a > 0 ? a : -a; }

int compareFunc(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

int threeSumClosest(int *nums, int numsSize, int target) {
    qsort(nums, numsSize, sizeof(int), &compareFunc);
    int currentDiff = INT_MAX;
    int result = 0;
    for (int i = 0; i < numsSize - 2; i++) {
        if (i && nums[i] == nums[i - 1]) {
            continue;
        }

        int current = target - nums[i];
        int j = i + 1;
        int k = numsSize - 1;
        while (j < k) {
            int diff = current - (nums[j] + nums[k]);
            if (Abs(diff) < currentDiff) {
                currentDiff = Abs(diff);
                result = target - diff;
            }

            if (diff < 0) {
                k--;
            } else if (diff > 0) {
                j++;
            } else {
                return result;
            }

            while (j < k && j > i + 1 && nums[j] == nums[j - 1]) {
                j++;
            }
            while (j < k && k < numsSize - 1 && nums[k] == nums[k + 1]) {
                k--;
            }
        }
    }
    return result;
}