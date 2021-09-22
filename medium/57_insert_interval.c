
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int **copy(int **intervals, int intervalsSize, int *newInterval) {
    int **result = (int **)malloc(sizeof(int *) * (intervalsSize + 1));
    for (int i = 0; i < intervalsSize; i++) {
        result[i] = (int *)malloc(sizeof(int) * 2);
        result[i][0] = intervals[i][0];
        result[i][1] = intervals[i][1];
    }
    result[intervalsSize] = (int *)malloc(sizeof(int) * 2);
    result[intervalsSize][0] = newInterval[0];
    result[intervalsSize][1] = newInterval[1];
    return result;
}

int cmp(const void *a, const void *b) {
    int *first = *(int **)a;
    int *second = *(int **)b;
    return first[0] - second[0];
}

int **insert(int **intervals, int intervalsSize, int *intervalsColSize, int *newInterval, int newIntervalSize, int *returnSize, int **returnColumnSizes) {
    int **target = copy(intervals, intervalsSize, newInterval);
    qsort(target, intervalsSize + 1, sizeof(int *), cmp);

    int i = 0;
    int j = 1;
    while (j < intervalsSize + 1) {
        if (target[j][0] > target[i][1]) {
            i++;
            target[i][0] = target[j][0];
            target[i][1] = target[j][1];
            j++;
            continue;
        }
        target[i][0] = MIN(target[i][0], target[j][0]);
        target[i][1] = MAX(target[i][1], target[j][1]);
        j++;
    }

    int total = i + 1;
    *returnSize = total;
    int *columnSizes = (int *)malloc(sizeof(int) * total);
    for (int i = 0; i < total; i++) {
        columnSizes[i] = 2;
    }
    *returnColumnSizes = columnSizes;
    return target;
}