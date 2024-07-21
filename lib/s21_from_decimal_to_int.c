#include "../s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  s21_decimal tmp = src;
  int error = 1;
  if (check_acceptable_decimal(&src) && dst) {
    int sign = (get_sign(tmp) == POSITIVE) ? 1 : -1;
    int pow = get_power(tmp);
    while (pow > 0) {
      decimal_div_by_ten(&tmp);
      pow--;
    }
    if (check_zero_one_bits(tmp.bits[2]) && check_zero_one_bits(tmp.bits[1])) {
      if (tmp.bits[0] > INT_MAX && sign == 1)
        error = 1;
      else {
        *dst = (int)tmp.bits[0];
        *dst *= sign;
        error = 0;
      }
    }
  }
  return error;
}