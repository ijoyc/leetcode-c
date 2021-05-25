/*
* @Author: chenyizhuo.yizhuoc
* @Date:   2021-05-25 11:15:10
* @Last Modified by:   chenyizhuo.yizhuoc
* @Last Modified time: 2021-05-25 11:15:17
*/


int findUnsortedSubarray(int* nums, int numsSize){
    int start = numsSize - 1;
    int end = 0;
    
    for (int i = 0; i < numsSize; i++) {
        if (i + 1 < numsSize && nums[i] > nums[i + 1]) {
            start = i;
            break;
        }
    }
    
    for (int i = numsSize - 1; i >= 0; i--) {
        if (i - 1 >= 0 && nums[i] < nums[i - 1]) {
            end = i;
            break;
        }
    }
    
    if (end <= start) {
        return 0;
    }
    
    int minIndex = start;
    int i = start + 1;
    for (; i < numsSize; i++) {
        if (nums[i] < nums[minIndex]) {
            minIndex = i;
        }
    }
    
    int maxIndex = end;
    for (i = end - 1; i >= 0; i--) {
        if (nums[i] > nums[maxIndex]) {
            maxIndex = i;
        }
    }
    
    for (i = 0; nums[i] <= nums[minIndex]; i++) {
        
    }
    start = i;
    for (i = numsSize - 1; i > end && nums[i] >= nums[maxIndex]; i--) {
        
    }
    end = i;
    
    return end - start + 1;
}