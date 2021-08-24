

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */



int isValid(int n, char **board, int row, int column) {
    for (int i = 0; i < n; i++) {
        if (i != row && board[i][column] == 'Q') {
            return 0;
        }
    }
    for (int i = 0; i < n; i++) {
        if (i != column && board[row][i] == 'Q') {
            return 0;
        }
    }
    for (int i = 1; row >= i && column >= i; i++) {
        if (board[row - i][column - i] == 'Q') {
            return 0;
        }
    }
    for (int i = 1; row >= i && column + i < n; i++) {
        if (board[row - i][column + i] == 'Q') {
            return 0;
        }
    }
    return 1;
}

char **copy(char **board, int n) {
    char **result = (char **)malloc(sizeof(char *) * n);
    for (int i = 0; i < n; i++) {
        result[i] = (char *)malloc(sizeof(char) * (n + 1));
        memcpy(result[i], board[i], sizeof(char) * n);
        result[i][n] = '\0';
    }
    return result;
}

void backtracking(int n, char **board, int row, int *size, char ***result) {
    if (row == n) {
        result[*size] = copy(board, n);
        *size += 1;
        return;
    }

    for (int i = 0; i < n; i++) {
        if (isValid(n, board, row, i)) {
            board[row][i] = 'Q';
            backtracking(n, board, row + 1, size, result);
            board[row][i] = '.';
        }
    }
}

char ***solveNQueens(int n, int *returnSize, int **returnColumnSizes) {
    int size = 0;
    char ***result = (char ***)malloc(sizeof(char **) * 360);

    char **board = (char **)malloc(sizeof(char *) * n);
    for (int i = 0; i < n; i++) {
        board[i] = (char *)malloc(sizeof(char) * n);
        memset(board[i], '.', n);
    }

    backtracking(n, board, 0, &size, result);

    *returnSize = size;
    *returnColumnSizes = (int *)malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++) {
        (*returnColumnSizes)[i] = n;
    }
    return result;
}