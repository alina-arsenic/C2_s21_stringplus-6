#include "s21_string.h"

int is_delim(char c, const char *delim) {
    int result = 0;
    while (*delim) {
        if (c == *delim)
            result = 1;
        delim++;
    }
    return result;
}

char *s21_strtok(char *str, const char *delim) {
    char *result = s21_NULL;
    static char *backup_string;
    if (!str) {
        str = backup_string;
    }
    if (str) {
        int end_flag = 0;
        while (is_delim(*str, delim)) {  // find the first non-delim character
            str++;
        }
        if (*str == 0) {
            end_flag = 1;  // there's no delim in str
        } else {
            result = str;  // the begining of result is the current begining of str
        }

        while (!end_flag) {  // change the end of str/result and remember backup_string
            if (*str == 0) {
                backup_string = str;
                break;
            }
            if (is_delim(*str, delim)) {
                *str = 0;
                backup_string = str + 1;
                break;
            }
            str++;
        }
    }
    return result;
}
