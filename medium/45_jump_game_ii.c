
#define MIN(a, b) ((a) < (b) ? (a) : (b))

int jump(int *nums, int numsSize) {
    int *dp = (int *)malloc(sizeof(int) * numsSize);
    dp[numsSize - 1] = 0;
    for (int i = numsSize - 2; i >= 0; i--) {
        int min = numsSize;
        for (int j = nums[i], k = i + 1; j > 0 && k < numsSize; j--, k++) {
            min = MIN(dp[k], min);
        }
        dp[i] = min + 1;
    }
    int result = dp[0];
    free(dp);
    return result;
}