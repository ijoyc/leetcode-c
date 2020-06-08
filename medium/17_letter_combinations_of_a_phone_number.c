/*
 * Created Date: Monday June 8th 2020
 * Author: yizhuoc
 */

#include <stdlib.h>
#include <string.h>


static int nums[] = { 1, 3, 3, 3, 3, 3, 4, 3, 4 };
static char *dict[] = {
    "",
    "abc",
    "def",
    "ghi",
    "jkl",
    "mno",
    "pqrs",
    "tuv",
    "wxyz"
};

void permutation(char *digits, char *container, int pos, int n, char **result, int *currentIndex) {
    if (pos == n) {
        char *item = (char *)malloc(sizeof(char) * (n + 1));
        
        int j = 0;
        for (int i = 0; i < n; i++) {
            if (container[i] != ' ') {
                item[j++] = container[i];
            }
        }
        item[j] = '\0';
        
        result[*currentIndex] = item;
        *currentIndex = *currentIndex + 1;
        return;
    }
    int digit = digits[pos] - '1';
    if (nums[digit] == 0) {
        container[pos] = ' ';
        permutation(digits, container, pos + 1, n, result, currentIndex);
        return;
    }

    for (int j = 0; j < nums[digit]; j++) {
        container[pos] = dict[digit][j];
        permutation(digits, container, pos + 1, n, result, currentIndex);
    }
}

char **letterCombinations(char *digits, int *returnSize) {
    int size = 1;
    int length = strlen(digits);
    if (length == 0) {
        *returnSize = 0;
        return NULL;
    }
    
    for (int i = 0; i < length; i++) {
        size *= nums[digits[i] - '1'];
    }
    *returnSize = size;

    char **result = (char **)malloc(sizeof(char *) * size);
    char *container = (char *)malloc(sizeof(char) * (size + 1));
    int currentIndex = 0;

    permutation(digits, container, 0, length, result, &currentIndex);

    return result;
}