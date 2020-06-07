/*
 * Created Date: Sunday June 7th 2020
 * Author: yizhuoc
 */

#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 8
#define SWAP(a, b) { int tmp = (a); (a) = (b); (b) = tmp; }

int Partition(int *nums, int from, int to) {
    int stub = nums[to];
    int i = from - 1;
    for (int j = from; j < to; j++) {
        if (nums[j] < stub) {
            i++;
            SWAP(nums[j], nums[i]);
        }
    }
    SWAP(nums[i + 1], nums[to]);
    return i + 1;
}

void QuickSort(int *nums, int from, int to) {
    if (from < to) {
        int mid = Partition(nums, from, to);
        QuickSort(nums, from, mid - 1);
        QuickSort(nums, mid + 1, to);
    }
}

int **AddTriplet(int **array, int *totalSize, int *currentSize, int a, int b, int c) {
    int total = *totalSize;
    int current = *currentSize;
    if (total == current) {
        total = total << 1;
        array = (int **)realloc(array, total * sizeof(int *));
    }

    int *triplet = (int *)malloc(sizeof(int) * 3);
    triplet[0] = a;
    triplet[1] = b;
    triplet[2] = c;
    array[current++] =triplet;

    *totalSize = total;
    *currentSize = current;

    return array;
}

int **threeSum(int *nums, int numsSize, int *returnSize, int **returnColumnSizes) {
    QuickSort(nums, 0, numsSize - 1);

    int arrayCapacity = INITIAL_CAPACITY;
    int arraySize = 0;
    int **array = (int **)malloc(sizeof(int *) * arrayCapacity);
    
    int total = 0;
    for (int i = 0; i < numsSize; i++) {
        if (i && nums[i] == nums[i - 1]) {
            continue;
        }

        int j = i + 1;
        int k = numsSize - 1;
        int target = -nums[i];

        while (j < k) {
            int sum = nums[j] + nums[k];
            if (sum > target) {
                k--;
            } else if (sum < target) {
                j++;
            } else {
                total++;
                array = AddTriplet(array, &arrayCapacity, &arraySize, nums[i], nums[j], nums[k]);
                while (j < k && nums[j + 1] == nums[j]) {
                    j++;
                }
                while (j < k && nums[k - 1] == nums[k]) {
                    k--;
                }
                j++;
                k--;
            }
        }
    }
    
    *returnColumnSizes = (int *)malloc(sizeof(int) * total);
    for (int i = 0; i < total; i++) {
        (*returnColumnSizes)[i] = 3;
    }
    *returnSize = total;
    return array;
}