/*
 * Created Date: Friday Aug 14th 2020
 * Author: yizhuoc
 */

#include <stdlib.h>
#include <string.h>

char *longestPalindrome(char *s) {
    int length = strlen(s);
      
    // P(i, j) = true if P(i + 1, j - 1) && s[i] == s[j]
    // P(i, i) = true
    // P(i, i + 1) = s[i] == s[i + 1]
    
    // To decrease space complexity to O(n)
    int *even = (int *)malloc(sizeof(int) * length);
    int *odd = (int *)malloc(sizeof(int) * length);
    
    int max = 1;
    char *start = s;
    for (int i = 0; i < length; i++) {
        even[i] = 1;
        if (i + 1 < length) {
            odd[i] = s[i] == s[i + 1];
            if (odd[i] && max == 1) {
                max = 2;
                start = s + i;
            }
        }
    }
    
    int index = 1;
    for (int i = 0; i < length - 2; i++) {
        int *p = (i & 1) ? odd : even;
        if (i != 0 && (i & 1) == 0) {
            index++;
        }
        for (int j = i + 2, k = 0; j < length; j++, k++) {
            int dpIndex = k + index;
            p[dpIndex] = p[dpIndex] && s[k] == s[j];
            if (p[dpIndex]) {
                int current = j - k + 1;
                if (current > max) {
                    max = current;
                    start = s + k;
                }
            }
        }
    }
    
    char *result = (char *)malloc(sizeof(char) * (max + 1));
    memcpy(result, start, max);
    result[max] = '\0';
    
    return result;
}