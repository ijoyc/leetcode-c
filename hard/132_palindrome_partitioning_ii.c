static inline int min(int a, int b) {
  return a < b ? a : b;
}

int minCut(char *s) {
  int len = strlen(s);
  if (!len) {
    return 0;
  }

  int **dp = (int **)malloc(sizeof(int *) * len);
  for (int i = 0; i < len; i++) {
    dp[i] = (int *)calloc(len, sizeof(int));
  }

  for (int i = 0; i < len; i++) {
    dp[i][i] = 1;
    if (i + 1 < len) {
      dp[i][i + 1] = s[i] == s[i + 1];
    }
  }

  // first, use dp to get palindrome table
  for (int i = 2; i < len; i++) {
    for (int j = 0; j < i - 1; j++) {
      dp[j][i] = s[j] == s[i] && dp[j + 1][i - 1];
    }
  }

  // second, dp2[i] = length of longest palindrome start from i
  int *dp2 = (int *)malloc(sizeof(int) * (len + 1));
  dp2[len] = -1;
  for (int i = 0; i < len; i++) {
    for (int j = i; j < len; j++) {
      if (dp[i][j]) {
        dp2[i] = j - i + 1;
      }
    }
  }

  // third, dp2[i] = minCut start from i
  for (int i = len - 1; i >= 0; i--) {
    dp2[i] = min(dp2[i + 1], dp2[i + dp2[i]]) + 1;
  }

  int count = dp2[0];
  for (int i = 0; i < len; i++) {
    free(dp[i]);
  }
  free(dp);
  free(dp2);
  return count;
}