
int isValidAt(char **board, int boardSize, int *boardColSize, int i, int j) {
    if (board[i][j] == '.') {
        return 1;
    }
    for (int k = i + 1; k < boardSize; k++) {
        if (board[k][j] == board[i][j]) {
            return 0;
        }
    }
    for (int k = j + 1; k < *boardColSize; k++) {
        if (board[i][k] == board[i][j]) {
            return 0;
        }
    }
    int gridI = i / 3 * 3;
    int gridJ = j / 3 * 3;
    for (int m = gridI; m < gridI + 3; m++) {
        for (int n = gridJ; n < gridJ + 3; n++) {
            if (m == i && n == j) {
                continue;
            }
            if (board[m][n] == board[i][j]) {
                return 0;
            }
        }
    }
    return 1;
}

int isValidSudoku(char **board, int boardSize, int *boardColSize) {
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardColSize[i]; j++) {
            if (!isValidAt(board, boardSize, boardColSize, i, j)) {
                return 0;
            }
        }
    }
    return 1;
}