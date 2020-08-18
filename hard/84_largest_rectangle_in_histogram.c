
int largestRectangleArea(int *heights, int heightsSize) {
  if (!heightsSize) {
    return 0;
  }

  int *stack = (int *)malloc(sizeof(int) * heightsSize);
  stack[0] = 0;
  int stackTop = 1;
  int max = 0;

  int i = 1;
  for (; i < heightsSize; i++) {
    while (stackTop && heights[stack[stackTop - 1]] > heights[i]) {
      int top = stack[--stackTop];
      int area = heights[top] * (stackTop == 0 ? i : (i - stack[stackTop - 1] - 1));
      max = max > area ? max : area;
    }
    stack[stackTop++] = i;
  }

  while (stackTop) {
    int top = stack[--stackTop];
    int area = heights[top] * (stackTop == 0 ? i : (i - stack[stackTop - 1] - 1));
    max = max > area ? max : area;
  }

  free(stack);
  return max;
}