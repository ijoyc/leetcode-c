/*
 * Created Date: Friday June 5th 2020
 * Author: yizhuoc
 */

#include <stdio.h>
#include <limits.h>

int myAtoi(char *str) {
    long result = 0;
    int sign = 1;

    while (*str == ' ') {
        str++;
    }

    if (*str == '-') {
        sign = -1;
        str++;
    } else if (*str == '+') {
        str++;
    }

    while (*str >= '0' && *str <= '9') {
        result = result * 10 + (*str - '0');
        
        if (result > INT_MAX) {
            return sign == 1 ? INT_MAX : INT_MIN;
        }
        str++;
    }

    return sign * result;
}