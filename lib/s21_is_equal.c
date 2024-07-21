#include "../s21_decimal.h"

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  compare_result result = CMP_TRUE;
  if (normalize_decimals(&value_1, &value_2) &&
      check_acceptable_decimal(&value_1) &&
      check_acceptable_decimal(&value_2)) {
    if (check_zero_mantissa(&value_1) && check_zero_mantissa(&value_2))
      result = CMP_TRUE;
    else if (binary_compare_decimal(&value_1, &value_2) != BITS_EQUAL)
      result = CMP_FALSE;
  }
  return result;
}