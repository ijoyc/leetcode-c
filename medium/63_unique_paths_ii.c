
int uniquePathsWithObstacles(int **obstacleGrid, 
  int obstacleGridSize, 
  int *obstacleGridColSize) {

  long long *dp = (long long *)calloc(*obstacleGridColSize, sizeof(long long));
  dp[*obstacleGridColSize - 1] = 1;

  for (int i = obstacleGridSize - 1; i >= 0; i--) {
    for (int j = *obstacleGridColSize - 1; j >= 0; j--) {
      dp[j] = obstacleGrid[i][j] ? 0 : dp[j] + (j + 1 < *obstacleGridColSize ? dp[j + 1] : 0);
    }
  }

  int res = dp[0];
  free(dp);
  return res;
}