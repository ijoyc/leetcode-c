/*
 * Created Date: Tuesday June 9th 2020
 * Author: yizhuoc
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void dfs(char **result, int *index, char *buf, int length, int i, int diff) {
    if (i == length) {
        result[(*index)++] = strdup(buf);
        return;
    }

    // currently we have i characters, still need at least 'diff' right parentheses
    // if this summation is still less than length, we can put more left parentheses
    if (i + diff < length) {
        buf[i] = '(';
        dfs(result, index, buf, length, i + 1, diff + 1);
    }
    if (diff > 0) {
        buf[i] = ')';
        dfs(result, index, buf, length, i + 1, diff - 1);
    }
}

// learn by solution
char **generateParenthesis(int n, int *returnSize) {
    // Catalan Number: C(2n, n) - C(2n, n + 1) = C(2n, n) / (n + 1)
    int size = 1;
    for (int i = 2; i <= n; i++) {
        size *= (i + n);
    }
    for (int i = 2; i <= n; i++) {
        size /= i;
    }
    *returnSize = size;

    int length = n << 1;
    char **result = (char **)malloc(sizeof(char *) * size);
    char *buf = (char *)malloc(sizeof(char) * (length + 1));
    buf[length] = '\0';
    int index = 0;
    dfs(result, &index, buf, length, 0, 0);

    return result;
}