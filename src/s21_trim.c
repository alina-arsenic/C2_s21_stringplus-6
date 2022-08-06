#include "s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
    char *buffer = s21_NULL;
    if (src != s21_NULL && trim_chars != s21_NULL) {
        s21_size_t len = s21_strlen(src);
        int left = 0, n = len;
        for (s21_size_t i = 0; i < len; i++) {
            if (s21_strchr(trim_chars, src[i]) == s21_NULL) {
                left = i;
                break;
            } else {
                n--;
            }
        }
        for (int i = len - 1; i > left; i--) {
            if (s21_strchr(trim_chars, src[i]) == s21_NULL)
                break;
            else
                n--;
        }
        if (n < 0)
            n = 0;
        buffer = malloc(sizeof(char*) * (n + 1));
        s21_memcpy(buffer, src + left, n);
        buffer[n] = '\0';
    }
    return buffer;
}
