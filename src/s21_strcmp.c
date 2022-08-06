#include "s21_string.h"

int s21_strcmp(const char *str1, const char *str2) {
    int i = 0, r = 0;
    do {
        r = str1[i] - str2[i];
        if (r > 0 || r < 0)
            break;
        else
            i++;
    } while (str1[i] != '\0' || str2[i] != '\0');
    return r;
}
