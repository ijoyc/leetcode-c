
int numDistinct(char *s, char *t) {
  int slength = strlen(s);
  int tlength = strlen(t);

  long long **dp = (long long **)malloc(sizeof(long long *) * (tlength + 1));
  for (int i = 0; i <= tlength; i++) {
    dp[i] = (long long *)calloc(slength + 1, sizeof(long long));
  }
  for (int i = 0; i <= slength; i++) {
    dp[tlength][i] = 1;
  }

  for (int i = tlength - 1; i >= 0; i--) {
    for (int j = slength - (tlength - i); j >= 0; j--) {
      dp[i][j] = s[j] == t[i] ? dp[i][j + 1] + dp[i + 1][j + 1] : dp[i][j + 1];
    }
  }

  int res = dp[0][0];
  for (int i = 0; i <= tlength; i++) {
    free(dp[i]);
  }
  free(dp);
  return res;
}