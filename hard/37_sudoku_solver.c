/*
* @Author: chenyizhuo.yizhuoc
* @Date:   2020-12-29 14:32:50
* @Last Modified by:   chenyizhuo.yizhuoc
* @Last Modified time: 2020-12-29 18:15:42
*/


#define DIM 9
#define BLOCK 3

int isValid(char **board, int i, int j, char num) {
    for (int col = 0; col < DIM; col++) {
        if (board[i][col] == num) {
            return 0;
        }
    }
    for (int row = 0; row < DIM; row++) {
        if (board[row][j] == num) {
            return 0;
        }
    }

    int blockRow = i / BLOCK * BLOCK;
    int blockColumn = j / BLOCK * BLOCK;
    for (int row = blockRow; row < blockRow + BLOCK; row++) {
        for (int col = blockColumn; col < blockColumn + BLOCK; col++) {
            if (board[row][col] == num) {
                return 0;
            }
        }
    }
    return 1;
}

int backtracking(char **board, int index) {
    if (index >= DIM * DIM) {
        return 1;
    }
    
    int i = index / DIM;
    int j = index % DIM;
    int success = 0;

    if (board[i][j] == '.') {
        for (int num = 1; num <= DIM; num++) {
            if (isValid(board, i, j, num + '0')) {
                board[i][j] = num + '0';
                success = success || backtracking(board, index + 1);
                if (success) {
                    break;
                }
                board[i][j] = '.';
            }
        }
    } else {
        success = backtracking(board, index + 1);
    }
    return success;
}

void solveSudoku(char **board, int boardSize, int *boardColSize) {
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            if (backtracking(board, i * DIM + j)) {
                return;
            }
        }
    }
}