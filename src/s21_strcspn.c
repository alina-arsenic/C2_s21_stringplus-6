#include "s21_string.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
    s21_size_t length = 0;
    int i = 0, j = 0, k = 0;
    for (; str1[i]; i++) {
        for (j = 0; str2[j]; j++) {
            if (str1[i] == str2[j]) {
                k = 1;
                break;
            }
        }
        if (k == 1)
            break;
        length++;
    }
    return length;
}
