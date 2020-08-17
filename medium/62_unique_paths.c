
int uniquePaths(int m, int n) {
  // row: n, column: m
  int *dp = (int *)calloc(m, sizeof(int));
  dp[m - 1] = 1;

  for (int i = 0; i < n; i++) {
    for (int j = m - 2; j >= 0; j--) {
      dp[j] = dp[j] + dp[j + 1];
    }
  }
  
  int res = dp[0];
  free(dp);

  return res;
}