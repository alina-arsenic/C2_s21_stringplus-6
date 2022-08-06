#include "s21_string.h"

char *s21_strchr(const char *str, int c) {
  char *result = s21_NULL;
  for (; *str; str++)
    if (*str == (char)c) {
      result = (char *)str;
      break;
    }
  if (!result && *str == (char)c) result = (char *)str;
  return result;
}
