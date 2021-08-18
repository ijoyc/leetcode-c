
#define STACK_INITIAL_CAPACITY 16
#define MIN(x, y) ((x) < (y) ? (x): (y))

typedef struct {
    int *values;
    int top;
    int capacity;
} Stack;

Stack *NewStack() {
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->values = (int *)malloc(sizeof(int) * STACK_INITIAL_CAPACITY);
    s->top = 0;
    s->capacity = STACK_INITIAL_CAPACITY;
    return s;
}

void Push(Stack *s, int value) {
    if (s->top == s->capacity) {
        s->capacity *= 2;
        s->values = (int *)realloc(s->values, sizeof(int) * s->capacity);
    }
    s->values[s->top] = value;
    s->top += 1;
}

int Pop(Stack *s) {
    if (s->top == 0) {
        return -1;
    }
    s->top -= 1;
    return s->values[s->top];
}

int Top(Stack *s) {
    if (s->top == 0) {
        return -1;
    }
    return s->values[s->top - 1];
}

void FreeStack(Stack *s) {
    free(s->values);
    free(s);
}

int trap(int *height, int heightSize) {
    Stack *s = NewStack();
    int result = 0;

    for (int i = 0; i < heightSize; i++) {
        while (s->top != 0 && height[Top(s)] < height[i]) {
            int currentIndex = Pop(s);
            if (s->top == 0) {
                break;
            }
            int left = height[Top(s)];
            int right = height[i];
            result += (MIN(left, right) - height[currentIndex]) * ((i - Top(s) - 1));
        }
        Push(s, i);
    }

    FreeStack(s);
    return result;
}


int trap2(int *height, int heightSize) {
    int left = 0;
    int right = heightSize - 1;
    int leftMax = -1;
    int rightMax = -1;
    int result = 0;

    while (left < right) {
        if (height[left] < height[right]) {
            if (height[left] > leftMax) {
                leftMax = height[left];
            } else {
                result += leftMax - height[left];
            }
            left++;
        } else {
            if (height[right] > rightMax) {
                rightMax = height[right];
            } else {
                result += rightMax - height[right];
            }
            right--;
        }
    }

    return result;
}
