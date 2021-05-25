/*
* @Author: chenyizhuo.yizhuoc
* @Date:   2021-05-25 12:01:06
* @Last Modified by:   chenyizhuo.yizhuoc
* @Last Modified time: 2021-05-25 15:39:41
*/

void merge(int *nums, int numsSize, int from, int mid, int to) {
    int i = from;
    int j = mid + 1;
    int k = 0;
    int tmp[numsSize];

    while (i <= mid && j <= to) {
        if (nums[i] < nums[j]) {
            tmp[k++] = nums[i++];
        } else {
            tmp[k++] = nums[j++];
        }
    }

    while (i <= mid) {
        tmp[k++] = nums[i++];
    }
    while (j <= to) {
        tmp[k++] = nums[j++];
    }

    for (int i = 0; i < k; i++) {
        nums[from + i] = tmp[i];
    }
}

void mergeSort(int *nums, int numsSize, int from, int to) {
    if (from >= to) {
        return;
    }
    int mid = from + (to - from) / 2;
    mergeSort(nums, numsSize, from, mid);
    mergeSort(nums, numsSize, mid + 1, to);
    merge(nums, numsSize, from, mid, to);

}

int *sortArray(int *nums, int numsSize, int *returnSize) {
    int *result = (int *)malloc(sizeof(int) * numsSize);
    memcpy(result, nums, sizeof(int) * numsSize);
    mergeSort(result, numsSize, 0, numsSize - 1);
    *returnSize = numsSize;
    return result;
}