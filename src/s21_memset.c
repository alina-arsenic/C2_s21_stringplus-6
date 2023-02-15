#include "s21_string.h"

void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *str0 = s21_NULL;
  if (str == s21_NULL) {
  } else {
    str0 = (unsigned char *)str;
    while (n--) *(unsigned char *)str++ = c;
  }
  return ((void *)str0);
}
