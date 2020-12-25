/*
* @Author: chenyizhuo.yizhuoc
* @Date:   2020-12-21 11:41:14
* @Last Modified by:   chenyizhuo.yizhuoc
* @Last Modified time: 2020-12-25 12:43:35
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char **copy(char **current, int currentSize) {
	char **result = (char **)malloc(sizeof(char *) * currentSize);
	memcpy(result, current, sizeof(char *) * currentSize);
	return result;
}

void backtracking(char *s, int start, int length, int **dp, char **current, int currentSize, char ****result, int *size, int *capacity, int **returnColumnSizes) {
	if (start == length) {
		if (*size == *capacity) {
			int newCapacity = *capacity * 2;
			*result = (char ***)realloc(*result, sizeof(char **) * newCapacity);
			*returnColumnSizes = (int *)realloc(*returnColumnSizes, sizeof(int) * newCapacity);
			*capacity = newCapacity;
		}
		(*result)[*size] = copy(current, currentSize);
		(*returnColumnSizes)[*size] = currentSize;
		*size += 1;
		return;
	}

	for (int i = start; i < length; i++) {
		if (dp[start][i]) {
			int len = i - start + 1;
			char *sub = (char *)malloc(sizeof(char) * (len + 1));
			strncpy(sub, s + start, len);
			sub[len] = '\0';

			current[currentSize++] = sub;
			backtracking(s, i + 1, length, dp, current, currentSize, result, size, capacity, returnColumnSizes);
			currentSize--;
		}
	}
}

char ***partition(char *s, int *returnSize, int **returnColumnSizes) {
	int length = strlen(s);
	int **dp = (int **)malloc(sizeof(int *) * length);
	for (int i = 0; i < length; i++) {
		dp[i] = (int *)calloc(length, sizeof(int));
	}
	for (int i = 0; i < length; i++) {
		dp[i][i] = 1;
		if (i + 1 < length) {
			dp[i][i + 1] = s[i] == s[i + 1];
		}
	}
	for (int k = 2; k < length; k++) {
		for (int i = 0; i < length - k; i++) {
			int j = i + k;
			dp[i][j] = s[i] == s[j] ? dp[i + 1][j - 1] : 0;
		}
	}

	int capacity = 16;
	char ***result = (char ***)malloc(sizeof(char **) * capacity);
	int *columnSizes = (int *)malloc(sizeof(int) * capacity);
	int size = 0;
	char **current = (char **)malloc(sizeof(char *) * length);

	backtracking(s, 0, length, dp, current, 0, &result, &size, &capacity, &columnSizes);

	for (int i = 0; i < length; i++) {
		free(dp[i]);
	}
	free(dp);
	free(current);

	*returnSize = size;
	*returnColumnSizes = columnSizes;
	return result;
}

int main() {
	char *s = "ababaaabba";

	int returnSize = 0;
	int *returnColumnSizes;
	char ***result = partition(s, &returnSize, &returnColumnSizes);

	printf("result: %d\n", returnSize);
	for (int i = 0; i < returnSize; i++) {
		if (returnColumnSizes[i] == 0) {
			printf("[]\n");
			continue;
		}

		for (int j = 0; j < returnColumnSizes[i]; j++) {
			printf("%s ", result[i][j]);
		}
		printf("\n");
	}
	return 0;
}