#include "../s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int error = 1;
  if (dst) {
    *dst = init_zero_decimal();
    int sign = src < 0 ? 1 : 0;
    if (sign) {
      dst->bits[0] = -src;
      set_sign(dst, sign);
    } else
      dst->bits[0] = src;
    error = 0;
  }
  return error;
}