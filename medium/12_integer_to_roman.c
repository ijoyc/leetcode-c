/*
 * Created Date: Saturday June 6th 2020
 * Author: yizhuoc
 */

#include <stdio.h>

#define LENGTH 20

char *intToRoman(int num) {
    char *dict[] = {
        "IVX",
        "XLC",
        "CDM",
        "M"
    };
    char result[LENGTH] = { 0 };
    int i = LENGTH - 2;
    int row = 0;
    while (num) {
        int digit = num % 10;

        char *values = dict[row];
        if (digit >= 1 && digit <= 3) {
            for (int j = 0; j < digit; j++) {
                result[i--] = values[0];
            }
        } else if (digit == 4) {
            result[i--] = values[1];
            result[i--] = values[0];
        } else if (digit == 9) {
            result[i--] = values[2];
            result[i--] = values[0];
        } else if (digit) {
            for (int j = 0; j < digit - 5; j++) {
                result[i--] = values[0];
            }
            result[i--] = values[1];
        }

        num /= 10;
        row++;
    }
    return result + i + 1;
}