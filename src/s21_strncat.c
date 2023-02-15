#include "s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
    char *str = dest;
    while (*dest) {
        dest++;
    }
    while (n) {
        *dest = *src;
        dest++;
        src++;
        n--;
    }
    if (!n) {
        *dest = '\0';
    }
    return str;
}
