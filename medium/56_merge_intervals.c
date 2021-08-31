
int cmp(const void *a, const void *b) {
    int *first = *(int **)a;
    int *second = *(int **)b;
    return first[0] - second[0];
}

int **merge(int **intervals, int intervalsSize, int *intervalsColSize, int *returnSize, int **returnColumnSizes) {
    qsort(intervals, intervalsSize, sizeof(int *), cmp);

    int *stack = (int *)malloc(sizeof(int) * 2 * intervalsSize);
    int top = 0;

    for (int i = 0; i < intervalsSize; i++) {
        int *current = intervals[i];
        if (top == 0 || current[0] > stack[top - 1]) {
            stack[top++] = current[0];
            stack[top++] = current[1];
        } else if (top > 0 && stack[top - 1] < current[1]) {
            stack[top - 1] = current[1];
        }
    }

    int resultSize = top / 2;
    int **result = (int **)malloc(sizeof(int *) * resultSize);
    int *columnSizes = (int *)malloc(sizeof(int) * resultSize);

    for (int i = 0; i < resultSize; i++) {
        columnSizes[i] = 2;
        int *pair = (int *)malloc(sizeof(int) * 2);
        pair[0] = stack[2 * i];
        pair[1] = stack[2 * i + 1];
        result[i] = pair;
    }

    *returnSize = resultSize;
    *returnColumnSizes = columnSizes;
    return result;
}