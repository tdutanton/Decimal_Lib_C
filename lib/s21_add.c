#include "../s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  arithmetic_result message = OK;
  s21_decimal tmp_value_1 = value_1;
  s21_decimal tmp_value_2 = value_2;
  s21_decimal sum_rem = init_zero_decimal();
  s21_decimal sum_int = init_zero_decimal();
  s21_decimal one = one_decimal();
  s21_decimal value_1_int = init_zero_decimal();
  s21_decimal value_2_int = init_zero_decimal();
  int pow_1 = get_power(value_1);
  int pow_2 = get_power(value_2);
  int pow_max = (pow_1 - pow_2) > 0 ? pow_1 : pow_2;
  s21_truncate(tmp_value_1, &value_1_int);
  s21_truncate(tmp_value_2, &value_2_int);
  message = basic_add(value_1_int, value_2_int, &sum_int);
  if (!message) {
    get_sum_remainders(value_1, value_2, value_1_int, value_2_int, &sum_rem,
                       &message);
    int tmp_nums_rem = number_of_nums_in_decimal(sum_rem);
    if (tmp_nums_rem > pow_max) {
      message = basic_add(sum_int, one, &sum_int);
      multiple_mulling_decimal_by_ten(&one, get_power(sum_rem));
      basic_sub(sum_rem, one, &sum_rem);
    }
    int nums_int = number_of_nums_in_decimal(sum_int);
    int empty_spaces = NUMS_IN_DECIMAL - nums_int;
    while (available_div_by_ten(sum_rem)) decimal_div_by_ten(&sum_rem);
    int nums_rem_from_pow = get_power(sum_rem);
    int nums_rem = number_of_nums_in_decimal(sum_rem);
    int available_nums_rem =
        (empty_spaces > nums_rem_from_pow) ? nums_rem_from_pow : empty_spaces;
    if (empty_spaces > 0) {
      if (nums_rem_from_pow - available_nums_rem > 1) {
        while (nums_rem_from_pow - available_nums_rem != 1) {
          decimal_div_by_ten(&sum_rem);
          nums_rem_from_pow--;
        }
      }
      if (nums_rem_from_pow - available_nums_rem == 1)
        decimal_div_by_ten_rounded(&sum_rem);
      while (get_power(sum_int) != available_nums_rem &&
             available_mul_by_ten(sum_int))
        decimal_mul_by_ten(&sum_int);
      if (get_power(sum_int) != available_nums_rem)
        sum_rem = init_zero_decimal();
    }
    if (empty_spaces == 0 && nums_rem != 0)
      banking_for_add(&sum_int, &sum_rem, &message);
  }
  if (!message) {
    message = basic_add(sum_int, sum_rem, result);
    make_zero_to_empty_decimal(result);
  }
  return message;
}