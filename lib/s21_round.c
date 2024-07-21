#include "../s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  int error = 1;  // 0 - OK; 1 - ошибка вычисления
  if (check_acceptable_decimal(&value) && result) {
    s21_decimal tmp = value;
    s21_decimal o_five = o_five_decimal();
    int sign = get_sign(tmp);
    int pow = get_power(tmp);
    tmp = *set_sign(&tmp, 0);
    if (pow == 0)
      *result = value;
    else {
      s21_decimal tmp_integer = init_zero_decimal();
      s21_truncate(tmp, &tmp_integer);
      int even = check_even_decimal(tmp_integer);
      s21_decimal remainder = init_zero_decimal();
      multiple_mulling_decimal_by_ten(&tmp_integer, pow);
      basic_sub(tmp, tmp_integer, &remainder);
      multiple_mulling_decimal_by_ten(&o_five, pow);
      while (get_power(tmp_integer) != 0) decimal_div_by_ten(&tmp_integer);
      int less = s21_is_less(remainder, o_five);
      if (less)
        *result = tmp_integer;
      else if (s21_is_greater(remainder, o_five))
        basic_add(tmp_integer, one_decimal(), result);
      else if (s21_is_equal(remainder, o_five)) {
        if (even)
          *result = tmp_integer;
        else
          basic_add(tmp_integer, one_decimal(), result);
      }
      set_sign(result, sign);
    }
    error = 0;
  }
  return error;
}