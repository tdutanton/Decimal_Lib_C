#include "../s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int error = 1;
  if (check_acceptable_decimal(&src) && dst) {
    int sign = get_sign(src);
    double power = pow(10, get_power(src));
    long double res = 0.0;
    for (register int i = 0; i < BITS_IN_MANTISSA; i++) {
      if (get_bit_in_decimal(&src, i)) {
        res += pow(2, i);
      }
    }
    res /= power;
    res *= (sign == NEGATIVE) ? -1 : 1;
    *dst = (float)res;
    error = 0;
  }
  return error;
}