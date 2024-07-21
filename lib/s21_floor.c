#include "../s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  error_code code = NO_ERROR;
  s21_decimal temp;
  s21_decimal neg_one = {{1, 0, 0, 0b10000000000000000000000000000000}};
  if (!result)
    code = ERROR;
  else if (s21_truncate(value, &temp))
    code = ERROR;
  else {
    *result = temp;
    if (get_sign(value) &&
        !(temp.bits[0] == 0xFFFFFFFF && temp.bits[1] == 0xFFFFFFFF &&
          temp.bits[2] == 0xFFFFFFFF)) {
      if (s21_is_not_equal(value, temp)) s21_add(temp, neg_one, result);
    }
  }
  return code;
}