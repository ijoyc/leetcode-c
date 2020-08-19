
int max(int a, int b) {
  return a > b ? a : b;
}

int min(int a, int b) {
  return a < b ? a : b;
}

int isInterleave(char *s1, char *s2, char *s3) {
  int length1 = strlen(s1);
  int length2 = strlen(s2);
  int length3 = strlen(s3);

  if (length1 == 0) {
    return strcmp(s2, s3) == 0;
  } else if (length2 == 0) {
    return strcmp(s1, s3) == 0;
  }
  if (length1 + length2 != length3) {
    return 0;
  }

  int **dp = (int **)malloc(sizeof(int *) * (length1 + 1));
  for (int i = 0; i <= length1; i++) {
    dp[i] = (int *)calloc(length2 + 1, sizeof(int));
  }

  dp[length1][length2] = 1;
  for (int l = 1; l <= length3; l++) {
    int start = length2 - l;
    for (int i = max(0, start), j = length1 + min(0, start); i <= length2 && j >= 0; i++, j--) {
      if (((i + 1 > length2 || dp[j][i + 1]) && s3[length3 - l] == s2[i]) || ((j + 1 > length1 || dp[j + 1][i]) && s3[length3 - l] == s1[j])) {
        dp[j][i] = 1;
      }
    }
  }

  for (int i = 0; i <= length1; i++) {
    for (int j = 0; j <= length2; j++) {
      printf("%d", dp[i][j]);
    }
    printf("\n");
  }

  int res = dp[0][0];
  for (int i = 0; i < length1; i++) {
    free(dp[i]);
  }
  free(dp);
  return res;
}