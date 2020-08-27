static inline int min(int a, int b) {
  return a < b ? a : b;
}

static inline int max(int a, int b) {
  return a > b ? a : b;
}

int calculateMinimumHP(int **dungeon, int dungeonSize, int *dungeonColSize) {
  if (!dungeonSize) {
    return 0;
  }
  int columnSize = *dungeonColSize;
  // dp[i][j]: min hp from (i,j) to the end point
  // use 1-d array to save space
  int dp[columnSize + 1];
  for (int i = 0; i < columnSize; i++) {
    dp[i] = INT_MAX;
  }

  for (int i = dungeonSize - 1; i >= 0; i--) {
    dp[columnSize] = i == dungeonSize - 1 ? 1 : INT_MAX;
    for (int j = columnSize - 1; j >= 0; j--) {
      dp[j] = max(1, min(dp[j], dp[j + 1]) - dungeon[i][j]);
    }
  }
  
  return dp[0];
}