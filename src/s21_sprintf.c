#include <math.h>
#include <stdio.h>
#include "s21_string.h"

void set_to_zero(t_struct *format_spec) {
  format_spec->i = 0;
  format_spec->nprinted = 0;
  format_spec->minus = 0;
  format_spec->width = 0;
  format_spec->precisiontf = 0;
  format_spec->precision = 0;
  format_spec->size = 0;
  format_spec->plus = 0;
  format_spec->space = 0;
}

void set_to_zero2(t_struct *format_spec) {
  format_spec->minus = 0;
  format_spec->width = 0;
  format_spec->precisiontf = 0;
  format_spec->precision = 0;
  format_spec->size = 0;
  format_spec->plus = 0;
  format_spec->space = 0;
}

int s21_atoi(const char *nptr) {
  int res = 0;
  int sign = 1;
  if (nptr != NULL) {
    while (*nptr == '\f' || *nptr == '\n' || *nptr == '\r' || *nptr == '\t' ||
           *nptr == '\v' || *nptr == 32)
      nptr++;
    if (*nptr == '-' || *nptr == '+') {
      if (*nptr == '-') sign = -1;
      nptr++;
    }
    while (*nptr >= '0' && *nptr <= '9') {
      res = res * 10 + *nptr - 48;
      nptr++;
    }
  }
  return (res * sign);
}

int spec_pars(t_struct *format_spec, int pos, const char *format, va_list ap,
              char *str) {
  format_spec->i = pos;
  if (!s21_strchr(TYPESPEC, format[pos])) {
    set_modifiers(format, format_spec);
  } else if (s21_strchr(TYPESPEC, format[pos])) {
    converting(format[pos], ap, format_spec, str);
    set_to_zero2(format_spec);
  }
  return (format_spec->i - 1);
}

int formatparse(const char *format, t_struct *format_spec, va_list ap, int pos,
                char *str) {
  while (format[pos] != '\0') {
    if (format[pos] != '%' && format[pos]) {
      format_spec->nprinted +=
          addtostr(str + format_spec->nprinted, &format[pos], 1);
    } else if (format[pos] == '%') {
      if (!s21_strchr(ALLSYMBOLS, format[pos + 1])) break;
      while (s21_strchr(ALLSYMBOLS, format[pos + 1])) {
        pos = pos + 1;
        if (s21_strchr(TYPESPEC, format[pos])) {
          pos = spec_pars(format_spec, pos, format, ap, str) + 2;
          break;
        } else {
        }
        pos = spec_pars(format_spec, pos, format, ap, str);
      }
      continue;
    }
    pos++;
  }
  str[format_spec->nprinted] = '\0';
  return (format_spec->nprinted);
}

int addtostr(void *str, const void *c, s21_size_t n) {
  s21_memcpy(str, c, n);
  return n;
}

void flags(const char *format, t_struct *format_spec) {
  while (s21_strchr("-+ ", format[format_spec->i])) {
    if (format[format_spec->i] == '-') format_spec->minus = 1;
    if (format[format_spec->i] == '+') format_spec->plus = 1;
    if (format[format_spec->i] == ' ') format_spec->space = 1;
    format_spec->i++;
  }
}

void width(const char *format, t_struct *format_spec) {
  if (format[format_spec->i] >= '0' && format[format_spec->i] <= '9') {
    format_spec->width = s21_atoi(&format[format_spec->i]);
    while (format[format_spec->i] >= '0' && format[format_spec->i] <= '9')
      format_spec->i++;
  }
}

void precision(const char *format, t_struct *format_spec) {
  int i = format_spec->i;
  if (format[i] == '.') {
    i++;
    format_spec->precisiontf = 1;
    if (format[i] >= '0' && format[i] <= '9') {
      format_spec->precision = s21_atoi(&format[i]);
      while (format[i] >= '0' && format[i] <= '9') i++;
    }
  }
  format_spec->i = i;
}

void set_modifiers(const char *format, t_struct *format_spec) {
  flags(format, format_spec);
  width(format, format_spec);
  precision(format, format_spec);
  if (format[format_spec->i] == 'l') {
    format_spec->size = 3;
    format_spec->i++;
    if (format[format_spec->i] == 'l') {
      format_spec->size = 4;
      format_spec->i++;
    }
  } else if (format[format_spec->i] == 'h') {
    format_spec->size = 2;
    format_spec->i++;
    if (format[format_spec->i] == 'h') {
      format_spec->size = 1;
      format_spec->i++;
    }
  }
}

void converting(char c, va_list ap, t_struct *format_spec, char *str) {
  if (c == 'c')
    ifchar(format_spec, ap, str);
  else if (c == 's')
    ifstring(format_spec, ap, str);
  else if (c == 'd' || c == 'i')
    ifint(format_spec, ap, 0, str);
  else if (c == 'u')
    ifudecint(format_spec, ap, str);
  else if (c == 'f')
    iffloat(format_spec, ap, 0, str);
  else if (c == '%')
    ifpercent(format_spec, str);
}

char *itoa_base(s21_uintmax_t value, s21_uintmax_t base) {
  int i = 1;
  unsigned long long n = value;
  while ((n /= base) >= 1) i++;
  char *s = (char *)malloc(sizeof(char) * (i + 1));
  s[i] = '\0';
  n = value;
  while (i-- > 0) {
    s[i] = (n % base < 10) ? n % base + '0' : n % base + 'a' - 10;
    n /= base;
  }
  return (s);
}

char *itoa_base_upper(s21_intmax_t value, s21_intmax_t base) {
  long long n;
  int sign;
  int i;
  n = (value < 0) ? -value : value;
  sign = (value < 0 && base == 10) ? -1 : 0;
  i = (sign == -1) ? 2 : 1;
  while ((n /= base) >= 1) i++;
  char *s = (char *)malloc(sizeof(char) * (i + 1));
  s[i] = '\0';
  n = (value < 0) ? -value : value;
  while (i-- + sign) {
    s[i] = (n % base < 10) ? n % base + '0' : n % base + 'A' - 10;
    n /= base;
  }
  (i == 0) ? s[i] = '-' : 0;
  return (s);
}

int signed_nbr_len(s21_intmax_t n, int base) {
  int nbrlen = 0;
  if (n < 0) {
    n = -n;
    nbrlen++;
  }
  while (n) {
    n = n / base;
    nbrlen++;
  }
  return (nbrlen);
}

int unsigned_nbr_len(s21_uintmax_t n, int base) {
  int i = 0;
  if (n == 0) {
    i = 1;
  } else {
    while (n) {
      n = n / base;
      i++;
    }
  }
  return (i);
}

void writeblanks(int n, char *str, t_struct *f) {
  while (n > 0) {
    f->nprinted += addtostr(str + f->nprinted, " ", 1);
    n--;
  }
}

void ifpercent(t_struct *f, char *str) {
  int num = 0;
  if (f->width != 0 && f->minus == 0) {
    num = f->width - 1;
    writeblanks(num, str, f);
    f->nprinted += addtostr(str + f->nprinted, "%", 1);
    //    f->nprinted = f->nprinted + num + 1;
  } else if (f->width && f->minus == 1) {
    num = f->width - 1;
    f->nprinted += addtostr(str + f->nprinted, "%", 1);
    writeblanks(num, str, f);
    //    f->nprinted = f->nprinted + num;
  } else {
    f->nprinted += addtostr(str + f->nprinted, "%", 1);
    //    f->nprinted++;
  }
}

void ifchar(t_struct *f, va_list ap, char *str) {
  int num = 0;
  char c = (char)va_arg(ap, int);
  //  if (f->size_l == 1) {
  //    wchar_t c = (wchar_t)va_arg(ap, int);
  //  }
  if (f->width && f->minus == 0) {
    num = f->width - 1;
    writeblanks(num, str, f);
    f->nprinted += addtostr(str + f->nprinted, &c, 1);
    //   f->nprinted = f->nprinted + num;
  } else if (f->width && f->minus == 1) {
    num = f->width - 1;
    f->nprinted += addtostr(str + f->nprinted, &c, 1);
    writeblanks(num, str, f);
    //    f->nprinted = f->nprinted + num;
  } else {
    f->nprinted += addtostr(str + f->nprinted, &c, 1);
    //   f->nprinted++;
  }
}

void right_aligned_int(t_struct *format_spec, char *s, int sign, char *str) {
  char c = ' ';
  char signc = '\0';
  if (sign == NEGATIVE) {
    signc = '-';
  } else if (format_spec->plus == 1) {
    signc = '+';
    format_spec->width -= 1;
  } else if (format_spec->space == 1) {
    signc = ' ';
    format_spec->width -= 1;
  }
  while (format_spec->width-- > 0)
    format_spec->nprinted += addtostr(str + format_spec->nprinted, &c, 1);
  if (sign != 0 || format_spec->plus == 1 || format_spec->space == 1)
    format_spec->nprinted += addtostr(str + format_spec->nprinted, &signc, 1);
  while (format_spec->precision-- > 0)
    format_spec->nprinted += addtostr(str + format_spec->nprinted, "0", 1);
  format_spec->nprinted +=
      addtostr(str + format_spec->nprinted, s, s21_strlen(s));
}

void left_aligned_int(t_struct *format_spec, char *s, int sign, char *str) {
  if (sign == NEGATIVE) {
    format_spec->nprinted += addtostr(str + format_spec->nprinted, "-", 1);
  } else if (format_spec->plus == 1) {
    format_spec->nprinted += addtostr(str + format_spec->nprinted, "+", 1);
    format_spec->width -= 1;
  } else if (format_spec->space == 1) {
    format_spec->nprinted += addtostr(str + format_spec->nprinted, " ", 1);
    format_spec->width -= 1;
  }
  while (format_spec->precision > 0) {
    format_spec->nprinted += addtostr(str + format_spec->nprinted, "0", 1);
    format_spec->precision--;
  }
  format_spec->nprinted +=
      addtostr(str + format_spec->nprinted, s, s21_strlen(s));
  while (format_spec->width > 0) {
    format_spec->nprinted += addtostr(str + format_spec->nprinted, " ", 1);
    format_spec->width--;
  }
}

void formatextractionint(s21_intmax_t n, t_struct *format_spec, int sign,
                         char *str) {
  char *s;
  s = itoa_base_upper(n, 10);
  int intlen = signed_nbr_len(n, 10);
  if (n == 0) intlen = 1;
  if (format_spec->precisiontf == 1 && format_spec->precision == 0 && n == 0) {
    intlen = 0;
    s[0] = '\0';
  }
  if (format_spec->precisiontf && format_spec->precision > intlen)
    format_spec->precision = format_spec->precision - intlen;
  else
    format_spec->precision = 0;
  if (sign != 0)
    format_spec->width =
        format_spec->width - (format_spec->precision + intlen + 1);
  else
    format_spec->width = format_spec->width - (format_spec->precision + intlen);
  if (format_spec->minus == 0) right_aligned_int(format_spec, s, sign, str);
  if (format_spec->minus == 1) left_aligned_int(format_spec, s, sign, str);
  free(s);
}

void ifint(t_struct *format_spec, va_list ap, int sign, char *str) {
  if (format_spec->size == 1) {
    char n = (char)va_arg(ap, int);
    if (n < 0) {
      sign = NEGATIVE;
      n = n * -1;
    }
    formatextractionint(n, format_spec, sign, str);
  } else if (format_spec->size == 2) {
    short int n = (short int)va_arg(ap, int);
    if (n < 0) {
      sign = NEGATIVE;
      n = n * -1;
    }
    formatextractionint(n, format_spec, sign, str);
  } else if (format_spec->size == 3) {
    long int n = va_arg(ap, long int);
    if (n < 0) {
      sign = NEGATIVE;
      n = n * -1;
    }
    formatextractionint(n, format_spec, sign, str);
  } else if (format_spec->size == 4) {
    long long int n = va_arg(ap, long long int);
    if (n < 0) {
      sign = NEGATIVE;
      n = n * -1;
    }
    formatextractionint(n, format_spec, sign, str);
  } else {
    int n = va_arg(ap, int);
    if (n < 0) {
      sign = NEGATIVE;
      n = n * -1;
    }
    formatextractionint(n, format_spec, sign, str);
  }
}

void rightalignedchar(t_struct *format_spec, char c, char *s, int i,
                      char *str) {
  if (format_spec->precisiontf && i > format_spec->precision)
    i = format_spec->precision;
  if (format_spec->width > i) {
    while ((format_spec->width - i) > 0) {
      format_spec->nprinted += addtostr(str + format_spec->nprinted, &c, 1);
      format_spec->width--;
    }
    addtostr(str + format_spec->nprinted, s, s21_strlen(s));
    format_spec->nprinted = format_spec->nprinted + i;
  } else {
    addtostr(str + format_spec->nprinted, s, s21_strlen(s));
    format_spec->nprinted = format_spec->nprinted + i;
  }
}

void leftalignedchar(t_struct *format_spec, char c, char *s, int i, char *str) {
  if (format_spec->precisiontf && i > format_spec->precision)
    i = format_spec->precision;
  if (format_spec->width > i) {
    addtostr(str + format_spec->nprinted, s, s21_strlen(s));
    format_spec->nprinted = format_spec->nprinted + i;
    while ((format_spec->width - i) > 0) {
      format_spec->nprinted += addtostr(str + format_spec->nprinted, &c, 1);
      format_spec->width--;
    }
  } else {
    addtostr(str + format_spec->nprinted, s, s21_strlen(s));
    format_spec->nprinted = format_spec->nprinted + i;
  }
}

void ifstring(t_struct *format_spec, va_list ap, char *str) {
  char *s = s21_NULL;
  int i;
  char c = ' ';
  s = (char *)va_arg(ap, char *);
  if (s == s21_NULL) s = "(null)";
  i = s21_strlen(s);
  if (format_spec->minus == 0)
    rightalignedchar(format_spec, c, s, i, str);
  else if (format_spec->minus == 1)
    leftalignedchar(format_spec, c, s, i, str);
}

void right_aligned_uint(t_struct *format_spec, char *s, char *str) {
  char c = ' ';
  while (format_spec->width-- > 0)
    format_spec->nprinted += addtostr(str + format_spec->nprinted, &c, 1);
  while (format_spec->precision-- > 0)
    format_spec->nprinted += addtostr(str + format_spec->nprinted, "0", 1);
  format_spec->nprinted += addtostr(str + format_spec->nprinted, s, s21_strlen(s));
}

void left_aligned_uint(t_struct *format_spec, char *s, char *str) {
  while (format_spec->precision > 0) {
    format_spec->nprinted += addtostr(str + format_spec->nprinted, "0", 1);
    format_spec->precision--;
  }
  format_spec->nprinted +=
      addtostr(str + format_spec->nprinted, s, s21_strlen(s));
  while (format_spec->width > 0) {
    format_spec->nprinted += addtostr(str + format_spec->nprinted, " ", 1);
    format_spec->width--;
  }
}

void formatextractionuint(s21_uintmax_t n, t_struct *format_spec, char *str) {
  char *s = itoa_base(n, 10);
  int intlen = 0;
  intlen = unsigned_nbr_len(n, 10);
  if (format_spec->precisiontf == 1 && format_spec->precision == 0 && n == 0) {
    intlen = 0;
    s[0] = '\0';
  }
  if (format_spec->precisiontf && format_spec->precision > intlen)
    format_spec->precision = format_spec->precision - intlen;
  else
    format_spec->precision = 0;
  format_spec->width = format_spec->width - (format_spec->precision + intlen);
  if (format_spec->minus == 0) right_aligned_uint(format_spec, s, str);
  if (format_spec->minus == 1) left_aligned_uint(format_spec, s, str);
  free(s);
}

void ifudecint(t_struct *format_spec, va_list ap, char *str) {
  if (format_spec->size == 1) {
    unsigned char n = (unsigned char)va_arg(ap, unsigned int);
    formatextractionuint(n, format_spec, str);
  } else if (format_spec->size == 2) {
    unsigned short int n = (unsigned short int)va_arg(ap, unsigned int);
    formatextractionuint(n, format_spec, str);
  } else if (format_spec->size == 3) {
    unsigned long int n = va_arg(ap, unsigned long int);
    formatextractionuint(n, format_spec, str);
  } else if (format_spec->size == 4) {
    unsigned long long int n = va_arg(ap, unsigned long long int);
    formatextractionuint(n, format_spec, str);
  } else {
    unsigned int n = va_arg(ap, unsigned int);
    formatextractionuint(n, format_spec, str);
  }
}

void formatextractionfloat(long double num, t_struct *format_spec, int sign,
                           char *str) {
  static char buffer[256] = {'\0'};
  long double int_part;
  long double float_part =
      modfl(num, &int_part) *
      powl((long double)10, (long double)format_spec->precision);
  float_part = roundl(float_part);
  if (modfl(num, &int_part) == 0.5 && format_spec->precision == 0) {
    float_part = 0.0;
  } else if (float_part == powl((long double)10, (long double)format_spec->precision)) {
    int_part++;
    float_part = 0.0;
  }
  char *s1 = itoa_base_upper(int_part, 10);
  int intlen = signed_nbr_len(int_part, 10);
  s21_strcpy(buffer, s1);
  if (format_spec->precision > 0)
    s21_strcat(buffer, ".");
  else if (format_spec->precision == 0 && int_part == 0)
    format_spec->width += 1;
  else
    format_spec->width += 2;
  char *s2 = s21_NULL;
  char *p = s21_NULL;
  if (float_part == 0.0) {
    s2 = (char *)calloc(format_spec->precision + 1, sizeof(char));
    for (int i = format_spec->precision; i > 0; i--) {
      s2[i] = '0';
    }
    s2[format_spec->precision] = '\0';
  } else {
    s2 = itoa_base_upper(float_part, 10);
  }
  if (format_spec->precision > (int)s21_strlen(s2)) {
    for (int i = format_spec->precision - s21_strlen(s2); i > 0; i--)
      s21_strcat(buffer, "0");
  }
  s21_strcat(buffer, s2);
  p = buffer;
  if (sign != 0)
    format_spec->width = format_spec->width - (format_spec->precision + intlen + 2);
  else if (int_part == 0.0 && float_part == 0.0)
    format_spec->width = format_spec->width - (format_spec->precision + intlen + 2);
  else
    format_spec->width = format_spec->width - (format_spec->precision + intlen + 1);
  format_spec->precision = 0;
  if (format_spec->minus == 0) right_aligned_int(format_spec, p, sign, str);
  if (format_spec->minus == 1) left_aligned_int(format_spec, p, sign, str);
  free(s1);
  free(s2);
}

void iffloat(t_struct *format_spec, va_list ap, int sign, char *str) {
  double num = va_arg(ap, double);
  if (num < 0.0 /*|| num == -0.0*/) {
    sign = NEGATIVE;
    num = num * -1.0;
  }
  if (format_spec->precisiontf == 0) format_spec->precision = 6;
  formatextractionfloat(num, format_spec, sign, str);
}

int s21_sprintf(char *str, const char *format, ...) {
  va_list ap;
  int chr_printed = 0;
  t_struct *format_spec;
  int formatlen = s21_strlen(format);
  if ((format_spec = (t_struct *)malloc(sizeof(t_struct)))) {
    set_to_zero(format_spec);
    format_spec->format = (char *)format;
    va_start(ap, format);
    if (format[0] || !(formatlen == 1 && format[0] == '%'))
      chr_printed = formatparse(format, format_spec, ap, 0, str);
    va_end(ap);
    free(format_spec);
  }
  return (chr_printed);
}
