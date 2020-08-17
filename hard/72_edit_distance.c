
int min(int a, int b, int c) {
  int res = a < b ? a : b;
  return res < c ? res : c;
}

int minDistance(char *word1, char *word2) {
  int length1 = strlen(word1);
  int length2 = strlen(word2);

  int **dp = (int **)malloc(sizeof(int *) * (length1 + 1));
  for (int i = 0; i <= length1; i++) {
    dp[i] = (int *)malloc(sizeof(int) * (length2 + 1));
  }

  dp[length1][length2] = 0;
  for (int i = 0; i < length1; i++) {
    dp[i][length2] = length1 - i;
  }
  for (int i = 0; i < length2; i++) {
    dp[length1][i] = length2 - i;
  }

  int first = length1 < length2 ? length1 : length2;

  int start1 = length1 - 1;
  int start2 = length2 - 1;

  for (int i = 0; i < first; i++) {
    for (int j = start1; j >= 0; j--) {
      if (word1[j] == word2[start2]) {
        dp[j][start2] = dp[j + 1][start2 + 1];
      } else {
        dp[j][start2] = 1 + min(dp[j + 1][start2], dp[j][start2 + 1], dp[j + 1][start2 + 1]);
      }
    }

    for (int j = start2; j >= 0; j--) {
      if (word1[start1] == word2[j]) {
        dp[start1][j] = dp[start1 + 1][j + 1];
      } else {
        dp[start1][j] = 1 + min(dp[start1 + 1][j], dp[start1][j + 1], dp[start1 + 1][j + 1]);
      }
    }

    start1--;
    start2--;
  }

  // for (int i = 0; i <= length1; i++) {
  //   for (int j = 0; j <= length2; j++) {
  //     printf("%d ", dp[i][j]);
  //   }
  //   printf("\n");
  // }

  int res = dp[0][0];
  for (int i = 0; i <= length1; i++) {
    free(dp[i]);
  }
  free(dp);
  return res;
}