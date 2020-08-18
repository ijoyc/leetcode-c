
int isScramble(char *s1, char *s2) {
  int len = strlen(s1);
  if (len != strlen(s2)) {
    return 0;
  }

  int ***dp = (int ***)malloc(sizeof(int **) * len);
  for (int i = 0; i < len; i++) {
    dp[i] = (int **)malloc(sizeof(int *) * len);
    for (int j = 0; j < len; j++) {
      dp[i][j] = (int *)calloc(len, sizeof(int));
    }
  }

  for (int i = 0; i < len; i++) {
    for (int j = 0; j < len; j++) {
      dp[i][j][0] = s1[i] == s2[j];
    }
  }

  for (int l = 1; l < len; l++) {
    for (int i = 0; i < len - l; i++) {
      for (int j = 0; j < len - l; j++) {
        for (int k = 0; k < l; k++) {
          if ((dp[i][j][k] && dp[i + k + 1][j + k + 1][l - k - 1]) || (dp[i][j + l - k][k] && dp[i + k + 1][j][l - k - 1])) {
            dp[i][j][l] = 1;
            break;
          }
        }
      }
    }
  }

  int res = dp[0][0][len - 1];
  for (int i = 0; i < len; i++) {
    for (int j = 0; j < len; j++) {
      free(dp[i][j]);
    }
    free(dp[i]);
  }
  free(dp);

  return res;
}