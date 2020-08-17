
int min(int a, int b) {
  return a < b ? a : b;
}

int minPathSum(int** grid, int gridSize, int* gridColSize) {
  int *dp = (int *)calloc(*gridColSize + 1, sizeof(int));
  int last = *gridColSize - 1;
  dp[last] = grid[gridSize - 1][last];
  for (int i = last - 1; i >= 0; i--) {
    dp[i] = grid[gridSize - 1][i] + dp[i + 1];
  }
  dp[last + 1] = INT_MAX;

  for (int i = gridSize - 2; i >= 0; i--) {
    for (int j = last; j >= 0; j--) {
      dp[j] = grid[i][j] + min(dp[j], dp[j + 1]);
    }
  }

  int res = dp[0];
  free(dp);
  return res;
}