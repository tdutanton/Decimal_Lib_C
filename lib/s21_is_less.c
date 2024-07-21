#include "../s21_decimal.h"

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  compare_result result = CMP_FALSE;
  if (normalize_decimals(&value_1, &value_2) &&
      check_acceptable_decimal(&value_1) &&
      check_acceptable_decimal(&value_2)) {
    int value_1_sign = get_sign(value_1);
    int value_2_sign = get_sign(value_2);
    if (s21_is_equal(value_1, init_zero_decimal()) &&
        s21_is_equal(value_2, init_zero_decimal()))
      result = CMP_FALSE;
    else {
      if (value_1_sign == NEGATIVE && value_2_sign == POSITIVE) {
        result = CMP_TRUE;
      } else if (value_1_sign == POSITIVE && value_2_sign == NEGATIVE) {
        result = CMP_FALSE;
      } else if (value_1_sign == NEGATIVE && value_2_sign == NEGATIVE) {
        if (binary_compare_mantissa(&value_2, &value_1) == BITS_LESS)
          result = CMP_TRUE;
      } else {
        if (binary_compare_mantissa(&value_1, &value_2) == BITS_LESS) {
          result = CMP_TRUE;
        }
      }
    }
  }
  return result;
}