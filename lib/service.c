#include "../s21_decimal.h"

int get_sign(s21_decimal decimal) {
  bits_bit3 bits3;
  bits3.a = decimal.bits[3];
  return bits3.bits_3_part.sign;
}

int get_power(s21_decimal decimal) {
  bits_bit3 bits3;
  bits3.a = decimal.bits[3];
  return bits3.bits_3_part.pow;
}

int get_bit(unsigned int bits, unsigned int index) {
  return !!(bits & (1U << index));
}

int get_bit_in_decimal(s21_decimal* value, unsigned int index) {
  return !!(value->bits[index / BITS_IN_ONE_INT] &
            (1U << index % BITS_IN_ONE_INT));
}

int set_bit(unsigned int bits, unsigned int index, int bit) {
  int result = 0;
  if (bit == 1) result = bits | (1U << index);
  if (bit == 0) result = bits & ~(1U << index);
  return result;
}

s21_decimal* set_bit_in_decimal(s21_decimal* value, unsigned int index,
                                int bit) {
  s21_decimal* result = NULL;
  if (value) {
    result = value;
    if (bit == 1)
      result->bits[index / BITS_IN_ONE_INT] =
          value->bits[index / BITS_IN_ONE_INT] |
          (1U << index % BITS_IN_ONE_INT);
    if (bit == 0)
      result->bits[index / BITS_IN_ONE_INT] =
          value->bits[index / BITS_IN_ONE_INT] &
          ~(1U << index % BITS_IN_ONE_INT);
  }
  return result;
}

s21_decimal* set_sign(s21_decimal* value, int sign) {
  s21_decimal* result = NULL;
  if (value) {
    result = value;
    set_bit_in_decimal(result, 127, sign);
  }
  return result;
}

s21_decimal decimals_and(s21_decimal value_1, s21_decimal value_2) {
  s21_decimal result = init_zero_decimal();
  result.bits[0] = value_1.bits[0] & value_2.bits[0];
  result.bits[1] = value_1.bits[1] & value_2.bits[1];
  result.bits[2] = value_1.bits[2] & value_2.bits[2];
  return result;
}

s21_decimal decimals_xor(s21_decimal value_1, s21_decimal value_2) {
  s21_decimal result = init_zero_decimal();
  result.bits[0] = value_1.bits[0] ^ value_2.bits[0];
  result.bits[1] = value_1.bits[1] ^ value_2.bits[1];
  result.bits[2] = value_1.bits[2] ^ value_2.bits[2];
  return result;
}

s21_decimal decimals_inverse(s21_decimal value) {
  s21_decimal result = init_zero_decimal();
  result.bits[0] = ~value.bits[0];
  result.bits[1] = ~value.bits[1];
  result.bits[2] = ~value.bits[2];
  return result;
}

s21_decimal* decimal_abs(s21_decimal* value) {
  s21_decimal* result = value;
  result->bits[3] = set_bit(result->bits[3], 31, 0);
  return result;
}

int binary_compare_mantissa(s21_decimal* value_1, s21_decimal* value_2) {
  binary_compare_result result = BITS_EQUAL;
  for (register int i = BITS_IN_MANTISSA - 1; i >= 0 && result == BITS_EQUAL;
       i--) {
    int bit_1 = get_bit_in_decimal(value_1, i);
    int bit_2 = get_bit_in_decimal(value_2, i);
    if (bit_1 == 0 && bit_2 == 1)
      result = BITS_LESS;
    else if (bit_1 == 1 && bit_2 == 0)
      result = BITS_GREAT;
  }
  return result;
}

int binary_compare_decimal(s21_decimal* value_1, s21_decimal* value_2) {
  binary_compare_result result = BITS_EQUAL;
  for (register int i = BITS_IN_DECIMAL - 1; i >= 0 && result == BITS_EQUAL;
       i--) {
    int bit_1 = get_bit_in_decimal(value_1, i);
    int bit_2 = get_bit_in_decimal(value_2, i);
    if (bit_1 == 0 && bit_2 == 1)
      result = BITS_LESS;
    else if (bit_1 == 1 && bit_2 == 0)
      result = BITS_GREAT;
  }
  return result;
}

int check_zero_mantissa(s21_decimal* value) {
  int result = 1;  // 1 - OK (в мантиссе все нули), 0 - failure
  for (register int i = BITS_IN_MANTISSA - 1; i >= 0 && result == 1; i--) {
    if (get_bit_in_decimal(value, i)) result = 0;
  }
  return result;
}

int check_zero_one_bits(unsigned int bits) {
  int result = 1;  // 1 - OK, 0 - failure
  for (register int i = BITS_IN_ONE_INT - 1; i >= 0 && result == 1; i--) {
    if (get_bit(bits, i)) result = 0;
  }
  return result;
}

s21_decimal init_zero_decimal(void) {
  s21_decimal result = {0};
  return result;
}

s21_decimal mantissa_shift_left_step(s21_decimal* value) {
  s21_decimal result = init_zero_decimal();
  for (int i = 0; i < 3; i++) {
    result.bits[i] = value->bits[i] << 1;
  }
  for (int i = 0; i < 2; i++) {
    if (get_bit(value->bits[i], BITS_IN_ONE_INT - 1)) {
      result.bits[i + 1] = set_bit(result.bits[i + 1], 0, 1);
    }
  }
  result.bits[3] = value->bits[3];
  return result;
}

s21_decimal mantissa_shift_right_step(s21_decimal* value) {
  s21_decimal result = init_zero_decimal();
  for (int i = 0; i < 3; i++) {
    result.bits[i] = value->bits[i] >> 1;
  }
  for (int i = 0; i < 2; i++) {
    if (get_bit(value->bits[i + 1], 0)) {
      result.bits[i] = set_bit(result.bits[i], BITS_IN_ONE_INT - 1, 1);
    }
  }
  result.bits[3] = value->bits[3];
  return result;
}

s21_decimal mantissa_shifts_left(s21_decimal* value, unsigned int steps) {
  s21_decimal result = *value;
  while (steps) {
    result = mantissa_shift_left_step(&result);
    steps--;
  }
  result.bits[3] = value->bits[3];
  return result;
}

void set_power(s21_decimal* number, unsigned char power) {
  int sign = get_sign(*number);
  unsigned int mask = power;
  number->bits[3] = mask << 16;
  set_sign(number, sign);
}

int check_acceptable_pow(s21_decimal* value) {
  int result = (get_power(*value) <= 28) ? 1 : 0;  // 1 - OK, 0 - bad pow (> 28)
  return result;
}

int check_empty_parts_bits_3(s21_decimal* value) {
  bits_bit3 bits3;
  bits3.a = value->bits[3];
  int result_1 =
      (bits3.bits_3_part.empty_1 == 0) ? 1 : 0;  // 1 - OK, 0 - bad (not empty)
  int result_2 =
      (bits3.bits_3_part.empty_2 == 0) ? 1 : 0;  // 1 - OK, 0 - bad (not empty)
  int result = (result_1 + result_2 == 2) ? 1 : 0;
  return result;
}

int mantissa_bit_length(s21_decimal number) {
  int length = 0;
  int empty = 0;
  while (empty != 1) {
    if (check_zero_mantissa(&number))
      empty = 1;
    else {
      number = mantissa_shift_right_step(&number);
      length++;
    }
  }
  return length;
}

int available_normalize_by_mul(s21_decimal value, int add_pow,
                               int* available_pow) {
  s21_decimal tmp = value;
  int result = 0;  // 0 - нельзя доумножить на разницу степеней, 1 - ОК
  int count = 0;
  for (register int i = 0; i < add_pow; i++) {
    if (available_mul_by_ten(tmp)) {
      decimal_mul_by_ten(&tmp);
      count++;
    }
  }
  result = (count == add_pow) ? 1 : 0;
  *available_pow = count;
  return result;
}

void decimal_div_by_ten_rounded(s21_decimal* value) {
  s21_decimal integ = *value;
  s21_decimal rem = init_zero_decimal();
  s21_decimal five = o_five_decimal();
  s21_decimal one = one_decimal();
  decimal_div_by_ten(&integ);
  int even = check_even_decimal(integ);
  decimal_mul_by_ten(&integ);
  basic_sub(*value, integ, &rem);
  decimal_div_by_ten(&integ);
  set_power(&one, get_power(*value) - 1);
  set_power(&five, get_power(rem));
  if (binary_compare_mantissa(&rem, &five) == BITS_GREAT)
    basic_add(integ, one, &integ);
  else if (binary_compare_mantissa(&rem, &five) == BITS_EQUAL && !even)
    basic_add(integ, one, &integ);
  *value = integ;
  set_sign(value, get_sign(*value));
}

// Базовая нормализация
int normalize_decimals(s21_decimal* value_1, s21_decimal* value_2) {
  normalize_result result = FAIL;  // 0 - FAIL, 1 - OK (SCALED), 2 - не
                                   // вмещается в decimal (BIGGER_THAN_MANTISSA)
  if (check_acceptable_decimal(value_1) && check_acceptable_decimal(value_2)) {
    s21_decimal tmp_1 = *value_1;
    s21_decimal tmp_2 = *value_2;
    int good_pow = 0;
    int mulling = 0;
    int exp_sub = get_power(*value_1) - get_power(*value_2);
    s21_decimal* to_mul = value_2;
    s21_decimal* to_div = value_1;
    if (exp_sub < 0) {
      to_mul = value_1;
      to_div = value_2;
      exp_sub = exp_sub * -1;
    }
    if (available_normalize_by_mul(*to_mul, exp_sub, &good_pow)) {
      while (exp_sub > 0) {
        decimal_mul_by_ten(to_mul);
        exp_sub--;
      }
      result = SCALED;
      mulling = 1;
    }
    if (!mulling) {
      while (get_power(*to_div) != get_power(*to_mul)) {
        decimal_div_by_ten(to_div);
      }
      result = SCALED;
    }
    set_sign(value_1, get_sign(tmp_1));
    set_sign(value_2, get_sign(tmp_2));
  }
  return result;
}

int basic_add(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  arithmetic_result message = OK;
  int sign_sum = get_sign(value_1);
  s21_decimal over_bit = decimals_and(value_1, value_2);
  *result = decimals_xor(value_1, value_2);
  if (get_sign(value_1) != get_sign(value_2)) {
    s21_decimal negative_decimal =
        (binary_is_less(value_1, value_2)) ? value_1 : value_2;
    s21_decimal positive_decimal =
        (binary_is_equal(negative_decimal, value_1)) ? value_2 : value_1;
    over_bit =
        (!binary_is_less(positive_decimal, *decimal_abs(&negative_decimal)))
            ? decimals_and(decimals_inverse(positive_decimal), negative_decimal)
            : decimals_and(decimals_inverse(negative_decimal),
                           positive_decimal);
    *result = decimals_xor(positive_decimal, negative_decimal);
    sign_sum = (binary_compare_mantissa(&negative_decimal, &positive_decimal) ==
                BITS_GREAT)
                   ? NEGATIVE
                   : POSITIVE;
  }
  while (binary_is_not_equal(over_bit, init_zero_decimal()) && message == OK) {
    if (sign_sum == POSITIVE && get_bit_in_decimal(&over_bit, 95) == 1)
      message = TOO_BIG;
    else if (sign_sum == NEGATIVE && get_bit_in_decimal(&over_bit, 95) == 1)
      message = TOO_SMALL;
    s21_decimal over_bit_shifted = mantissa_shift_left_step(&over_bit);
    if (get_sign(value_1) == get_sign(value_2)) {
      over_bit = decimals_and(*result, over_bit_shifted);
      *result = decimals_xor(*result, over_bit_shifted);
    } else if (get_sign(value_1) != get_sign(value_2)) {
      *result = decimals_xor(*result, over_bit_shifted);
      over_bit = decimals_and(*result, over_bit_shifted);
    }
  }
  result = set_sign(result, sign_sum);
  set_power(result, get_power(value_1));
  return message;
}

int binary_is_less(s21_decimal value_1, s21_decimal value_2) {
  compare_result result = CMP_FALSE;
  int value_1_sign = get_sign(value_1);
  int value_2_sign = get_sign(value_2);
  s21_decimal zero = init_zero_decimal();
  if (binary_compare_mantissa(&value_1, &zero) == BITS_EQUAL &&
      binary_compare_mantissa(&value_2, &zero) == BITS_EQUAL)
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
  return result;
}

int binary_is_equal(s21_decimal value_1, s21_decimal value_2) {
  compare_result result = CMP_TRUE;
  if (check_zero_mantissa(&value_1) && check_zero_mantissa(&value_2))
    result = CMP_TRUE;
  else if (binary_compare_decimal(&value_1, &value_2) != BITS_EQUAL)
    result = CMP_FALSE;
  return result;
}

int binary_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  compare_result result = CMP_FALSE;
  result = CMP_TRUE;
  if (check_zero_mantissa(&value_1) && check_zero_mantissa(&value_2))
    result = CMP_FALSE;
  else if (binary_compare_decimal(&value_1, &value_2) == BITS_EQUAL)
    result = CMP_FALSE;
  return result;
}

int binary_is_greater(s21_decimal value_1, s21_decimal value_2) {
  compare_result result = CMP_FALSE;
  decimal_sign value_1_sign = get_sign(value_1);
  decimal_sign value_2_sign = get_sign(value_2);
  if (binary_is_equal(value_1, init_zero_decimal()) &&
      binary_is_equal(value_2, init_zero_decimal()))
    result = CMP_FALSE;
  else {
    if (value_1_sign == POSITIVE && value_2_sign == NEGATIVE) {
      result = CMP_TRUE;
    } else if (value_1_sign == NEGATIVE && value_2_sign == POSITIVE) {
      result = CMP_FALSE;
    } else if (value_1_sign == NEGATIVE && value_2_sign == NEGATIVE) {
      result = (binary_compare_mantissa(&value_2, &value_1) == BITS_GREAT)
                   ? CMP_TRUE
                   : CMP_FALSE;
    } else {
      result = (binary_compare_mantissa(&value_1, &value_2) == BITS_GREAT)
                   ? CMP_TRUE
                   : CMP_FALSE;
    }
  }
  return result;
}

int basic_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  arithmetic_result message = OK;
  int sign_2 = get_sign(value_2);
  *result = init_zero_decimal();
  if (sign_2 == POSITIVE) {
    message = basic_add(value_1, *set_sign(&value_2, NEGATIVE), result);
  } else if (sign_2 == NEGATIVE) {
    message = basic_add(value_1, *set_sign(&value_2, POSITIVE), result);
  }
  return message;
}

int available_mul_by_ten(s21_decimal value) {
  s21_decimal mul = value;
  mantissa_mul_by_ten(&mul);
  mantissa_div_by_ten(&mul);
  return (binary_is_equal(mul, value)) ? 1 : 0;  // 1 - OK; 0 - fail
}

int available_div_by_ten(s21_decimal value) {
  int result = 0;
  s21_decimal zero = init_zero_decimal();
  s21_decimal div = value;
  decimal_div_by_ten(&div);
  decimal_mul_by_ten(&div);
  if (s21_is_equal(div, value)) {
    result = 1;
  }
  if (binary_is_equal(*decimal_abs(&value), zero) ||
      binary_is_equal(*decimal_abs(&div), zero))
    result = 0;
  return result;
  // 1 - OK; 0 - fail
}

int check_acceptable_decimal(s21_decimal* value) {
  int result = 0;  // 0 - fail, 1 - OK
  if (value && check_acceptable_pow(value) && check_empty_parts_bits_3(value))
    result = 1;
  return result;
}

s21_decimal max_decimal(void) {
  s21_decimal value = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  return value;
}

s21_decimal one_decimal(void) {
  s21_decimal value = {{1, 0, 0, 0}};
  return value;
}

s21_decimal o_five_decimal(void) {
  s21_decimal value = {{5, 0, 0, 0b00000000000000010000000000000000}};
  return value;
}

void mantissa_mul_by_ten(s21_decimal* number) {
  unsigned int exponent = number->bits[3];
  s21_decimal temp = *number;
  temp.bits[3] = 0;
  s21_decimal a = mantissa_shift_left_step(&temp);
  s21_decimal b = mantissa_shifts_left(&temp, 3);
  basic_add(a, b, number);
  number->bits[3] = exponent;
}

void decimal_mul_by_ten(s21_decimal* number) {
  int pow = get_power(*number);
  int sign = get_sign(*number);
  s21_decimal temp = *number;
  temp.bits[3] = 0;
  s21_decimal a = mantissa_shift_left_step(&temp);
  s21_decimal b = mantissa_shifts_left(&temp, 3);
  basic_add(a, b, number);
  set_power(number, pow + 1);
  set_sign(number, sign);
}

void mantissa_div_by_ten(s21_decimal* number) {
  s21_decimal result = init_zero_decimal();
  unsigned int exponent = number->bits[3];
  s21_decimal remainder = *number;  // делимое, остаток от деления
  s21_decimal ten = {{10, 0, 0, 0}};
  s21_decimal divider = ten;  // делитель
  remainder.bits[3] = 0;
  while (s21_is_greater_or_equal(remainder, divider)) {
    s21_decimal temp = {{1, 0, 0, 0}};
    unsigned int shift =
        mantissa_bit_length(remainder) - mantissa_bit_length(divider);
    divider = mantissa_shifts_left(&divider, shift);
    if (s21_is_less(remainder, divider)) {
      divider = mantissa_shift_right_step(&divider);
      shift--;
    }
    basic_sub(remainder, divider, &remainder);
    temp = mantissa_shifts_left(&temp, shift);
    basic_add(result, temp, &result);
    divider = ten;
  }
  *number = result;
  number->bits[3] = exponent;
}

void decimal_div_by_ten(s21_decimal* number) {
  int pow = get_power(*number);
  int sign = get_sign(*number);
  s21_decimal result = init_zero_decimal();
  s21_decimal remainder = *number;  // делимое, остаток от деления
  s21_decimal ten = {{10, 0, 0, 0}};
  s21_decimal divider = ten;  // делитель
  remainder.bits[3] = 0;
  while (binary_is_greater(remainder, divider) ||
         binary_is_equal(remainder, divider)) {
    s21_decimal temp = {{1, 0, 0, 0}};
    unsigned int shift =
        mantissa_bit_length(remainder) - mantissa_bit_length(divider);
    divider = mantissa_shifts_left(&divider, shift);
    if (binary_compare_mantissa(&remainder, &divider) == BITS_LESS) {
      divider = mantissa_shift_right_step(&divider);
      shift--;
    }
    basic_sub(remainder, divider, &remainder);
    temp = mantissa_shifts_left(&temp, shift);
    basic_add(result, temp, &result);
    divider = ten;
  }
  *number = result;
  set_power(number, pow - 1);
  set_sign(number, sign);
}

int check_even_decimal(s21_decimal value) {
  int result =
      get_bit_in_decimal(&value, 0) ? 0 : 1;  // 0 - нечетное, 1 - четное
  return result;
}

int get_exp_from_float(char str_float[]) {
  int exp = 0;
  char* p = strrchr(str_float, 'e') + 1;
  sscanf(p, "%d", &exp);
  return exp;
}

unsigned int get_mantissa_from_float(char str_float[], int* pow) {
  unsigned int result = 0;
  char* p = strrchr(str_float, '.');
  char before_dot[10] = {0};
  strncpy(before_dot, str_float, p - str_float);
  char after_dot[7] = {0};
  strncpy(after_dot, p + 1, 6);
  for (int i = 5; i >= 0 && after_dot[i] == '0'; i--) {
    *pow -= 1;
  }
  if (*pow != 0) strncat(before_dot, after_dot, *pow);
  sscanf(before_dot, "%u", &result);
  return result;
}

int number_of_nums_in_decimal(s21_decimal value) {
  int count = 0;
  s21_decimal tmp = value;
  while (binary_is_not_equal(tmp, init_zero_decimal())) {
    mantissa_div_by_ten(&tmp);
    count++;
  }
  return count;
}

s21_decimal first_num_in_decimal(s21_decimal value) {
  s21_decimal result = init_zero_decimal();
  s21_decimal tmp = value;
  decimal_div_by_ten(&tmp);
  decimal_mul_by_ten(&tmp);
  basic_sub(value, tmp, &result);
  return result;
}

void multiple_mulling_decimal_by_ten(s21_decimal* value, int pow) {
  while (get_power(*value) != pow) {
    decimal_mul_by_ten(value);
  }
}

void scaling_decimal_for_add(s21_decimal* value, int pow) {
  for (register int i = 0; i < pow; i++) {
    decimal_mul_by_ten(value);
  }
}

void banking_for_add(s21_decimal* sum_int, s21_decimal* sum_rem,
                     arithmetic_result* message) {
  s21_decimal first_num = first_num_in_decimal(*sum_int);
  basic_sub(*sum_int, first_num, sum_int);
  while (get_power(first_num) != get_power(*sum_rem)) {
    decimal_mul_by_ten(&first_num);
  }
  *message = basic_add(first_num, *sum_rem, &first_num);
  s21_round(first_num, &first_num);
  *message = basic_add(*sum_int, first_num, sum_int);
  *sum_rem = init_zero_decimal();
}

void get_sum_remainders(s21_decimal value_1, s21_decimal value_2,
                        s21_decimal value_1_int, s21_decimal value_2_int,
                        s21_decimal* sum_rem, arithmetic_result* message) {
  int pow_1 = get_power(value_1);
  int pow_2 = get_power(value_2);
  int pow_max = (pow_1 - pow_2) > 0 ? pow_1 : pow_2;
  s21_decimal value_1_rem = init_zero_decimal();
  s21_decimal value_2_rem = init_zero_decimal();
  scaling_decimal_for_add(&value_1_int, pow_1);
  scaling_decimal_for_add(&value_2_int, pow_2);
  basic_sub(value_1, value_1_int, &value_1_rem);
  basic_sub(value_2, value_2_int, &value_2_rem);
  scaling_decimal_for_add(&value_1_rem, pow_max - pow_1);
  scaling_decimal_for_add(&value_2_rem, pow_max - pow_2);
  *message = basic_add(value_1_rem, value_2_rem, sum_rem);
}

void make_zero_to_empty_decimal(s21_decimal* value) {
  if (s21_is_equal(*value, init_zero_decimal())) {
    set_sign(value, 0);
    set_power(value, 0);
  }
}

void d_decimal_add(double_decimal value_1, double_decimal value_2,
                   double_decimal* result) {
  double_decimal overflow = {{1, 0}};
  double_decimal temp = value_2;
  *result = value_1;

  while (!(d_decimal_is_zero(overflow))) {
    for (int i = 0; i < 8; i++)
      overflow.bits[i] = result->bits[i] & temp.bits[i];

    d_decimal_shift_left(&overflow, 1);

    for (int i = 0; i < 8; i++)
      result->bits[i] = result->bits[i] ^ temp.bits[i];
    for (int i = 0; i < 8; i++) temp.bits[i] = overflow.bits[i];
  }
}

void d_decimal_shift_left(double_decimal* number, int count) {
  for (int i = 0; i < count; i++) {
    double_decimal overflow = {0};

    for (int j = 0; j < 8; j++) {
      if (j == 7) {
        number->bits[j] = (number->bits[j] << 1) + overflow.bits[j];
      } else {
        overflow.bits[j + 1] = number->bits[j] >> 31;
        number->bits[j] = (number->bits[j] << 1) + overflow.bits[j];
      }
    }
  }
}

void d_decimal_shift_right(double_decimal* number, int count) {
  for (int i = 0; i < count; i++) {
    double_decimal overflow = {0};

    for (int j = 0; j < 8; j++) {
      if (j == 7) {
        number->bits[j] = (number->bits[j] >> 1) + overflow.bits[j];
      } else {
        overflow.bits[j] = (number->bits[j + 1] << 31);
        number->bits[j] = (number->bits[j] >> 1) + overflow.bits[j];
      }
    }
  }
}

double_decimal d_decimal_div_by_ten(double_decimal value,
                                    double_decimal* remainder) {
  double_decimal temp = {0};
  double_decimal rem = {0};
  double_decimal one = {{1, 0, 0, 0, 0, 0, 0, 0}};

  double_decimal temp1 = value;
  d_decimal_shift_right(&temp1, 1);
  double_decimal temp2 = value;
  d_decimal_shift_right(&temp2, 2);
  d_decimal_add(temp1, temp2, &temp);

  for (int i = 4; i < 256; i *= 2) {
    temp1 = temp;
    d_decimal_shift_right(&temp1, i);
    d_decimal_add(temp, temp1, &temp);
  }

  d_decimal_shift_right(&temp, 3);

  temp1 = temp;
  d_decimal_shift_left(&temp1, 3);
  temp2 = temp;
  d_decimal_shift_left(&temp2, 1);
  d_decimal_add(temp1, temp2, &temp1);

  d_decimal_sub(value, temp1, &rem);

  if (rem.bits[0] > 9) {
    double_decimal ten = {{10, 0, 0, 0, 0, 0, 0, 0}};
    d_decimal_sub(rem, ten, remainder);
    d_decimal_add(temp, one, &temp);
  } else {
    *remainder = rem;
  }
  return temp;
}

void d_decimal_sub(double_decimal value_1, double_decimal value_2,
                   double_decimal* result) {
  double_decimal temp = value_2;
  double_decimal one = {{1, 0, 0, 0, 0, 0, 0, 0}};
  for (int i = 0; i < 8; i++) temp.bits[i] = ~(temp.bits[i]);
  d_decimal_add(temp, one, &temp);
  d_decimal_add(value_1, temp, result);
}

double_decimal create_double_decimal(s21_decimal number) {
  double_decimal result = {0};
  for (int i = 0; i < 3; i++) result.bits[i] = number.bits[i];
  return result;
}

int d_decimal_is_zero(double_decimal number) {
  int res = 1;
  for (int i = 0; i < 8 && res == 1; i++) {
    if (number.bits[i] != 0) res = 0;
  }
  return res;
}

double_decimal d_decimal_division(double_decimal value_1,
                                  double_decimal value_2,
                                  double_decimal* remainder, int* power) {
  double_decimal one = {{1, 0, 0, 0, 0, 0, 0, 0}};
  double_decimal res = {0};
  double_decimal divider = value_2;
  *remainder = value_1;
  while (!d_decimal_is_zero(*remainder) && *power < 29) {
    res = d_decimal_mul_by_ten(res);
    *remainder = d_decimal_mul_by_ten(*remainder);
    *power += 1;
    while (d_decimal_compare(*remainder, divider) == 2 ||
           d_decimal_compare(*remainder, divider) == 0) {
      unsigned int shift =
          d_decimal_bit_length(*remainder) - d_decimal_bit_length(divider);
      d_decimal_shift_left(&divider, shift);

      if (d_decimal_compare(*remainder, divider) == 1) {
        d_decimal_shift_right(&divider, 1);
        shift--;
      }
      d_decimal_sub(*remainder, divider, remainder);
      d_decimal_shift_left(&one, shift);
      d_decimal_add(res, one, &res);

      divider = value_2;
      for (int i = 0; i < 8; i++) one.bits[i] = 0;
      one.bits[0] = 1;
    }
  }
  return res;
}

int d_decimal_bit_length(double_decimal number) {
  int length = 0;
  int empty = 0;
  while (empty != 1) {
    if (d_decimal_is_zero(number))
      empty = 1;
    else {
      d_decimal_shift_right(&number, 1);
      length++;
    }
  }
  return length;
}

int d_decimal_compare(double_decimal value_1, double_decimal value_2) {
  int res = 0;
  for (int i = 256 - 1; i >= 0 && res == 0; i--) {
    int bit_1 =
        !!(value_1.bits[i / BITS_IN_ONE_INT] & (1U << i % BITS_IN_ONE_INT));
    int bit_2 =
        !!(value_2.bits[i / BITS_IN_ONE_INT] & (1U << i % BITS_IN_ONE_INT));
    if (bit_1 == 0 && bit_2 == 1)
      res = 1;
    else if (bit_1 == 1 && bit_2 == 0)
      res = 2;
  }
  return res;  // 0 - оба double_decimal равны, 1 - первый меньше, 2 - второй
               // меньше
}

double_decimal d_decimal_mul_by_ten(double_decimal number) {
  double_decimal res = {0};
  double_decimal a = number;
  d_decimal_shift_left(&a, 1);
  double_decimal b = number;
  d_decimal_shift_left(&b, 3);
  d_decimal_add(a, b, &res);
  return res;
}

int count_digits(double_decimal number) {
  int count = 0;
  double_decimal rem = {0};
  while (!d_decimal_is_zero(number)) {
    number = d_decimal_div_by_ten(number, &rem);
    count++;
  }
  return count;
}

void convert_to_decimal(s21_decimal* result, double_decimal res, int* power,
                        int sign) {
  *result = init_zero_decimal();
  for (int i = 0; i < 3; i++) result->bits[i] = res.bits[i];
  while (available_div_by_ten(*result) && *power > 0) {
    mantissa_div_by_ten(result);
    *power -= 1;
  }
  if (check_zero_mantissa(result) == 0) {
    set_power(result, *power);
    set_sign(result, sign);
  }
}

// void print_hex_decimal(s21_decimal number) {
//   for (int j = 0; j < 4; j++) {
//     if (j == 3)
//       printf("0x%08X", number.bits[j]);
//     else
//       printf("0x%08X, ", number.bits[j]);
//   }
//   printf("\n");
// }

// void print_double_decimal(double_decimal number) {
//   for (int i = 7; i >= 0; i--) {
//     print_bits(number.bits[i]);
//     // printf(" ");
//   }
//   printf("\n");
// }

// void print_float_binary(float src) {
//   union {
//     float f;
//     unsigned int j;
//   } u;
//   u.f = src;
//   for (register int i = sizeof(src) * 8 - 1; i >= 0; i--) {
//     printf("%d", (u.j >> i) & 1);
//     if (i == 31 || i == 23) printf(" ");
//   }
//   printf("\n");
// }

// void print_decimal(s21_decimal number) {
//   for (register int i = sizeof(number.bits[3]) * 8 - 1; i >= 0; i--) {
//     if ((i >= 24 && i <= 30) || (i >= 0 && i <= 15)) {
//       printf("\033[0;34m%d\033[0m", (number.bits[3] >> i) & 1);
//     } else {
//       printf("%d", (number.bits[3] >> i) & 1);
//     }
//     if (i == 31 || i == 24 || i == 16 || i == 0) printf(" ");
//   }

//   for (int i = 2; i >= 0; i--) {
//     print_bits(number.bits[i]);
//     if (i != 0) printf(" ");
//   }
//   printf("\n");
// }

// void print_bits(unsigned int num) {
//   for (register int i = sizeof(num) * 8 - 1; i >= 0; i--) {
//     printf("%d", (num >> i) & 1);
//   }
// }