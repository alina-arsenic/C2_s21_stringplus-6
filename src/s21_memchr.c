#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  unsigned const char *str0 = s21_NULL;
  if (str == s21_NULL) {
  } else {
    while (n--) {
      if (*(unsigned const char *)str++ == (unsigned char)c)
        str0 = (unsigned const char *)--str;
    }
  }
  return ((void *)str0);
}
