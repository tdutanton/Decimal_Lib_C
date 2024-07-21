#include "../s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  arithmetic_result error_code = OK;
  unsigned sign = get_sign(value_1) ^ get_sign(value_2);
  int power = get_power(value_1) + get_power(value_2);
  double_decimal one = {{1, 0, 0, 0, 0, 0, 0, 0}};
  double_decimal val_1 = create_double_decimal(value_1);
  double_decimal val_2 = create_double_decimal(value_2);
  double_decimal res = {0}, remainder = {0};
  int rem = 0;

  for (int j = 0; j <= 191; j++) {
    double_decimal temp = val_1;

    if (!!(val_2.bits[j / BITS_IN_ONE_INT] & (1U << j % BITS_IN_ONE_INT))) {
      d_decimal_shift_left(&temp, j);
      d_decimal_add(temp, res, &res);
    }
  }
  while (!(res.bits[7] == 0 && res.bits[6] == 0 && res.bits[5] == 0 &&
           res.bits[4] == 0 && res.bits[3] == 0) ||
         power > 28) {
    rem = remainder.bits[0];
    res = d_decimal_div_by_ten(res, &remainder);
    power--;
  }

  if (remainder.bits[0] > 5)
    d_decimal_add(res, one, &res);
  else if (remainder.bits[0] == 5) {
    if (get_bit(res.bits[0], 0) == 1 || rem != 0) d_decimal_add(res, one, &res);
  }

  if (res.bits[3] != 0)
    error_code = sign == 1 ? TOO_SMALL : TOO_BIG;
  else if (power < 0)
    error_code = sign == 1 ? TOO_SMALL : TOO_BIG;
  else {
    *result = init_zero_decimal();
    for (int i = 0; i < 3; i++) result->bits[i] = res.bits[i];
    if (check_zero_mantissa(result) == 0) {
      set_power(result, power);
      set_sign(result, sign);
    }
  }
  return error_code;
}