
int max(int a, int b) {
  return a > b ? a : b;
}

// Unlimited transactions count
/*
int maxProfit(int *prices, int pricesSize) {
  int length = pricesSize - 1;
  int **dp = (int **)malloc(sizeof(int *) * length);
  for (int i = 0; i < length; i++) {
    dp[i] = (int *)malloc(sizeof(int) * length);
  }

  for (int i = 0; i < length; i++) {
    for (int j = i; j < length; j++) {
      dp[i][j] = max(prices[j + 1] - prices[i], 0);
    }
  }

  for (int i = 0; i < length; i++) {
    for (int j = i; j < length; j++) {
      printf("%d ", dp[i][j]);
    }
    printf("\n");
  }
  printf("\n");

  for (int i = length - 1; i >= 0; i --) {
    for (int j = i + 1; j < length; j++) {
      dp[i][j] = max(dp[i][j], dp[i][j - 1] + dp[j][j]);
    }
  }

  for (int i = 0; i < length; i++) {
    for (int j = i; j < length; j++) {
      printf("%d ", dp[i][j]);
    }
    printf("\n");
  }
  printf("\n");

  int res = dp[0][length - 1];
  free(dp);
  return res;
}
*/

#define NUM_TRANSACTION 2

int maxProfit(int *prices, int pricesSize) {
  if (!pricesSize) {
    return 0;
  }

  // dp[transaction][day]
  // dp[i][j] = max(dp[i][j - 1],
  //                prices[j] + maxValue)
  // maxValue = max(maxValue, dp[i - 1][j - 1] + prices[j - 1])
  int **dp = (int **)malloc(sizeof(int *) * (NUM_TRANSACTION + 1));
  for (int i = 0; i <= NUM_TRANSACTION; i++) {
    dp[i] = (int *)calloc(pricesSize, sizeof(int));
  }

  for (int i = 1; i <= NUM_TRANSACTION; i++) {
    int maxValue = INT_MIN;
    for (int j = 1; j < pricesSize; j++) {
      maxValue = max(maxValue, dp[i - 1][j] - prices[j - 1]);
      dp[i][j] = max(prices[j] + maxValue, dp[i][j - 1]);
    }
  }

  int res = dp[NUM_TRANSACTION][pricesSize - 1];
  for (int i = 0; i <= NUM_TRANSACTION; i++) {
    free(dp[i]);
  }
  free(dp);
  return res;
}