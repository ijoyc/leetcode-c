
#define MIN(a, b) ((a) < (b) ? (a) : (b))

int *spiralOrder(int **matrix, int matrixSize, int *matrixColSize, int *returnSize) {
    if (matrixSize == 0) {
        *returnSize = 0;
        return NULL;
    }

    int size = matrixSize * *matrixColSize;
    int *result = (int *)malloc(sizeof(int) * size);
    *returnSize = size;
    int current = 0;

    for (int i = 0; i < (MIN(matrixSize, *matrixColSize) + 1) / 2; i++) {
        for (int j = i; j < *matrixColSize - i; j++) {
            result[current++] = matrix[i][j];
        }
        if (i + 1 >= matrixSize - i) {
            break;
        }
        for (int j = i + 1; j < matrixSize - i; j++) {
            result[current++] = matrix[j][*matrixColSize - i - 1];
        }
        if (*matrixColSize - i - 2 < i) {
            break;
        }
        for (int j = *matrixColSize - i - 2; j >= i; j--) {
            result[current++] = matrix[matrixSize - i - 1][j];
        }
        for (int j = matrixSize - i - 2; j > i; j--) {
            result[current++] = matrix[j][i];
        }
    }

    return result;
}