#include "s21_test.h"

START_TEST(s21_sub_1) {
  s21_decimal first = {
      {0b00000000000000000000000000000001, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b10000000000000000000000000000000}};
  s21_decimal second = {
      {0b00000000000000000000000000000001, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b10000000000000000000000000000000}};
  s21_decimal decimal_check = {{0, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal decimal_result = init_zero_decimal();
  s21_sub(first, second, &decimal_result);
  ck_assert_int_eq((s21_sub(first, second, &decimal_result)), 0);
  compare(decimal_check, decimal_result);
}
END_TEST

START_TEST(s21_sub_2) {
  s21_decimal first = {{10, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal second = {{5, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal decimal_check = {{5, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal decimal_result = init_zero_decimal();
  s21_sub(first, second, &decimal_result);
  ck_assert_int_eq((s21_sub(first, second, &decimal_result)), 0);
  compare(decimal_check, decimal_result);
}
END_TEST

START_TEST(s21_sub_3) {
  s21_decimal first = {{10, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal second = {{5, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal decimal_check = {{15, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal decimal_result = init_zero_decimal();
  s21_sub(first, second, &decimal_result);
  ck_assert_int_eq((s21_sub(first, second, &decimal_result)), 0);
  compare(decimal_check, decimal_result);
}
END_TEST

START_TEST(s21_sub_4) {
  s21_decimal first = {{10, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal second = {{5, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal decimal_check = {{5, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal decimal_result = init_zero_decimal();
  s21_sub(first, second, &decimal_result);
  ck_assert_int_eq((s21_sub(first, second, &decimal_result)), 0);
  compare(decimal_check, decimal_result);
}
END_TEST

START_TEST(s21_sub_5) {
  s21_decimal first = {{10, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal second = {{5, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal decimal_check = {{15, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal decimal_result = init_zero_decimal();
  s21_sub(first, second, &decimal_result);
  ck_assert_int_eq((s21_sub(first, second, &decimal_result)), 0);
  compare(decimal_check, decimal_result);
}
END_TEST

START_TEST(s21_sub_6) {
  s21_decimal first = {{10, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal second = {{15, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal decimal_check = {{25, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal decimal_result = init_zero_decimal();
  s21_sub(first, second, &decimal_result);
  ck_assert_int_eq((s21_sub(first, second, &decimal_result)), 0);
  compare(decimal_check, decimal_result);
}
END_TEST

START_TEST(s21_sub_7) {
  s21_decimal first = {{10, 10, 0, 0b00000000000000000000000000000000}};
  s21_decimal second = {{15, 5, 0, 0b10000000000000000000000000000000}};
  s21_decimal decimal_check = {{25, 15, 0, 0b00000000000000000000000000000000}};
  s21_decimal decimal_result = init_zero_decimal();
  s21_sub(first, second, &decimal_result);
  ck_assert_int_eq((s21_sub(first, second, &decimal_result)), 0);
  compare(decimal_check, decimal_result);
}
END_TEST

START_TEST(s21_sub_8) {
  s21_decimal first = {{1000, 0, 0, 0b00000000000000100000000000000000}};
  s21_decimal second = {{50, 0, 0, 0b00000000000000010000000000000000}};
  s21_decimal decimal_check = {{500, 0, 0, 0b00000000000000100000000000000000}};
  s21_decimal decimal_result = init_zero_decimal();
  s21_sub(first, second, &decimal_result);
  ck_assert_int_eq((s21_sub(first, second, &decimal_result)), 0);
  compare(decimal_check, decimal_result);
}
END_TEST

START_TEST(s21_sub_9) {
  s21_decimal value_1 = {{55555, 0, 0, 0}};
  s21_decimal value_2 = {{66666, 0, 0, 262144}};
  s21_decimal result = {{0}};
  s21_decimal correct_answer = {{555483334, 0, 0, 262144}};
  int function_returned = s21_sub(value_1, value_2, &result);

  ck_assert_uint_eq(function_returned, 0);
  compare(result, correct_answer);
}
END_TEST

START_TEST(s21_sub_10) {
  s21_decimal value_1 = {{4294967295, 0, 0, 2147614720}};
  s21_decimal value_2 = {{23465246, 0, 0, 2147549184}};
  s21_decimal result = {{0}};
  s21_decimal correct_answer = {{4060314835, 0, 0, 2147614720}};
  int function_returned = s21_sub(value_1, value_2, &result);

  ck_assert_uint_eq(function_returned, 0);
  compare(result, correct_answer);
}
END_TEST

START_TEST(s21_sub_11) {
  s21_decimal value_1 = {{4294967295, 0, 0, 0}};
  s21_decimal value_2 = {{4294967295, 100, 0, 0}};
  s21_decimal result = {{0}};
  s21_decimal correct_answer = {{0, 100, 0, 2147483648}};
  int function_returned = s21_sub(value_1, value_2, &result);

  ck_assert_uint_eq(function_returned, 0);
  compare(result, correct_answer);
}
END_TEST

START_TEST(s21_sub_12) {
  s21_decimal value_1 = {{4294967295, 4563654, 0, 2148139008}};
  s21_decimal value_2 = {{23465246, 364563, 0, 2148270080}};
  s21_decimal result = {{0}};
  s21_decimal correct_answer = {{4271501950, 456000936, 0, 2148270080}};
  int function_returned = s21_sub(value_1, value_2, &result);

  ck_assert_uint_eq(function_returned, 0);
  compare(result, correct_answer);
}
END_TEST

START_TEST(s21_sub_13) {
  s21_decimal value_1 = {{4294967295, 345634, 0, 2147876864}};
  s21_decimal value_2 = {{23465246, 45634, 0, 327680}};
  s21_decimal result = {{0}};
  s21_decimal correct_answer = {{234652459, 801975, 0, 2147876864}};
  int function_returned = s21_sub(value_1, value_2, &result);

  ck_assert_uint_eq(function_returned, 0);
  compare(result, correct_answer);
}
END_TEST

START_TEST(s21_sub_14) {
  s21_decimal value_1 = {{4294967295, 345634, 0, 393216}};
  s21_decimal value_2 = {{23465246, 45634, 0, 2147811328}};
  s21_decimal result = {{0}};
  s21_decimal correct_answer = {{234652459, 801975, 0, 393216}};
  int function_returned = s21_sub(value_1, value_2, &result);

  ck_assert_uint_eq(function_returned, 0);
  compare(result, correct_answer);
}
END_TEST

START_TEST(s21_sub_15) {
  s21_decimal value_1 = {{4294967295, 4294967295, 2147483647, 1638400}};
  s21_decimal value_2 = {{4294967295, 4294967295, 0, 983040}};
  s21_decimal result = {{0}};
  s21_decimal correct_answer = {{4153960755, 858993458, 785251635, 2149056512}};
  int function_returned = s21_sub(value_1, value_2, &result);

  ck_assert_uint_eq(function_returned, 0);
  compare(result, correct_answer);
}

START_TEST(s21_sub_16) {
  s21_decimal value_1 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal value_2 = {{4294967294, 4294967295, 4294967295, 0}};
  s21_decimal result = {{0}};
  s21_decimal correct_answer = {{1, 0, 0, 0}};
  int function_returned = s21_sub(value_1, value_2, &result);

  ck_assert_uint_eq(function_returned, 0);
  compare(result, correct_answer);
}

START_TEST(s21_sub_17) {
  s21_decimal value_1 = {{4294967295, 4294967295, 4294967295, 1835008}};
  s21_decimal value_2 = {{4294967294, 4294967295, 4294967295, 0}};

  s21_decimal result = {{0}};
  s21_decimal correct_answer = {
      {4294967286, 4294967295, 4294967295, 2147483648}};
  int function_returned = s21_sub(value_1, value_2, &result);

  ck_assert_uint_eq(function_returned, 0);
  compare(result, correct_answer);
}
END_TEST

START_TEST(s21_sub_18) {
  s21_decimal value_1 = {{4294967295, 4294967295, 4294967295}};
  s21_decimal value_2 = {{54, 0, 0, 0b00000000000000100000000000000000}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{0xFFFFFFFE, 4294967295, 4294967295}};
  int function_returned = s21_sub(value_1, value_2, &result);

  ck_assert_uint_eq(function_returned, 0);
  compare(result, expected);
}

START_TEST(s21_sub_19) {
  s21_decimal value_1 = {
      {0x88c7bcb6, 0x9bdf88, 0, 0b10000000000000100000000000000000}};
  s21_decimal value_2 = {
      {4294967295, 4294967295, 4294967295, 0b10000000000000000000000000000000}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{0xf4646712, 0xfffe70f6, 0xffffffff}};
  int function_returned = s21_sub(value_1, value_2, &result);

  ck_assert_uint_eq(function_returned, 0);
  compare(result, expected);
}

START_TEST(s21_sub_20) {
  s21_decimal value_1 = {{4294967295, 4294967295, 4294967295, 2147483648}};
  s21_decimal value_2 = {{1, 0, 0, 0}};
  s21_decimal result = {{0}};
  s21_decimal correct_answer = {{0, 0, 0, 0}};
  int function_returned = s21_sub(value_1, value_2, &result);

  ck_assert_uint_eq(function_returned, 2);
  compare(result, correct_answer);
}
END_TEST

START_TEST(s21_sub_21) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(s21_sub_22) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(s21_sub_23) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(s21_sub_24) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(s21_sub_25) {
  s21_decimal val1 = {{8, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(s21_sub_26) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(s21_sub_27) {
  s21_decimal val1 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(s21_sub_28) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(s21_sub_29) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(s21_sub_30) {
  s21_decimal val1 = {{8, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(s21_sub_31) {
  s21_decimal val1 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(s21_sub_32) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{4, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(2, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(s21_sub_33) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal val2 = {{4, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(s21_sub_34) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(s21_sub_35) {
  s21_decimal val1 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal res;
  ck_assert_int_eq(2, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(s21_sub_36) {
  s21_decimal val1 = {{4, 0, 0, 0}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(s21_sub_37) {
  s21_decimal val1 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(s21_sub_38) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal val2 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(1, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(s21_sub_39) {
  s21_decimal val1 = {{4, 0, 0, 0}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(1, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(s21_sub_40) {
  s21_decimal val1 = {{4, 0, 0, 0}};
  s21_decimal val2 = {{4, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(s21_sub_41) {
  s21_decimal dec1;
  s21_decimal dec2;
  int tmp1 = 100;
  int tmp2 = 99999;
  int res_s21 = 0;
  int res = -99899;
  s21_decimal res1;
  s21_from_int_to_decimal(tmp1, &dec1);
  s21_from_int_to_decimal(tmp2, &dec2);
  s21_sub(dec1, dec2, &res1);
  s21_from_decimal_to_int(res1, &res_s21);
  ck_assert_int_eq(res_s21, res);
}
END_TEST

START_TEST(s21_sub_42) {
  s21_decimal dec1;
  s21_decimal dec2;
  int tmp1 = -100;
  int tmp2 = -99999;
  int res_s21 = 0;
  s21_decimal res1;
  int res = 99899;
  s21_from_int_to_decimal(tmp1, &dec1);
  s21_from_int_to_decimal(tmp2, &dec2);
  s21_sub(dec1, dec2, &res1);
  s21_from_decimal_to_int(res1, &res_s21);
  ck_assert_int_eq(res_s21, res);
}
END_TEST

START_TEST(s21_sub_43) {
  s21_decimal x = {{3, 0, 0, 0}};
  s21_decimal y = {{2, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_decimal res = {{1, 0, 0, 0}};
  ck_assert_int_eq(s21_sub(x, y, &z), 0);
  compare(z, res);
}
END_TEST

START_TEST(s21_sub_44) {
  s21_decimal x = {{3, 0, 0, 0}};
  s21_decimal y = {{2, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_decimal res = {{1, 0, 0, 0x80000000}};
  ck_assert_int_eq(s21_sub(y, x, &z), 0);
  compare(z, res);
}
END_TEST

START_TEST(s21_sub_45) {
  s21_decimal x = {{3, 0, 0, 0x80000000}};
  s21_decimal y = {{2, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_decimal res = {{5, 0, 0, 0x80000000}};
  ck_assert_int_eq(s21_sub(x, y, &z), 0);
  compare(z, res);
}
END_TEST

START_TEST(s21_sub_46) {
  s21_decimal x = {{3, 0, 0, 0x80000000}};
  s21_decimal y = {{2, 0, 0, 0x80000000}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_decimal res = {{1, 0, 0, 0x80000000}};
  ck_assert_int_eq(s21_sub(x, y, &z), 0);
  compare(z, res);
}
END_TEST

START_TEST(s21_sub_47) {
  s21_decimal x = {{3, 0, 0, 0}};
  s21_decimal y = {{2, 0, 0, 0x80000000}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_decimal res = {{5, 0, 0, 0}};
  ck_assert_int_eq(s21_sub(x, y, &z), 0);
  compare(z, res);
}
END_TEST

START_TEST(s21_sub_48) {
  s21_decimal x = {{2, 0, 0, 0}};
  s21_decimal y = {{0xfffffffe, 0xffffffff, 0xffffffff, 0x80000000}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_sub(x, y, &z), 1);
  compare(z, res);
}
END_TEST

START_TEST(s21_sub_49) {
  s21_decimal x = {{2, 0, 0, 0x80000000}};
  s21_decimal y = {{0xfffffffe, 0xffffffff, 0xffffffff, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_sub(x, y, &z), 2);
  compare(z, res);
}
END_TEST

START_TEST(s21_sub_50) {
  s21_decimal x = {{0x00000037, 0x00000000, 0x00000000, 0x001C0000}};
  s21_decimal y = {{0x00000002, 0x00000000, 0x00000000, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_decimal res = {{0x1FFFFFC9, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  ck_assert_int_eq(s21_sub(x, y, &z), 0);
  for (int i = 3; i >= 0; i--) {
    ck_assert_int_eq(z.bits[i], res.bits[i]);
  }
}
END_TEST

START_TEST(s21_sub_51) {
  s21_decimal x = {{0, 1, 0, 0}};
  s21_decimal y = {{1, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_decimal res = {{0xffffffff, 0, 0, 0}};
  ck_assert_int_eq(s21_sub(x, y, &z), 0);
  compare(z, res);
}
END_TEST

START_TEST(s21_sub_52) {
  s21_decimal x = {{0x00000037, 0x00000000, 0x00000000, 0x001C0000}};
  s21_decimal y = {{2, 0, 0, 0x80000000}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_decimal res = {{0x020000037, 0x7C4A04C2, 0x409F9CBC, 0x001C0000}};
  ck_assert_int_eq(s21_sub(x, y, &z), 0);
  compare(z, res);
}
END_TEST

START_TEST(s21_sub_53) {
  s21_decimal x = {{0x00000037, 0x00000000, 0x00000000, 0x001C0000}};
  s21_decimal y = {{2, 0, 0, 0x80000000}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_decimal res = {{0x1FFFFFC9, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  ck_assert_int_eq(s21_add(x, y, &z), 0);
  compare(z, res);
}
END_TEST

START_TEST(s21_sub_54) {
  s21_decimal x = {{0x000000A1, 0x00000000, 0x00000000, 0x80020000}};
  s21_decimal y = {{0x00000005, 0x00000000, 0x00000000, 0x00010000}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_decimal res = {{0x000000D3, 0x00000000, 0x00000000, 0x80020000}};
  ck_assert_int_eq(s21_sub(x, y, &z), 0);
  compare(z, res);
}
END_TEST

Suite *test_s21_sub() {
  Suite *suite = suite_create("s21_sub");
  TCase *t_case = tcase_create("s21_sub");

  suite_add_tcase(suite, t_case);
  tcase_add_test(t_case, s21_sub_1);
  tcase_add_test(t_case, s21_sub_2);
  tcase_add_test(t_case, s21_sub_3);
  tcase_add_test(t_case, s21_sub_4);
  tcase_add_test(t_case, s21_sub_5);
  tcase_add_test(t_case, s21_sub_6);
  tcase_add_test(t_case, s21_sub_7);
  tcase_add_test(t_case, s21_sub_8);
  tcase_add_test(t_case, s21_sub_9);
  tcase_add_test(t_case, s21_sub_10);
  tcase_add_test(t_case, s21_sub_11);
  tcase_add_test(t_case, s21_sub_12);
  tcase_add_test(t_case, s21_sub_13);
  tcase_add_test(t_case, s21_sub_14);
  tcase_add_test(t_case, s21_sub_15);
  tcase_add_test(t_case, s21_sub_16);
  tcase_add_test(t_case, s21_sub_17);
  tcase_add_test(t_case, s21_sub_18);
  tcase_add_test(t_case, s21_sub_19);
  tcase_add_test(t_case, s21_sub_20);
  tcase_add_test(t_case, s21_sub_21);
  tcase_add_test(t_case, s21_sub_22);
  tcase_add_test(t_case, s21_sub_23);
  tcase_add_test(t_case, s21_sub_24);
  tcase_add_test(t_case, s21_sub_25);
  tcase_add_test(t_case, s21_sub_26);
  tcase_add_test(t_case, s21_sub_27);
  tcase_add_test(t_case, s21_sub_28);
  tcase_add_test(t_case, s21_sub_29);
  tcase_add_test(t_case, s21_sub_30);
  tcase_add_test(t_case, s21_sub_31);
  tcase_add_test(t_case, s21_sub_32);
  tcase_add_test(t_case, s21_sub_33);
  tcase_add_test(t_case, s21_sub_34);
  tcase_add_test(t_case, s21_sub_35);
  tcase_add_test(t_case, s21_sub_36);
  tcase_add_test(t_case, s21_sub_37);
  tcase_add_test(t_case, s21_sub_38);
  tcase_add_test(t_case, s21_sub_39);
  tcase_add_test(t_case, s21_sub_40);
  tcase_add_test(t_case, s21_sub_41);
  tcase_add_test(t_case, s21_sub_42);
  tcase_add_test(t_case, s21_sub_43);
  tcase_add_test(t_case, s21_sub_44);
  tcase_add_test(t_case, s21_sub_45);
  tcase_add_test(t_case, s21_sub_46);
  tcase_add_test(t_case, s21_sub_47);
  tcase_add_test(t_case, s21_sub_48);
  tcase_add_test(t_case, s21_sub_49);
  tcase_add_test(t_case, s21_sub_50);
  tcase_add_test(t_case, s21_sub_51);
  tcase_add_test(t_case, s21_sub_52);
  tcase_add_test(t_case, s21_sub_53);
  tcase_add_test(t_case, s21_sub_54);

  return suite;
}