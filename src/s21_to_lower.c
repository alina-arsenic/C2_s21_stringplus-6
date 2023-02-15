#include "s21_string.h"

int s21_isupper(char ch) {
    int status = 0;
    if (ch > 64 && ch < 91)
        status = 1;
    return status;
}

void *s21_to_lower(const char *str) {
    char *buffer = s21_NULL;
    if (str != s21_NULL) {
        s21_size_t len = s21_strlen(str), i = 0;
        buffer = malloc((len + 1)*sizeof(char));
        for (; i < len + 1; i++) {
            buffer[i] = (s21_isupper(str[i]) == 1) ? str[i] + 32 : str[i];
        }
    }
    return buffer;
}
