#include "s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  char *result = s21_NULL;
  if (*needle == '\0') {
    result = (char *)haystack;
  } else {
    for (; *haystack; haystack++) {
      const char *h, *n;
      for (h = haystack, n = needle; *h && *n && (*h == *n); h++, n++) continue;
      if (*n == '\0') {
        result = (char *)haystack;
        break;
      }
    }
  }
  return result;
}
