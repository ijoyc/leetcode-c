/*
* @Author: chenyizhuo.yizhuoc
* @Date:   2021-05-26 10:52:59
* @Last Modified by:   chenyizhuo.yizhuoc
* @Last Modified time: 2021-05-28 10:43:36
*/

int searchMatrix(int **matrix, int matrixSize, int *matrixColSize, int target) {
    int row = 0;
    int col = *matrixColSize - 1;
    while (row < matrixSize && col >= 0) {
        if (matrix[row][col] == target) {
            return 1;
        } else if (matrix[row][col] > target) {
            col--;
        } else {
            row++;
        }
    }
    return 0;
}