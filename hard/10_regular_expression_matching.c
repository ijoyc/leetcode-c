/*
 * Created Date: Saturday June 6th 2020
 * Author: yizhuoc
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
Given an input string (s) and a pattern (p), implement regular expression matching with support for '.' and '*'.

'.' Matches any single character.
'*' Matches zero or more of the preceding element.
The matching should cover the entire input string (not partial).

Note:

s could be empty and contains only lowercase letters a-z.
p could be empty and contains only lowercase letters a-z, and characters like . or *.
*/

// learn from solution
int isMatch(char *s, char *p) {
    int slength = strlen(s);
    int plength = strlen(p);
    int **dp = (int **)malloc(sizeof(int *) * (slength + 1));
    for (int i = 0; i <= slength; i++) {
        dp[i] = (int *)calloc(plength + 1, sizeof(int));
    }

    dp[slength][plength] = 1;
    // dp[i from 0 to slength - 1][plength] = 0

    for (int i = slength; i >= 0; i--) {
        for (int j = plength - 1; j >= 0; j--) {
            int isCurrentMatch = i < slength && (s[i] == p[j] || p[j] == '.');
            if (p[j + 1] == '*') {
                dp[i][j] = dp[i][j + 2] || (isCurrentMatch && dp[i + 1][j]);
            } else if (isCurrentMatch) {
                dp[i][j] = dp[i + 1][j + 1];
            } else {
                dp[i][j] = 0;
            }
        }
    }

    // for (int i = 0; i <= slength; i++) {
        // for (int j = 0; j <= plength; j++) {
            // printf("%d ", dp[i][j]);
        // }
        // printf("\n");
    // }
    
    int result = dp[0][0];
    for (int i = 0; i <= slength; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}