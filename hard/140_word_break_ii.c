#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
int isInDict(char *s, int sLength, char **wordDict, int *lengths, int wordDictSize) {
    for (int i = 0; i < wordDictSize; i++) {
        if (sLength == lengths[i] && strncmp(s, wordDict[i], sLength) == 0) {
            return 1;
        }
    }
    return 0;
}

char **construct(char **list, int *listLength, int *capacity, char *str, int strLength, int row, int col, int **dp, char *s) {
    int sLength = strlen(s);
    int maxLength = sLength * 2;
    if (col == sLength) {
        str[strLength - 1] = '\0';
        list[*listLength] = str;
        *listLength += 1;
        if (*listLength == *capacity) {
            *capacity *= 2;
            list = realloc(list, sizeof(char *) * *capacity);
        }
        return list;
    }

    for (int i = col; i < sLength; i++) {
        if (dp[row][i] == i + 1) {
            int wordLength = i - col + 1;
            char *prefix = (char *)malloc(sizeof(char) * maxLength);
            strncpy(prefix, str, strLength);
            strncpy(prefix + strLength, s + col, wordLength);
            int newLength = strLength + wordLength;
            prefix[newLength++] = ' ';
            list = construct(list, listLength, capacity, prefix, newLength, i + 1, i + 1, dp, s);
        }
    }
    return list;
}
*/

typedef struct {
    int size;
    int *nums;
} List;

List *newList(int capacity) {
    List *list = (List *)malloc(sizeof(List));
    list->size = 0;
    list->nums = (int *)malloc(sizeof(int) * capacity);
    return list;
}

void insert(List *list, int num) {
    list->nums[list->size++] = num;
}

char **build(char **list, int *listLength, int *capacity, char *str, int strLength, int row, List **dp, char *s, int sLength) {
    if (row < 0) {
        str[strLength - 1] = '\0';
        list[*listLength] = str;
        *listLength += 1;
        if (*listLength == *capacity) {
            *capacity *= 2;
            list = realloc(list, sizeof(char *) * *capacity);
        }
        return list;
    }
    int maxLength = 2 * sLength;
    for (int i = 0; i < dp[row]->size; i++) {
        int len = row - dp[row]->nums[i] + 1;
        char *suffix = (char *)malloc(sizeof(char) * maxLength);
        strncpy(suffix, s + dp[row]->nums[i], len);
        suffix[len++] = ' ';
        strncpy(suffix + len, str, strLength);
        list = build(list, listLength, capacity, suffix, len + strLength, dp[row]->nums[i] - 1, dp, s, sLength);
    }
    return list;
}

char **helper(char *s, int *lengths, char **wordDict, int wordDictSize, int *returnSize) {
    int sLength = strlen(s);
    List **dp = (List **)malloc(sizeof(List *) * sLength);
    for (int i = 0; i < sLength; i++) {
        dp[i] = newList(sLength);
    }

    for (int i = 0; i < sLength; i++) {
        for (int j = 0; j < wordDictSize; j++) {
            int start = i - lengths[j] + 1;
            if (start < 0 || strncmp(s + start, wordDict[j], lengths[j])) {
                continue;
            }
            if (start == 0 || dp[start - 1]->size) {
                insert(dp[i], start);
            }
        }
    }

    for (int i = 0; i < sLength; i++) {
        for (int j = 0; j < dp[i]->size; j++) {
            printf("%d ", dp[i]->nums[j]);
        }
        printf("\n");
    }

    int capacity = 16;
    char **res = (char **)malloc(sizeof(char *) * capacity);
    int listLength = 0;
    res = build(res, &listLength, &capacity, "", 0, sLength - 1, dp, s, sLength);
//    res = construct(res, &listLength, &capacity, "", 0, 0, 0, dp, s);

//    printf("capacity: %d\n", capacity);
    *returnSize = listLength;
    return res;
}

char **wordBreak(char *s, char **wordDict, int wordDictSize, int *returnSize) {
    if (!wordDictSize) {
        *returnSize = 0;
        return NULL;
    }
    int lengths[wordDictSize];
    for (int i = 0; i < wordDictSize; i++) {
        lengths[i] = strlen(wordDict[i]);
    }
    return helper(s, lengths, wordDict, wordDictSize, returnSize);
}

int main() {
    char *s = "catsanddog";
//    char *s = "catsandog";
    char *wordDict[] = {"cat", "cats", "and", "sand", "dog"};
//    char *s = "pineapplepenapple";
//    char *wordDict[] = {"apple", "pen", "applepen", "pine", "pineapple"};
    int wordDictSize = 5;

//    char *s = "a";
//    char *wordDict[] = {"a"};
//    int wordDictSize = 1;

//    char *s = "aaaaaaa";
//    char *wordDict[] = {"aaaa","aa","a"};
//    int wordDictSize = 3;

//    char *s = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
//    char *wordDict[] = {"a","aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa"};
//    int wordDictSize = 10;

    int returnSize = 0;
    char **res = wordBreak(s, wordDict, wordDictSize, &returnSize);
    printf("return size: %d\n", returnSize);
    for (int i = 0; i < returnSize; i++) {
        printf("%d: %s\n", i, res[i]);
    }
    return 0;
}
