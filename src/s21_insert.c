#include "s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
    char *buffer = s21_NULL;
    if (src != s21_NULL && str != s21_NULL) {
        s21_size_t len2 = s21_strlen(str), len1 = s21_strlen(src);
        if (start_index <= len1) {
            buffer = malloc((len1 + len2 + 1)*sizeof(char));
            s21_memcpy(buffer, src, start_index);
            s21_strcpy(&buffer[start_index], str);
            s21_strcpy(&buffer[start_index + len2], &src[start_index]);
        }
    }
    return buffer;
}
