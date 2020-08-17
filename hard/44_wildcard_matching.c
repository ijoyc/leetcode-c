
int isMatch(char *s, char *p) {
  int slen = strlen(s);
  int plen = strlen(p);

  int **dp = (int **)malloc(sizeof(int *) * (slen + 1));
  for (int i = 0; i <= slen; i++) {
    dp[i] = (int *)calloc(plen + 1, sizeof(int));
  }

  dp[slen][plen] = 1;
  int res = 0;

  for (int i = slen; i >= 0; i--) {
    for (int j = plen - 1; j >= 0; j--) {
      int currentMatch = i != slen && (s[i] == p[j] || p[j] == '?');
      if (p[j] == '*') {
        dp[i][j] = (i < slen && dp[i + 1][j]) || dp[i][j + 1];
      } else if (currentMatch) {
        dp[i][j] = dp[i + 1][j + 1];
      }
    }
  }

  res = dp[0][0];
  for (int i = 0; i <= slen; i++) {
    free(dp[i]);
  }
  free(dp);

  return res;
}