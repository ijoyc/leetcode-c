
int numTrees(int n) {
  if (!n) {
    return 0;
  }

  int *dp = (int *)malloc(sizeof(int) * n);
  dp[0] = 1;

  for (int i = 1; i < n; i++) {

    int length = 0;
    for (int j = 0; j <= i; j++) {
      int left = j >= 1 ? j - 1 : 0;
      int right = i - j >= 1 ? i - j - 1 : 0;
      length += dp[left] * dp[right];
    }

    dp[i] = length;
  }

  int res = dp[n - 1];
  free(dp);
  return res;
}