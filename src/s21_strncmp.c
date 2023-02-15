#include "s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
    int r = 0;
    for (s21_size_t i = 0; i < n; i++) {
        r = str1[i] - str2[i];
        if (r != 0)
            break;
    }
    return r;
}
