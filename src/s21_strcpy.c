#include "s21_string.h"

char *s21_strcpy(char *dest, const char *src) {
  for (char *tmp_dest = dest; (*tmp_dest = *src); tmp_dest++, src++) continue;
  return dest;
}
