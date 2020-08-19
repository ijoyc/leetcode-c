
int minimumTotal(int **triangle, int triangleSize, int *triangleColSize) {
  int *dp = (int *)malloc(sizeof(int) * triangleSize);

  dp[0] = triangle[0][0];
  for (int i = 1; i < triangleSize; i++) {
    dp[i] = triangle[i][0] + dp[i - 1];
  }

  for (int i = 1; i < triangleSize; i++) {
    int val;
    int last;

    for (int j = i; j < triangleSize; j++) {
      val = dp[j - 1] + triangle[j][i];
      if (val < dp[j]) {
        dp[j] = val;
      }
      // update last step value
      // because we can only move to adjacent items
      if (j > i) {
        dp[j - 1] = last;
      }
      last = val;
    }
  }

  int res = dp[triangleSize - 1];
  free(dp);
  return res;
}