
int **generateMatrix(int n, int *returnSize, int **returnColumnSizes) {
    int **result = (int **)malloc(sizeof(int *) * n);
    for (int i = 0; i < n; i++) {
        result[i] = (int *)malloc(sizeof(int) * n);
    }

    int current = 1;
    for (int i = 0; i < (n + 1) / 2; i++) {
        for (int j = i; j <= n - i - 1; j++) {
            result[i][j] = current++;
        }
        for (int j = i + 1; j <= n - i - 1; j++) {
            result[j][n - i - 1] = current++;
        }
        for (int j = n - i - 2; j >= i; j--) {
            result[n - i - 1][j] = current++;
        }
        for (int j = n - i - 2; j > i; j--) {
            result[j][i] = current++;
        }
    }

    *returnSize = n;
    int *columnSizes = (int *)malloc(sizeof(int *) * n);
    for (int i = 0; i < n; i++) {
        columnSizes[i] = n;
    }
    *returnColumnSizes = columnSizes;
    return result;
}