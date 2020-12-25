/*
* @Author: chenyizhuo.yizhuoc
* @Date:   2020-12-25 17:01:54
* @Last Modified by:   chenyizhuo.yizhuoc
* @Last Modified time: 2020-12-25 17:32:54
*/

int isLocationAvailable(int row, int col, int n, char *queues) {
	for (int i = 0; i < row; i++) {
		if (queues[i * n + col]) {
			return 0;
		}
	}
	for (int i = 0; i < col; i++) {
		if (queues[row * n + i]) {
			return 0;
		}
	}
	int i = row - 1;
	int j = col - 1;
	while (i >= 0 && j >= 0) {
		if (queues[i * n + j]) {
			return 0;
		}
		i--;
		j--;
	}
	i = row - 1;
	j = col + 1;
	while (i >= 0 && j < n) {
		if (queues[i * n + j]) {
			return 0;
		}
		i--;
		j++;
	}
	return 1;
}

int backtracking(int row, int n, int count, char *queues) {
	if (row == n) {
		return count + 1;
	}
	for (int i = 0; i < n; i++) {
		if (isLocationAvailable(row, i, n, queues)) {
			queues[row * n + i] = 1;
			count = backtracking(row + 1, n, count, queues);
			queues[row * n + i] = 0;
		}
	}
	return count;
}

int totalNQueens(int n) {
	char *queues = (char *)calloc(n * n, sizeof(char));
	return backtracking(0, n, 0, queues);
}