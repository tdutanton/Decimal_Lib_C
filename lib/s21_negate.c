#include "../s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  int error = 1;  // 1 - error, 0 - OK
  if (check_acceptable_decimal(&value) && result) {
    error = 0;
    *result =
        (get_sign(value) == 0) ? *set_sign(&value, 1) : *set_sign(&value, 0);
  }
  return error;
}