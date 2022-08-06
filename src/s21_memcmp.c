#include "s21_string.h"

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  int cmp = 0;
  if (str1 == s21_NULL && str2 == s21_NULL) {
  } else {
    while (n--) {
      if (*(unsigned const char *)str1++ != *(unsigned const char *)str2++) {
        cmp = (*(unsigned const char *)--str1 - *(unsigned const char *)--str2);
        break;
      }
    }
  }
  return cmp;
}
