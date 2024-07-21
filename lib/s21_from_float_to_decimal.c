#include "../s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  error_code code = NO_ERROR;
  float_bits temp;
  temp.float_num = src;
  unsigned int sign = (temp.bits & 0b10000000000000000000000000000000) >> 31;
  int exponent = ((temp.bits << 1) >> 24) - 128;
  if (exponent == 127)
    code = ERROR;
  else if (fabs(src) < MIN_CONV_FLOAT) {
    *dst = init_zero_decimal();
    code = ERROR;
  } else if (fabs(src) > MAX_CONV_FLOAT) {
    code = ERROR;
  } else {
    *dst = init_zero_decimal();
    char str_float[20] = {0};
    sprintf(str_float, "%.6e", fabs(src));
    int exp_ten = get_exp_from_float(str_float);
    int multiplier = 6;
    dst->bits[0] = get_mantissa_from_float(str_float, &multiplier);
    if (exp_ten < 0) set_power(dst, multiplier + (-exp_ten));
    if (exp_ten >= 0) {
      int pow = exp_ten - multiplier;
      if (pow < 0)
        set_power(dst, -pow);
      else {
        for (int i = pow; available_mul_by_ten(*dst) && i > 0; i--)
          mantissa_mul_by_ten(dst);
      }
    }
    set_sign(dst, sign);
  }
  return code;
}