/*
 * Created Date: Monday June 8th 2020
 * Author: yizhuoc
 */

#include <stdlib.h>

#define INITIAL_CAPACITY 16

int compareFunc(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

int **addItem(int **nums, int a, int b, int c, int d, int *total, int *current) {
    int currentTotal = *total;
    int currentSize = *current;
    if (currentTotal == currentSize) {
        currentTotal <<= 1;
        nums = (int **)realloc(nums, sizeof(int *) * currentTotal);
        *total = currentTotal;
    }

    int *item = (int *)malloc(sizeof(int) * 4);
    item[0] = a;
    item[1] = b;
    item[2] = c;
    item[3] = d;
    nums[currentSize++] = item;
    *current = currentSize;
    return nums;
}

int **fourSum(int *nums, int numsSize, int target, int *returnSize, int **returnColumnSizes) {
    qsort(nums, numsSize, sizeof(int), &compareFunc);
    
    int total = 0;
    int capacity = INITIAL_CAPACITY;
    int size = 0;
    int **result = (int **)malloc(sizeof(int *) * capacity);
    
    for (int i = 0; i < numsSize - 3; i++) {
        if (i && nums[i] == nums[i - 1]) {
            continue;
        }

        for (int j = i + 1; j < numsSize - 2; j++) {
            if (j > i + 1 && nums[j] == nums[j - 1]) {
                continue;
            }

            int diff = target - (nums[i] + nums[j]);

            int m = j + 1;
            int n = numsSize - 1;
            while (m < n) {
                int sum = nums[m] + nums[n];
                if (sum > diff) {
                    n--;
                } else if (sum < diff) {
                    m++;
                } else {
                    total++;
                    result = addItem(result, nums[i], nums[j], nums[m], nums[n], &capacity, &size);
                    m++;
                    n--;

                    while (m < n && nums[m] == nums[m - 1]) {
                        m++;
                    }
                    while (m < n && nums[n] == nums[n + 1]) {
                        n--;
                    }
                }
            }
        }
    }

    *returnSize = total;
    int *columnSizes = (int *)malloc(sizeof(int) * total);
    for (int i = 0; i < total; i++) {
        columnSizes[i] = 4;
    }
    *returnColumnSizes = columnSizes;

    return result;
}