#include "../s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  arithmetic_result error_code = OK;
  if (check_zero_mantissa(&value_2))
    error_code = DIV_BY_ZERO;
  else {
    int power = get_power(value_1) - get_power(value_2);
    unsigned sign = get_sign(value_1) ^ get_sign(value_2);
    double_decimal val_1 = create_double_decimal(value_1);
    double_decimal val_2 = create_double_decimal(value_2);
    double_decimal one = {{1, 0, 0, 0, 0, 0, 0, 0}};
    double_decimal res = {0}, temp = {0}, remainder = {0};
    int rem = 0;
    res = d_decimal_division(val_1, val_2, &remainder, &power);
    if (power < 0 && d_decimal_is_zero(remainder)) {
      while (power < 0) {
        res = d_decimal_mul_by_ten(res);
        power++;
      }
    }
    while (count_digits(res) > 29 || res.bits[3] != 0) {
      rem = remainder.bits[0];
      res = d_decimal_div_by_ten(res, &remainder);
      power--;
    }
    if (power == 29) {
      res = d_decimal_div_by_ten(res, &temp);
      if (temp.bits[0] > 5)
        d_decimal_add(res, one, &res);
      else if (temp.bits[0] == 5) {
        if (get_bit(res.bits[0], 0) == 1 || remainder.bits[0] != 0)
          d_decimal_add(res, one, &res);
      }
      power--;
    } else if (remainder.bits[0] > 5)
      d_decimal_add(res, one, &res);
    else if (remainder.bits[0] == 5) {
      if (get_bit(res.bits[0], 0) == 1 || rem != 0)
        d_decimal_add(res, one, &res);
    }

    if (res.bits[3] != 0)
      error_code = sign == 1 ? TOO_SMALL : TOO_BIG;
    else if (power < 0)
      error_code = sign == 1 ? TOO_SMALL : TOO_BIG;
    else
      convert_to_decimal(result, res, &power, sign);
  }
  return error_code;
}