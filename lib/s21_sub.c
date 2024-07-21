#include "../s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  arithmetic_result message = OK;
  int sign_2 = get_sign(value_2);
  *result = init_zero_decimal();
  if (sign_2 == POSITIVE) {
    message = s21_add(value_1, *set_sign(&value_2, NEGATIVE), result);
  } else if (sign_2 == NEGATIVE) {
    message = s21_add(value_1, *set_sign(&value_2, POSITIVE), result);
  }
  return message;
}