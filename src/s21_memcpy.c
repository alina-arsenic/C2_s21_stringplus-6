#include "s21_string.h"

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  unsigned char *dest0 = s21_NULL;
  if (dest == s21_NULL && src == s21_NULL) {
  } else {
    dest0 = (unsigned char *)dest;
    while (n--) *(unsigned char *)dest++ = *(unsigned const char *)src++;
  }
  return ((void *)dest0);
}
