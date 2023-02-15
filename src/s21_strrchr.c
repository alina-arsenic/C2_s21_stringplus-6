#include "s21_string.h"

char *s21_strrchr(const char *str, int c) {
  char *result = s21_NULL;
  for (; *str; str++)
    if (*str == c) result = (char *)str;
  if (*str == c) result = (char *)str;
  return result;
}
