#include "../s21_decimal.h"

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  compare_result result = CMP_FALSE;
  if (normalize_decimals(&value_1, &value_2) &&
      check_acceptable_decimal(&value_1) &&
      check_acceptable_decimal(&value_2)) {
    if (s21_is_greater(value_1, value_2) == CMP_TRUE ||
        s21_is_equal(value_1, value_2) == CMP_TRUE) {
      result = CMP_TRUE;
    }
  }
  return result;
}