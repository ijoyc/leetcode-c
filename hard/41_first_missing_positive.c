
/*
3 9 10 7 8 15 16 4 5 1 2
 
3 9 3 7 8 15 16 4 5 1 2
 
3 9 3 7 8 15 16 4 5 10 2
 
1 9 3 7 8 15 16 4 5 10 2

1 9 3 7 8 15 16 4 9 10 2
 
1 9 3 7 5 15 16 4 9 10 2
 
1 9 3 7 5 15 16 8 9 10 2
 
1 9 3 4 5 15 7 8 9 10 2
 
1 2 3 4 5 16 ...
*/

int firstMissingPositive(int *nums, int numsSize) {
    for (int i = 0; i < numsSize; i++) {
        int current = nums[i];
        while (current > 0 && current <= numsSize && current != nums[current - 1]) {
            int tmp = nums[current - 1];
            nums[current - 1] = current;
            current = tmp;
        }
    }
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] != i + 1) {
            return i + 1;
        }
    }
    return numsSize + 1;
}