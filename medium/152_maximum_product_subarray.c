
static inline int Max(int a, int b) {
  return a > b ? a : b;
}

static inline int Min(int a, int b) {
  return a < b ? a : b;
}

static inline void Swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

int maxProduct_time_On(int *nums, int numsSize) {
  int res = nums[0];
  int max = nums[0];
  int min = nums[0];
  for (int i = 1; i < numsSize; i++) {
    if (nums[i] < 0) {
      Swap(max, min);
    }
    max = Max(nums[i], nums[i] * max);
    min = Min(nums[i], nums[i] * min);
    res = Max(res, max);
  }
  return res;
}

int maxProduct(int *nums, int numsSize) {
  if (!numsSize) {
    return 0;
  }

  // int dp[numsSize][numsSize];
  // memset(dp, 0, sizeof(int) * numsSize * numsSize);

  // int max = INT_MIN;
  
  // for (int i = 0; i < numsSize; i++) {
  //   dp[i][i] = nums[i];
  //   if (dp[i][i] > max) {
  //     max = dp[i][i];
  //   }
  // }

  // for (int i = 0; i < numsSize; i++) {
  //   for (int j = i + 1; j < numsSize; j++) {

  //   }
  // }
  int max = INT_MIN;
  for (int i = 0; i < numsSize; i++) {
    int p = nums[i];
    for (int j = i; j < numsSize; j++) {
      int current = j == i ? p : p * nums[j];
      p = current;
      if (current > max) {
        max = p;
      }
    }
  }
  return max;
}