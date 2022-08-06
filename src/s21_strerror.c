#include "s21_string.h"

char *s21_strerror(int errnum) {
    int errlist_num = sizeof(ERRLIST)/sizeof(ERRLIST[1]);
    char *p = s21_NULL;
    char error[256] = ERROR;
    char number[256];
    if (errnum < errlist_num && errnum >= 0) {
        p = (char *)ERRLIST[errnum];
    } else {
      int len = 0, f = 10, h = 1, n = errnum, d = 0, k = 0;
      do {
          errnum /= 10;
          len++;
      } while (errnum != 0);
      k = len - 1;
      if (n < 0) {
          n *= -1;
          number[0] = 45;
          k = len;
          d = 1;
      }
      number[k + 1] = 0;
      for (int j = k; j >= d; j--) {
          number[j] = ((n % f) / h) + '0';
          f *= 10;
          h *= 10;
      }
      s21_strcat(error, number);
      p = (char*)&error[0];
    }
    return p;
}
