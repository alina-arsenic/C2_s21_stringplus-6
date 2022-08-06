#include "s21_string.h"

s21_size_t s21_strspn(const char *str1, const char *str2) {
  s21_size_t result = 0;
  for (; *str1 && s21_strchr(str2, *str1); str1++, result++) continue;
  return result;
}
