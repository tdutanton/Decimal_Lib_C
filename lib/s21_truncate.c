#include "../s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int error = 1;  // 0 - OK; 1 - ошибка вычисления
  if (check_acceptable_decimal(&value) && result) {
    s21_decimal tmp = value;
    int sign = get_sign(value);
    int pow = get_power(tmp);
    while (pow > 0) {
      decimal_div_by_ten(&tmp);
      pow--;
    }
    *result = tmp;
    set_sign(result, sign);
    error = 0;
  }
  return error;
}