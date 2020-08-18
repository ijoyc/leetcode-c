
int maxAreaInHistogram(int *heights, int length, int *stack) {
  stack[0] = 0;
  int stackTop = 1;
  int i = 1;

  int max = 0;
  for (; i < length; i++) {
    while (stackTop && heights[stack[stackTop - 1]] > heights[i]) {
      int top = stack[--stackTop];
      int area = (stackTop ? i - 1 - stack[stackTop - 1] : i) * heights[top];
      max = max > area ? max : area;
    }
    stack[stackTop++] = i;
  }

  while (stackTop) {
    int top = stack[--stackTop];
    int area = (stackTop ? i - 1 - stack[stackTop - 1] : i) * heights[top];
    max = max > area ? max : area;
  }

  return max;
}


int maximalRectangle(char** matrix, int matrixSize, int* matrixColSize) {
  if (matrixSize == 0) {
    return 0;
  }

  int column = *matrixColSize;
  int *stack = (int *)malloc(sizeof(int) * column);
  int *heights = (int *)calloc(column, sizeof(int));
  int max = 0;

  for (int i = 0; i < matrixSize; i++) {
    for (int j = 0; j < column; j++) {
      heights[j] = matrix[i][j] == '1' ? heights[j] + 1 : 0;
    }

    int area = maxAreaInHistogram(heights, column, stack);
    max = max > area ? max : area;
  }

  free(stack);
  free(heights);
  return max;
}