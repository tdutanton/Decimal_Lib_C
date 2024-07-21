#include "s21_test.h"

START_TEST(s21_add_1) {
  s21_decimal first = {
      {0b00000000000000000000000000000001, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b10000000000000000000000000000000}};
  s21_decimal second = {
      {0b00000000000000000000000000000001, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b10000000000000000000000000000000}};
  s21_decimal decimal_check = {{2, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal decimal_result = init_zero_decimal();
  s21_add(first, second, &decimal_result);
  ck_assert_int_eq((s21_add(first, second, &decimal_result)), 0);
  compare(decimal_check, decimal_result);
}
END_TEST

START_TEST(s21_add_2) {
  s21_decimal first = {{10, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal second = {{5, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal decimal_check = {{15, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal decimal_result = init_zero_decimal();
  s21_add(first, second, &decimal_result);
  ck_assert_int_eq((s21_add(first, second, &decimal_result)), 0);
  compare(decimal_check, decimal_result);
}
END_TEST

START_TEST(s21_add_3) {
  s21_decimal first = {{10, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal second = {{5, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal decimal_check = {{5, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal decimal_result = init_zero_decimal();
  s21_add(first, second, &decimal_result);
  ck_assert_int_eq((s21_add(first, second, &decimal_result)), 0);
  compare(decimal_check, decimal_result);
}
END_TEST

START_TEST(s21_add_4) {
  s21_decimal first = {{10, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal second = {{5, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal decimal_check = {{15, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal decimal_result = init_zero_decimal();
  s21_add(first, second, &decimal_result);
  ck_assert_int_eq((s21_add(first, second, &decimal_result)), 0);
  compare(decimal_check, decimal_result);
}
END_TEST

START_TEST(s21_add_5) {
  s21_decimal first = {{10, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal second = {{5, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal decimal_check = {{5, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal decimal_result = init_zero_decimal();
  s21_add(first, second, &decimal_result);
  ck_assert_int_eq((s21_add(first, second, &decimal_result)), 0);
  compare(decimal_check, decimal_result);
}
END_TEST

START_TEST(s21_add_6) {
  s21_decimal first = {{10, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal second = {{15, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal decimal_check = {{5, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal decimal_result = init_zero_decimal();
  s21_add(first, second, &decimal_result);
  ck_assert_int_eq((s21_add(first, second, &decimal_result)), 0);
  compare(decimal_check, decimal_result);
}
END_TEST

START_TEST(s21_add_7) {
  s21_decimal first = {{100, 0, 0, 0b00000000000000100000000000000000}};
  s21_decimal second = {{10, 0, 0, 0b00000000000000010000000000000000}};
  s21_decimal decimal_check = {{200, 0, 0, 0b00000000000000100000000000000000}};
  s21_decimal decimal_result = init_zero_decimal();
  s21_add(first, second, &decimal_result);
  ck_assert_int_eq((s21_add(first, second, &decimal_result)), 0);
  compare(decimal_check, decimal_result);
}
END_TEST

START_TEST(s21_add_8) {
  s21_decimal first = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  s21_decimal second = {{0x88000001, 0x1F128130, 0x1027E72F, 0x1C0000}};
  s21_decimal decimal_check = {{0x9999999A, 0x99999999, 0x19999999, 0x0}};
  s21_decimal decimal_result = init_zero_decimal();
  s21_add(first, second, &decimal_result);
  ck_assert_int_eq((s21_add(first, second, &decimal_result)), 0);
  compare(decimal_check, decimal_result);
}
END_TEST

START_TEST(s21_add_9) {
  s21_decimal value_1 = {{55555, 0, 0, 0}};
  s21_decimal value_2 = {{66666, 0, 0, 262144}};
  s21_decimal result = {{0}};
  s21_decimal correct_answer = {{555616666, 0, 0, 262144}};
  int function_returned = s21_add(value_1, value_2, &result);

  ck_assert_uint_eq(function_returned, 0);
  compare(result, correct_answer);
}
END_TEST

START_TEST(s21_add_10) {
  s21_decimal value_1 = {{5555, 0, 0, 2147483648}};
  s21_decimal value_2 = {{333333333, 0, 0, 327680}};
  s21_decimal result = {{0}};
  s21_decimal correct_answer = {{222166667, 0, 0, 2147811328}};
  int function_returned = s21_add(value_1, value_2, &result);

  ck_assert_uint_eq(function_returned, 0);
  compare(result, correct_answer);
}
END_TEST

START_TEST(s21_add_11) {
  s21_decimal value_1 = {{4294967295, 0, 0, 327680}};
  s21_decimal value_2 = {{4294967295, 100, 0, 2148139008}};
  s21_decimal result = {{0}};
  s21_decimal correct_answer = {{4294867297, 99898, 0, 655360}};
  int function_returned = s21_add(value_1, value_2, &result);

  ck_assert_uint_eq(function_returned, 0);
  compare(result, correct_answer);
}
END_TEST

START_TEST(s21_add_12) {
  s21_decimal value_1 = {{4294967295, 613566756, 0, 2147811328}};
  s21_decimal value_2 = {{4294967295, 214748364, 0, 2147745792}};
  s21_decimal result = {{0}};
  s21_decimal correct_answer = {{4294967285, 2761050406, 0, 2147811328}};
  int function_returned = s21_add(value_1, value_2, &result);

  ck_assert_uint_eq(function_returned, 0);
  compare(result, correct_answer);
}
END_TEST

START_TEST(s21_add_13) {
  s21_decimal value_1 = {{346456, 53345, 0, 2147942400}};
  s21_decimal value_2 = {{567567, 3456567, 0, 262144}};
  s21_decimal result = {{0}};
  s21_decimal correct_answer = {{567220544, 3456513655, 0, 458752}};
  int function_returned = s21_add(value_1, value_2, &result);

  ck_assert_uint_eq(function_returned, 0);
  compare(result, correct_answer);
}
END_TEST

START_TEST(s21_add_14) {
  s21_decimal value_1 = {{4294967295, 4294967295, 2147483647, 1638400}};
  s21_decimal value_2 = {{4294967295, 4294967295, 0, 2148466688}};
  s21_decimal result = {{0}};
  s21_decimal correct_answer = {{4153960755, 858993458, 785251635, 2149056512}};
  int function_returned = s21_add(value_1, value_2, &result);

  ck_assert_uint_eq(function_returned, 0);
  compare(result, correct_answer);
}

START_TEST(s21_add_15) {
  s21_decimal value_1 = {{4294967295, 4294967295, 4294967295, 1638400}};
  s21_decimal value_2 = {{4294967295, 4294967295, 4294967295, 2148466688}};
  s21_decimal result = {{0}};
  s21_decimal correct_answer = {
      {2701727008, 2450292888, 4294967295, 2148466688}};
  int function_returned = s21_add(value_1, value_2, &result);

  ck_assert_uint_eq(function_returned, 0);
  compare(result, correct_answer);
}

START_TEST(s21_add_16) {
  s21_decimal value_1 = {{4294967295, 4294967295, 4294967295}};
  s21_decimal value_2 = {{54, 0, 0, 0b10000000000000100000000000000000}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{0xFFFFFFFE, 4294967295, 4294967295}};
  int function_returned = s21_add(value_1, value_2, &result);

  ck_assert_uint_eq(function_returned, 0);
  compare(result, expected);
}

START_TEST(s21_add_17) {
  s21_decimal value_1 = {{4294967294, 4294967295, 4294967295, 0}};
  s21_decimal value_2 = {{15, 0, 0, 65536}};

  s21_decimal result = {{0}};
  s21_decimal correct_answer = {{0, 0, 0, 0}};
  int function_returned = s21_add(value_1, value_2, &result);

  ck_assert_uint_eq(function_returned, 1);
  compare(result, correct_answer);
}
END_TEST

START_TEST(s21_add_18) {
  s21_decimal value_1 = {{4294967295, 4294967295, 4294967295, 2147483648}};
  s21_decimal value_2 = {{1, 0, 0, 2147483648}};

  s21_decimal result = {{0}};
  s21_decimal correct_answer = {{0, 0, 0, 0}};
  int function_returned = s21_add(value_1, value_2, &result);

  ck_assert_uint_eq(function_returned, 2);
  compare(result, correct_answer);
}
END_TEST

START_TEST(s21_add_19) {
  s21_decimal val1 = {{15, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(s21_add_20) {
  s21_decimal val1 = {{15, 0, 0, 0}};
  s21_decimal val2 = {{15, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(s21_add_21) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal val2 = {{1, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(1, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(s21_add_22) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(2, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(s21_add_23) {
  s21_decimal val1 = {{8, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(s21_add_24) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(s21_add_25) {
  s21_decimal val1 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(s21_add_26) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(s21_add_27) {
  s21_decimal val1 = {{0}};
  s21_decimal val2 = {{0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(s21_add_28) {
  s21_decimal val1 = {{4, 0, 0, 0}};
  s21_decimal val2 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(s21_add_29) {
  s21_decimal val1 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(s21_add_30) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{4, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(s21_add_31) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(2, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(s21_add_32) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal val2 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(s21_add_33) {
  s21_decimal val1 = {{4, 0, 0, 0}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(s21_add_34) {
  s21_decimal val1 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(s21_add_35) {
  s21_decimal val1 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(2, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(s21_add_36) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  set_power(&val1, 5);
  set_power(&val2, 3);
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(s21_add_37) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  set_power(&val1, 5);
  set_power(&val2, 3);
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(s21_add_38) {
  int num1 = 42;
  int num2 = 30;
  int sum_int = 72;
  s21_decimal a = {{0}};
  s21_decimal b = {{0}};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_add(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, sum_int);
  ck_assert_int_eq(s21_add(a, b, &res_dec), 0);
}
END_TEST

START_TEST(s21_add_39) {
  int num1 = 1000;
  int num2 = 2000;
  int sum_int = 3000;
  s21_decimal a = {{0}};
  s21_decimal b = {{0}};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_add(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, sum_int);
}
END_TEST

START_TEST(s21_add_40) {
  int num1 = 0;
  int num2 = 0;
  int sum_int = 0;
  s21_decimal a = {{0}};
  s21_decimal b = {{0}};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_add(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, sum_int);
}
END_TEST

START_TEST(s21_add_41) {
  int num1 = -15;
  int num2 = 5;
  int sum_int = -10;
  s21_decimal a = {{0}};
  s21_decimal b = {{0}};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_add(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, sum_int);
}
END_TEST

START_TEST(s21_add_42) {
  int num1 = 11115;
  int num2 = 5;
  int sum_int = 11120;
  s21_decimal a = {{0}};
  s21_decimal b = {{0}};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_add(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, sum_int);
}
END_TEST

START_TEST(s21_add_43) {
  int num1 = -1;
  int num2 = -10;
  int sum_int = -11;
  s21_decimal a = {{0}};
  s21_decimal b = {{0}};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_add(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, sum_int);
}
END_TEST

START_TEST(s21_add_44) {
  s21_decimal src1, src2;
  int a = -1234;
  int b = 234;
  int res_origin = -1000;
  s21_from_int_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_add(src1, src2, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(s21_add_45) {
  s21_decimal src1, src2;
  int a = -9403;
  int b = 234;
  int res_origin = -9169;
  s21_from_int_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_add(src1, src2, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(s21_add_46) {
  s21_decimal src1, src2;
  int a = 9403;
  int b = 202;
  int res_origin = 9605;
  s21_from_int_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_add(src1, src2, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(s21_add_47) {
  s21_decimal src1, src2;
  int a = 450;
  int b = -50;
  int res_origin = 400;
  s21_from_int_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_add(src1, src2, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(s21_add_48) {
  s21_decimal src1, src2;
  float num1 = 7.25;
  float num2 = 9.5;
  float res_origin = 16.75;
  s21_from_float_to_decimal(num1, &src1);
  s21_from_float_to_decimal(num2, &src2);
  s21_decimal res_dec = {0};
  float res_float = 0.0;
  s21_add(src1, src2, &res_dec);
  s21_from_decimal_to_float(res_dec, &res_float);
  ck_assert_float_eq(res_float, res_origin);
}
END_TEST

START_TEST(s21_add_49) {
  s21_decimal src1, src2;
  int num1 = -1234;
  float num2 = 1.234;
  float res_origin = -1232.766;
  s21_from_int_to_decimal(num1, &src1);
  s21_from_float_to_decimal(num2, &src2);
  s21_decimal res_dec = {0};
  float res_float = 0.0;
  s21_add(src1, src2, &res_dec);
  s21_from_decimal_to_float(res_dec, &res_float);
  ck_assert_float_eq(res_float, res_origin);
}
END_TEST

START_TEST(s21_add_50) {
  s21_decimal src1 = {{0}};
  s21_decimal src2 = {{0}};
  int num1 = -1234;
  float num2 = -1.234;
  float res_origin = -1235.234;
  s21_from_int_to_decimal(num1, &src1);
  s21_from_float_to_decimal(num2, &src2);
  s21_decimal res_dec = {0};
  float res_float = 0.0;
  s21_add(src1, src2, &res_dec);
  s21_from_decimal_to_float(res_dec, &res_float);
  ck_assert_float_eq(res_float, res_origin);
}
END_TEST

START_TEST(s21_add_51) {
  s21_decimal src1 = {{0}};
  s21_decimal src2 = {{0}};
  float num1 = -94;
  float num2 = 0.00234;
  float res_origin = 0;
  res_origin = num1 + num2;
  s21_from_float_to_decimal(num1, &src1);
  s21_from_float_to_decimal(num2, &src2);
  s21_decimal res_dec = {0};
  float res_float = 0.0;
  s21_add(src1, src2, &res_dec);
  s21_from_decimal_to_float(res_dec, &res_float);
  ck_assert_float_eq(res_float, res_origin);
}
END_TEST

START_TEST(s21_add_52) {
  s21_decimal src1 = {{0}};
  s21_decimal src2 = {{0}};
  float num1 = -940.3;
  float num2 = 0.000234;
  float res_origin = -940.299766;
  s21_from_float_to_decimal(num1, &src1);
  s21_from_float_to_decimal(num2, &src2);
  s21_decimal res_dec = {0};
  float res_float = 0.0;
  s21_add(src1, src2, &res_dec);
  s21_from_decimal_to_float(res_dec, &res_float);
  ck_assert_float_eq(res_float, res_origin);
}
END_TEST

START_TEST(s21_add_53) {
  s21_decimal src1 = {{0}};
  s21_decimal src2 = {{0}};
  float num1 = -0.9403;
  float num2 = 0.000234;
  float res_origin = -0.940066;
  s21_from_float_to_decimal(num1, &src1);
  s21_from_float_to_decimal(num2, &src2);
  s21_decimal res_dec = {0};
  float res_float = 0.0;
  s21_add(src1, src2, &res_dec);
  s21_from_decimal_to_float(res_dec, &res_float);
  ck_assert_float_eq(res_float, res_origin);
}
END_TEST

START_TEST(s21_add_54) {
  s21_decimal src1 = {{0}};
  s21_decimal src2 = {{0}};
  float num1 = -0.9403;
  float num2 = -112.0234;
  float res_origin = -112.9637;
  s21_from_float_to_decimal(num1, &src1);
  s21_from_float_to_decimal(num2, &src2);
  s21_decimal res_dec = {0};
  float res_float = 0.0;
  s21_add(src1, src2, &res_dec);
  s21_from_decimal_to_float(res_dec, &res_float);
  ck_assert_float_eq(res_float, res_origin);
}
END_TEST

START_TEST(s21_add_55) {
  s21_decimal src1 = {{0}};
  s21_decimal src2 = {{0}};
  float num1 = -0.94e03;
  float num2 = -112.0234;
  float res_origin = -1052.0234;
  s21_from_float_to_decimal(num1, &src1);
  s21_from_float_to_decimal(num2, &src2);
  s21_decimal res_dec = {0};
  float res_float = 0.0;
  s21_add(src1, src2, &res_dec);
  s21_from_decimal_to_float(res_dec, &res_float);
  ck_assert_float_eq(res_float, res_origin);
}
END_TEST

START_TEST(s21_add_56) {
  s21_decimal src1 = {{0}};
  s21_decimal src2 = {{0}};
  float num1 = -0.94e03;
  float num2 = -112.0e2;
  float res_origin = -12140;
  s21_from_float_to_decimal(num1, &src1);
  s21_from_float_to_decimal(num2, &src2);
  s21_decimal res_dec = {0};
  float res_float = 0.0;
  s21_add(src1, src2, &res_dec);
  s21_from_decimal_to_float(res_dec, &res_float);
  ck_assert_float_eq(res_float, res_origin);
}
END_TEST

START_TEST(s21_add_57) {
  s21_decimal dec1 = {{0}};
  s21_decimal dec2 = {{0}};
  int tmp1 = 100;
  int tmp2 = 99999;
  int res_s21 = 0;
  int res = 100099;
  s21_decimal res1 = {{0}};
  s21_from_int_to_decimal(tmp1, &dec1);
  s21_from_int_to_decimal(tmp2, &dec2);
  s21_add(dec1, dec2, &res1);
  s21_from_decimal_to_int(res1, &res_s21);
  ck_assert_int_eq(res_s21, res);
}
END_TEST

START_TEST(s21_add_58) {
  s21_decimal dec1 = {{0}};
  s21_decimal dec2 = {{0}};
  int tmp1 = -100;
  int tmp2 = -99999;
  int res_s21 = 0;
  int res = -100099;
  s21_decimal res1 = {{0}};
  s21_from_int_to_decimal(tmp1, &dec1);
  s21_from_int_to_decimal(tmp2, &dec2);
  s21_add(dec1, dec2, &res1);
  s21_from_decimal_to_int(res1, &res_s21);
  ck_assert_int_eq(res_s21, res);
}
END_TEST

START_TEST(s21_add_59) {
  s21_decimal dec1 = {{0}};
  s21_decimal dec2 = {{0}};
  int tmp1 = 2147483647;
  int tmp2 = -2147483647;
  int res_s21 = 0;
  int res = 0;
  s21_decimal res1 = {{0}};
  s21_from_int_to_decimal(tmp1, &dec1);
  s21_from_int_to_decimal(tmp2, &dec2);
  s21_add(dec1, dec2, &res1);
  s21_from_decimal_to_int(res1, &res_s21);
  ck_assert_int_eq(res_s21, res);
}
END_TEST

START_TEST(s21_add_60) {
  s21_decimal dec1 = {{0}};
  s21_decimal dec2 = {{0}};
  int tmp1 = -2147483647;
  int tmp2 = 2147483647;
  int res_s21 = 0;
  int res = 0;
  s21_decimal res1 = {{0}};
  s21_from_int_to_decimal(tmp1, &dec1);
  s21_from_int_to_decimal(tmp2, &dec2);
  s21_add(dec1, dec2, &res1);
  s21_from_decimal_to_int(res1, &res_s21);
  ck_assert_int_eq(res_s21, res);
}
END_TEST

START_TEST(s21_add_61) {
  int tmp1 = 4294967295;
  s21_decimal dec1 = {{tmp1, tmp1, tmp1, 0}};
  s21_decimal dec2 = {{1, 0, 0, 0}};
  s21_decimal res1 = {{0}};
  int ret_s21 = s21_add(dec1, dec2, &res1);
  ck_assert_int_eq(1, ret_s21);
}
END_TEST

START_TEST(s21_add_62) {
  int tmp1 = 4294967295;
  float tmp2 = pow(2, 31);
  s21_decimal dec1 = {{tmp1, tmp1, tmp1, tmp2}};
  s21_decimal dec2 = {{1, 0, 0, tmp2}};
  s21_decimal res1 = {{0}};
  int ret_s21 = s21_add(dec1, dec2, &res1);
  ck_assert_int_eq(2, ret_s21);
}
END_TEST

START_TEST(s21_add_63) {
  s21_decimal src1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal src2 = {0};
  float a = 0.01448;
  s21_from_float_to_decimal(a, &src2);
  s21_decimal res_dec = {0};
  s21_add(src1, src2, &res_dec);
  ck_assert_int_eq(s21_add(src1, src2, &res_dec), 0);
}
END_TEST

START_TEST(s21_add_64) {
  s21_decimal src1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(INT_MAX)}};
  s21_decimal src2 = {0};
  float a = -0.01448;
  s21_from_float_to_decimal(a, &src2);
  s21_decimal res_dec = {0};
  s21_add(src1, src2, &res_dec);
  ck_assert_int_eq(s21_add(src1, src2, &res_dec), 0);
}
END_TEST

START_TEST(s21_add_65) {
  s21_decimal c = {{5, 0, 0, 0}};
  s21_decimal d = {{5, 0, 0, 0}};
  s21_decimal etalon = {{10, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal* p_res = &res;

  int add = s21_add(c, d, p_res);
  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(add, 0);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_add_66) {
  s21_decimal c = {{100, 0, 0, 0}};
  s21_decimal d = {{100, 0, 0, 0}};
  s21_decimal etalon = {{100, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal* p_res = &res;

  int add = s21_add(c, d, p_res);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(add, 0);
  ck_assert_int_eq(equal, 0);
}
END_TEST

START_TEST(s21_add_67) {
  s21_decimal c = {{2147483647, 0, 0, 0}};
  s21_decimal d = {{2147483647, 0, 0, 0}};
  s21_decimal etalon = {{4294967294, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal* p_result = &result;

  int add = s21_add(c, d, p_result);
  ck_assert_int_eq(add, 0);

  int equal = s21_is_equal(result, etalon);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_add_68) {
  s21_decimal c = {{1000, 0, 0, 0}};
  s21_decimal d = {{1000, 0, 0, 0}};
  s21_decimal etalon = {{2000, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal* p_result = &result;

  int add = s21_add(c, d, p_result);
  ck_assert_int_eq(add, 0);

  int equal = s21_is_equal(result, etalon);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_add_69) {
  s21_decimal c = {{1000, 0, 0, ~(INT_MAX)}};
  s21_decimal d = {{1000, 0, 0, 0}};
  s21_decimal etalon = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal* p_result = &result;

  int add = s21_add(c, d, p_result);
  ck_assert_int_eq(add, 0);

  int equal = s21_is_equal(result, etalon);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_add_70) {
  s21_decimal c = {{1, 0, 0, ~(INT_MAX)}};
  s21_decimal d = {{1, 0, 0, ~(INT_MAX)}};
  s21_decimal etalon = {{2, 0, 0, ~(INT_MAX)}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal* p_result = &result;

  int add = s21_add(c, d, p_result);
  ck_assert_int_eq(add, 0);

  int equal = s21_is_equal(*p_result, etalon);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_add_71) {
  s21_decimal c = {{0, 0, 0, 0}};
  s21_decimal d = {{0, 0, 0, 0}};
  s21_decimal etalon = {{0, 0, 0, 0}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal* p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_add_72) {
  s21_decimal c = {{1, 0, 0, 0}};
  s21_decimal d = {{1, 0, 0, 0}};
  s21_decimal etalon = {{2, 0, 0, 0}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal* p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_add_73) {
  s21_decimal c = {{1000, 0, 0, 0}};
  s21_decimal d = {{1000, 0, 0, 0}};
  s21_decimal etalon = {{2000, 0, 0, 0}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal* p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_add_74) {
  s21_decimal c = {{INT_MAX, 0, 0, 0}};
  s21_decimal d = {{INT_MAX, 0, 0, 0}};
  s21_decimal etalon = {{4294967294, 0, 0, 0}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal* p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_add_75) {
  s21_decimal c = {{INT_MAX, 0, 0, 0}};
  s21_decimal d = {{INT_MAX, 0, 0, 0}};
  s21_decimal etalon = {{UINT32_MAX - 1, 0, 0, 0}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal* p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_add_76) {
  s21_decimal c = {{UINT32_MAX, 0, 0, 0}};
  s21_decimal d = {{1, 0, 0, 0}};
  s21_decimal etalon = {{0, 1, 0, 0}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal* p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  compare(res, etalon);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_add_77) {
  s21_decimal c = {{0, UINT_MAX - 1, 0, 0}};
  s21_decimal d = {{0, 1, 0, 0}};
  s21_decimal etalon = {{0, UINT_MAX, 0, 0}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal* p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_add_78) {
  s21_decimal c = {{0, 0, UINT_MAX - 1, 0}};
  s21_decimal d = {{0, 0, 1, 0}};
  s21_decimal etalon = {{0, 0, UINT_MAX, 0}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal* p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_add_79) {
  s21_decimal c = {{0, 0, 0, ~(INT_MAX)}};
  s21_decimal d = {{0, 0, 0, ~(INT_MAX)}};
  s21_decimal etalon = {{0, 0, 0, ~(INT_MAX)}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal* p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_add_80) {
  s21_decimal c = {{1, 0, 0, ~(INT_MAX)}};
  s21_decimal d = {{1, 0, 0, 0}};
  s21_decimal etalon = {{0, 0, 0, 0}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal* p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_add_81) {
  s21_decimal c = {{1, 0, 0, ~(INT_MAX)}};
  s21_decimal d = {{1, 0, 0, ~(INT_MAX)}};
  s21_decimal etalon = {{2, 0, 0, ~(INT_MAX)}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal* p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  compare(res, etalon);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_add_82) {
  s21_decimal c = {{11, 0, 0, EXPONENT_PLUS_1}};
  s21_decimal d = {{0, 0, 0, 0}};
  s21_decimal etalon = {{11, 0, 0, EXPONENT_PLUS_1}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal* p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_add_83) {
  s21_decimal c = {{11, 0, 0, EXPONENT_PLUS_1}};
  s21_decimal d = {{1, 0, 0, 0}};
  s21_decimal etalon = {{21, 0, 0, EXPONENT_PLUS_1}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal* p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  compare(res, etalon);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_add_84) {
  s21_decimal c = {{111, 0, 0, EXPONENT_PLUS_1}};
  s21_decimal d = {{1, 0, 0, 0}};
  s21_decimal etalon = {{121, 0, 0, EXPONENT_PLUS_1}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal* p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  compare(res, etalon);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_add_85) {
  s21_decimal c = {{111, 0, 0, EXPONENT_PLUS_2}};
  s21_decimal d = {{1, 0, 0, 0}};
  s21_decimal etalon = {{1111, 0, 0, EXPONENT_PLUS_2}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal* p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  compare(res, etalon);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_add_86) {
  s21_decimal c = {0};
  c.bits[0] = 0b11111111111111111111111111111110;
  c.bits[1] = 0b00000000000000000000000000000000;
  c.bits[2] = 0b00000000000000000000000000000000;
  c.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal d = {{1, 0, 0, 0}};
  s21_decimal etalon = {0};
  etalon.bits[0] = 0b11111111111111111111111111111111;
  etalon.bits[1] = 0b00000000000000000000000000000000;
  etalon.bits[2] = 0b00000000000000000000000000000000;
  etalon.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal* p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  compare(res, etalon);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_add_87) {
  s21_decimal c = {{UINT32_MAX - 1, UINT32_MAX, 0, 0}};
  s21_decimal d = {{1, 0, 0, 0}};
  s21_decimal etalon = {{UINT32_MAX, UINT32_MAX, 0, 0}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal* p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  compare(res, etalon);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_add_88) {
  s21_decimal c = {{0b00000000000000000001100101111001, 0, 0, 0}};
  s21_decimal d = {{0b00000000000000010010000110001001, 0, 0, 0}};
  s21_decimal etalon = {{0b00000000000000010011101100000010, 0, 0, 0}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal* p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_add_89) {
  s21_decimal c = {{0b10001001111001111111111111111111,
                    0b10001010110001110010001100000100, 0, 0}};
  s21_decimal d = {{0b00000000000000000000000000000001, 0, 0, 0}};
  s21_decimal etalon = {{0b10001001111010000000000000000000,
                         0b10001010110001110010001100000100, 0, 0}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal* p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_add_90) {
  s21_decimal c = {{UINT_MAX, UINT_MAX, 0, 0}};
  s21_decimal d = {{0b00000000000000000000000000000001, 0, 0, 0}};
  s21_decimal etalon = {{0, 0, 1, 0}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal* p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_add_91) {
  s21_decimal c = {
      {0b10000010111000100101101011101101, 0b11111001111010000010010110101101,
       0b10110000001111101111000010010100, 0b10000000000011100000000000000000}};
  s21_decimal d = {{0b00000011010000001001011100101110, 0, 0, 0}};
  s21_decimal etalon = {
      {0b01110001001010101101101011101101, 0b00101110001111001110000111111000,
       0b10110000001111101110111101101101, 0b10000000000011100000000000000000}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal* p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  compare(res, etalon);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_add_92) {
  s21_decimal c = {
      {0b10000010111000100101101011101101, 0b11111001111010000010010110101101,
       0b10110000001111101111000010010100, 0b10000000000011100000000000000000}};
  s21_decimal d = {
      {0b01001000000110110001111110011000, 0b11111011111111011000100101101101,
       0b00000000000001000110110101110111, 0b10000000000110000000000000000000}};
  s21_decimal etalon = {
      {0b10110110001010011011010111011010, 0b11111001111010100000110001111111,
       0b10110000001111101111000010010100, 0b10000000000011100000000000000000}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal* p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  compare(res, etalon);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_add_93) {
  s21_decimal src1, src2, origin;
  src1.bits[0] = 0b01001110111001000011100101110110;
  src1.bits[1] = 0b01001011001101011010000111011001;
  src1.bits[2] = 0b00011001101110010111010010111111;
  src1.bits[3] = 0b00000000000011110000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  origin.bits[0] = 0b01001110111001000011100101110110;
  origin.bits[1] = 0b01001011001101011010000111011001;
  origin.bits[2] = 0b00011001101110010111010010111111;
  origin.bits[3] = 0b00000000000011110000000000000000;

  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal* p_res = &result;

  int add = s21_add(src1, src2, p_res);
  ck_assert_int_eq(add, 0);

  compare(origin, result);

  int equal = s21_is_equal(result, origin);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_add_94) {
  s21_decimal c = {{0, 0, 0, 0}};
  s21_decimal d = {{0, 0, 0, 0}};
  s21_decimal etalon = {{0, 0, 0, 0}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal* p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_add_95) {
  s21_decimal c = {{1, 0, 0, 0}};
  s21_decimal d = {{1, 0, 0, 0}};
  s21_decimal etalon = {{2, 0, 0, 0}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal* p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_add_96) {
  s21_decimal c = {{1000, 0, 0, 0}};
  s21_decimal d = {{1000, 0, 0, 0}};
  s21_decimal etalon = {{2000, 0, 0, 0}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal* p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_add_97) {
  s21_decimal c = {{INT_MAX, 0, 0, 0}};
  s21_decimal d = {{INT_MAX, 0, 0, 0}};
  s21_decimal etalon = {{4294967294, 0, 0, 0}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal* p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_add_98) {
  s21_decimal c = {{INT_MAX, 0, 0, 0}};
  s21_decimal d = {{INT_MAX, 0, 0, 0}};
  s21_decimal etalon = {{UINT32_MAX - 1, 0, 0, 0}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal* p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_add_99) {
  s21_decimal c = {{UINT_MAX, 0, 0, 0}};
  s21_decimal d = {{1, 0, 0, 0}};
  s21_decimal etalon = {{0, 1, 0, 0}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal* p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  compare(res, etalon);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_add_100) {
  s21_decimal c = {{0, UINT_MAX - 1, 0, 0}};
  s21_decimal d = {{0, 1, 0, 0}};
  s21_decimal etalon = {{0, UINT_MAX, 0, 0}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal* p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_add_101) {
  s21_decimal c = {{0, 0, UINT_MAX - 1, 0}};
  s21_decimal d = {{0, 0, 1, 0}};
  s21_decimal etalon = {{0, 0, UINT_MAX, 0}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal* p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_add_102) {
  s21_decimal c = {{0, 0, 0, ~(INT_MAX)}};
  s21_decimal d = {{0, 0, 0, ~(INT_MAX)}};
  s21_decimal etalon = {{0, 0, 0, ~(INT_MAX)}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal* p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_add_103) {
  s21_decimal c = {{1, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal d = {{1, 0, 0, 0}};
  s21_decimal etalon = {{0, 0, 0, 0}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal* p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  compare(res, etalon);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_add_104) {
  s21_decimal c = {{1, 0, 0, ~(INT_MAX)}};
  s21_decimal d = {{1, 0, 0, ~(INT_MAX)}};
  s21_decimal etalon = {{2, 0, 0, ~(INT_MAX)}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal* p_res = &res;
  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  compare(res, etalon);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_add_105) {
  s21_decimal c = {{11, 0, 0, EXPONENT_PLUS_1}};
  s21_decimal d = {{0, 0, 0, 0}};
  s21_decimal etalon = {{11, 0, 0, EXPONENT_PLUS_1}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal* p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_add_106) {
  s21_decimal c = {{11, 0, 0, EXPONENT_PLUS_1}};
  s21_decimal d = {{1, 0, 0, 0}};
  s21_decimal etalon = {{21, 0, 0, EXPONENT_PLUS_1}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal* p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_add_107) {
  s21_decimal c = {{111, 0, 0, EXPONENT_PLUS_1}};
  s21_decimal d = {{1, 0, 0, 0}};
  s21_decimal etalon = {{121, 0, 0, EXPONENT_PLUS_1}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal* p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  compare(res, etalon);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_add_108) {
  s21_decimal c = {{111, 0, 0, EXPONENT_PLUS_2}};
  s21_decimal d = {{1, 0, 0, 0}};
  s21_decimal etalon = {{1111, 0, 0, EXPONENT_PLUS_2}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal* p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);
  compare(res, etalon);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_add_109) {
  s21_decimal c = {{0b00000000000000000001100101111001, 0, 0, 0}};
  s21_decimal d = {{0b00000000000000010010000110001001, 0, 0, 0}};
  s21_decimal etalon = {{0b00000000000000010011101100000010, 0, 0, 0}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal* p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_add_110) {
  s21_decimal c = {{0b10001001111001111111111111111111,
                    0b10001010110001110010001100000100, 0, 0}};
  s21_decimal d = {{0b00000000000000000000000000000001, 0, 0, 0}};
  s21_decimal etalon = {{0b10001001111010000000000000000000,
                         0b10001010110001110010001100000100, 0, 0}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal* p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_add_111) {
  s21_decimal c = {{UINT_MAX, UINT_MAX, 0, 0}};
  s21_decimal d = {{0b00000000000000000000000000000001, 0, 0, 0}};
  s21_decimal etalon = {{0, 0, 1, 0}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal* p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_add_112) {
  s21_decimal c = {
      {0b10000010111000100101101011101101, 0b11111001111010000010010110101101,
       0b10110000001111101111000010010100, 0b10000000000011100000000000000000}};
  s21_decimal d = {{0b00000011010000001001011100101110, 0, 0, 0}};
  s21_decimal etalon = {
      {0b01110001001010101101101011101101, 0b00101110001111001110000111111000,
       0b10110000001111101110111101101101, 0b10000000000011100000000000000000}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal* p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  compare(res, etalon);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_add_113) {
  s21_decimal src1 = {0};
  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b11111111111111111111111111111111;
  src1.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal src2 = {0};
  src2.bits[0] = 0b00000000000000000000000000000010;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000110000000000000000;
  s21_decimal s21_res = {0};
  ck_assert_int_eq(s21_add(src1, src2, &s21_res), 0);
}
END_TEST

START_TEST(s21_add_114) {
  s21_decimal src1 = {0};
  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b11111111111111111111111111111111;
  src1.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal src2 = {0};
  src2.bits[0] = 0b00000000000000000000000000000101;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000010000000000000000;
  s21_decimal s21_res = {0};
  ck_assert_int_eq(s21_add(src1, src2, &s21_res), 1);
}
END_TEST

START_TEST(s21_add_115) {
  s21_decimal src1 = {0};
  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b11111111111111111111111111111111;
  src1.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal src2 = {0};
  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal s21_res = {0};
  ck_assert_int_eq(s21_add(src1, src2, &s21_res), 1);
}
END_TEST

START_TEST(s21_add_116) {
  s21_decimal src1 = {0};
  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b11111111111111111111111111111111;
  src1.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal src2 = {0};
  src2.bits[0] = 0b00000000000000000000000000000010;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000110000000000000000;
  s21_decimal original_res = {0};
  original_res.bits[0] = 0b11111111111111111111111111111111;
  original_res.bits[1] = 0b11111111111111111111111111111111;
  original_res.bits[2] = 0b11111111111111111111111111111111;
  original_res.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal s21_res = {0};
  s21_add(src1, src2, &s21_res);
  ck_assert_int_eq(s21_add(src1, src2, &s21_res), 0);
  compare(s21_res, original_res);
}
END_TEST

START_TEST(s21_add_117) {
  s21_decimal src1 = {0};
  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b11111111111111111111111111111111;
  src1.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal src2 = {0};
  src2.bits[0] = 0b00000000000000000000000000000101;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000010000000000000000;
  s21_decimal original_res = {0};
  original_res.bits[0] = 0b11111111111111111111111111111110;
  original_res.bits[1] = 0b11111111111111111111111111111111;
  original_res.bits[2] = 0b11111111111111111111111111111111;
  original_res.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal s21_res = {0};
  s21_add(src1, src2, &s21_res);
  ck_assert_int_eq(s21_add(src1, src2, &s21_res), 0);
  compare(s21_res, original_res);
}
END_TEST

START_TEST(s21_add_118) {
  s21_decimal src1 = {0};
  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b11111111111111111111111111111111;
  src1.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal src2 = {0};
  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal original_res = {0};
  original_res.bits[0] = 0b11111111111111111111111111111110;
  original_res.bits[1] = 0b11111111111111111111111111111111;
  original_res.bits[2] = 0b11111111111111111111111111111111;
  original_res.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal s21_res = {0};
  s21_add(src1, src2, &s21_res);
  ck_assert_int_eq(s21_add(src1, src2, &s21_res), 0);
  compare(s21_res, original_res);
}
END_TEST

START_TEST(s21_add_119) {
  s21_decimal src1 = {{0}};
  src1.bits[0] = 0b00000000000000000000001111111111;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000010000000000000000;
  s21_decimal src2 = {0};
  src2.bits[0] = 0b00000000000000000000001111111111;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000100000000000000000;
  s21_decimal original_res = {0};
  original_res.bits[0] = 0b00000000000000000010101111110101;
  original_res.bits[1] = 0b00000000000000000000000000000000;
  original_res.bits[2] = 0b00000000000000000000000000000000;
  original_res.bits[3] = 0b00000000000000100000000000000000;
  s21_decimal s21_res = {0};
  s21_add(src1, src2, &s21_res);
  ck_assert_int_eq(s21_add(src1, src2, &s21_res), 0);
  compare(s21_res, original_res);
}
END_TEST

START_TEST(s21_add_120) {
  s21_decimal x = {{3, 0, 0, 0}};
  s21_decimal y = {{2, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_decimal res = {{5, 0, 0, 0}};
  ck_assert_int_eq(s21_add(x, y, &z), 0);
  compare(z, res);
}
END_TEST

START_TEST(s21_add_121) {
  s21_decimal x = {{1, 0, 0, 0}};
  s21_decimal y = {{0, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_decimal res = {{1, 0, 0, 0}};
  ck_assert_int_eq(s21_add(x, y, &z), 0);
  compare(z, res);
}
END_TEST

START_TEST(s21_add_122) {
  s21_decimal x = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x001C0000}};
  s21_decimal y = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x001C0000}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_decimal res = {{0x33333333, 0x33333333, 0x33333333, 0x001B0000}};
  ck_assert_int_eq(s21_add(x, y, &z), 0);
  compare(z, res);
}
END_TEST

START_TEST(s21_add_123) {
  s21_decimal x = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal y = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_add(x, y, &z), 1);
  compare(z, res);
}
END_TEST

START_TEST(s21_add_124) {
  s21_decimal x = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal y = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_add(x, y, &z), 2);
  compare(z, res);
}
END_TEST

START_TEST(s21_add_125) {
  s21_decimal x = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal y = {{1, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_add(x, y, &z), 1);
  compare(z, res);
}
END_TEST

START_TEST(s21_add_126) {
  s21_decimal x = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x001C0000}};
  s21_decimal y = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_add(x, y, &z), 1);
  compare(z, res);
}
END_TEST

START_TEST(s21_add_127) {
  s21_decimal x = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal y = {{1, 0, 0, 0}};
  set_power(&y, 1);
  s21_decimal z = {{0, 0, 0, 0}};
  s21_decimal res = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  ck_assert_int_eq(s21_add(x, y, &z), 0);
  compare(z, res);
}
END_TEST

START_TEST(s21_add_128) {
  s21_decimal x = {{1, 0, 0, 0x00000000}};
  s21_decimal y = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_decimal res = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  ck_assert_int_eq(s21_add(x, y, &z), 0);
  compare(z, res);
}
END_TEST

START_TEST(s21_add_129) {
  s21_decimal x = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal y = {{2, 0, 0, 0}};
  set_power(&y, 1);
  s21_decimal z = {{0, 0, 0, 0}};
  s21_decimal res = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  ck_assert_int_eq(s21_add(x, y, &z), 0);
  compare(z, res);
}
END_TEST

START_TEST(s21_add_130) {
  s21_decimal x = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal y = {{9, 0, 0, 0}};
  set_power(&y, 1);
  s21_decimal z = {{0, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_add(x, y, &z), 1);
  compare(z, res);
}
END_TEST

START_TEST(s21_add_131) {
  s21_decimal x = {{1, 0, 0, 0x00000000}};
  s21_decimal y = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x00010000}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_decimal res = {{0x9999999A, 0x99999999, 0x19999999, 00000000}};
  ck_assert_int_eq(s21_add(x, y, &z), 0);
  compare(res, z);
}
END_TEST

START_TEST(s21_add_132) {
  s21_decimal x = {{0xFFFFFFFF, 0, 0, 0}};
  s21_decimal y = {{1, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_decimal res = {{0, 1, 0, 0}};
  ck_assert_int_eq(s21_add(x, y, &z), 0);
  compare(z, res);
}
END_TEST

START_TEST(s21_add_133) {
  s21_decimal x = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  s21_decimal y = {{1, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_decimal res = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  ck_assert_int_eq(s21_add(x, y, &z), 0);
  compare(z, res);
}
END_TEST

START_TEST(s21_add_134) {
  s21_decimal x = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  s21_decimal y = {{13, 0, 0, 0}};
  set_power(&y, 1);
  s21_decimal z = {{0, 0, 0, 0}};
  s21_decimal res = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  ck_assert_int_eq(s21_add(x, y, &z), 0);
  compare(z, res);
}
END_TEST

START_TEST(s21_add_135) {
  s21_decimal x = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  s21_decimal y = {{19, 0, 0, 0}};
  set_power(&y, 1);
  s21_decimal z = {{0, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_add(x, y, &z), 1);
  compare(z, res);
}
END_TEST

START_TEST(s21_add_136) {
  s21_decimal x = {{8, 0, 0, 0x001C0000}};
  s21_decimal y = {{2, 0, 0, 0x001C0000}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_decimal res = {{1, 0, 0, 0b00000000000110110000000000000000}};
  ck_assert_int_eq(s21_add(x, y, &z), 0);
  compare(res, z);
}
END_TEST

START_TEST(s21_add_137) {
  s21_decimal x = {{0xFFFFFFFF, 0, 0, 0x00160000}};
  s21_decimal y = {{0x00000037, 0, 0, 0x00170000}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_decimal res = {{0x0000002D, 0x0000000A, 0, 0x00170000}};
  ck_assert_int_eq(s21_add(x, y, &z), 0);
  compare(z, res);
}
END_TEST

START_TEST(s21_add_138) {
  s21_decimal x = {{0xFFFFFFFF, 0x00000000, 0x00000000, 0x00160000}};
  s21_decimal y = {{0x00000038, 0x00000000, 0x00000000, 0x00170000}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_decimal res = {{0x0000002E, 0x0000000A, 0x00000000, 0x00170000}};
  ck_assert_int_eq(s21_add(x, y, &z), 0);
  compare(z, res);
}
END_TEST

START_TEST(s21_add_139) {
  s21_decimal x = {{0xFFFFFFFF, 0x00000000, 0x00000000, 0x00170000}};
  s21_decimal y = {{0x00000036, 0x00000000, 0x00000000, 0x00170000}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_decimal res = {{0x00000035, 0x00000001, 0x00000000, 0x00170000}};
  ck_assert_int_eq(s21_add(x, y, &z), 0);
  compare(z, res);
}
END_TEST

START_TEST(s21_add_140) {
  s21_decimal x = {{0x00000005, 0x00000000, 0x00000000, 0x001C0000}};
  s21_decimal y = {{0x00000005, 0x00000000, 0x00000000, 0x001C0000}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_decimal res = {
      {1, 0x00000000, 0x00000000, 0b00000000000110110000000000000000}};
  ck_assert_int_eq(s21_add(x, y, &z), 0);
  compare(z, res);
}
END_TEST

START_TEST(s21_add_141) {  // 0 0
  s21_decimal x = {{3, 0, 0, 0}};
  s21_decimal y = {{2, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_decimal res = {{5, 0, 0, 0}};
  ck_assert_int_eq(s21_add(x, y, &z), 0);
  compare(z, res);
}
END_TEST

START_TEST(s21_add_142) {  // 1 0
  s21_decimal x = {{3, 0, 0, 0x80000000}};
  s21_decimal y = {{2, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_decimal res = {{1, 0, 0, 0x80000000}};
  ck_assert_int_eq(s21_add(x, y, &z), 0);
  compare(z, res);
}
END_TEST

START_TEST(s21_add_143) {  // 1 1
  s21_decimal x = {{3, 0, 0, 0x80000000}};
  s21_decimal y = {{2, 0, 0, 0x80000000}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_decimal res = {{5, 0, 0, 0x80000000}};
  ck_assert_int_eq(s21_add(x, y, &z), 0);
  compare(z, res);
}
END_TEST

START_TEST(s21_add_144) {  // 0 1
  s21_decimal x = {{3, 0, 0, 0}};
  s21_decimal y = {{2, 0, 0, 0x80000000}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_decimal res = {{1, 0, 0, 0}};
  ck_assert_int_eq(s21_add(x, y, &z), 0);
  compare(z, res);
}
END_TEST

START_TEST(s21_add_145) {  // 0 0
  s21_decimal x = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x001C0000}};
  s21_decimal y = {{0x000003E9, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_decimal res = {{0xF7B22D0E, 0x9FFFAB98, 0x20999D2A, 0x00190000}};
  ck_assert_int_eq(s21_add(x, y, &z), 0);
  compare(z, res);
}
END_TEST

START_TEST(s21_add_146) {
  s21_decimal x = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal y = {{5, 0, 0, 0}};
  set_power(&y, 1);
  s21_decimal z = {{0, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_add(x, y, &z), 1);
  compare(z, res);
}
END_TEST

Suite* test_s21_add() {
  Suite* suite = suite_create("s21_add");
  TCase* t_case = tcase_create("s21_add");

  suite_add_tcase(suite, t_case);
  tcase_add_test(t_case, s21_add_1);
  tcase_add_test(t_case, s21_add_2);
  tcase_add_test(t_case, s21_add_3);
  tcase_add_test(t_case, s21_add_4);
  tcase_add_test(t_case, s21_add_5);
  tcase_add_test(t_case, s21_add_6);
  tcase_add_test(t_case, s21_add_7);
  tcase_add_test(t_case, s21_add_8);
  tcase_add_test(t_case, s21_add_9);
  tcase_add_test(t_case, s21_add_10);
  tcase_add_test(t_case, s21_add_11);
  tcase_add_test(t_case, s21_add_12);
  tcase_add_test(t_case, s21_add_13);
  tcase_add_test(t_case, s21_add_14);
  tcase_add_test(t_case, s21_add_15);
  tcase_add_test(t_case, s21_add_16);
  tcase_add_test(t_case, s21_add_17);
  tcase_add_test(t_case, s21_add_18);
  tcase_add_test(t_case, s21_add_19);
  tcase_add_test(t_case, s21_add_20);
  tcase_add_test(t_case, s21_add_21);
  tcase_add_test(t_case, s21_add_22);
  tcase_add_test(t_case, s21_add_23);
  tcase_add_test(t_case, s21_add_24);
  tcase_add_test(t_case, s21_add_25);
  tcase_add_test(t_case, s21_add_26);
  tcase_add_test(t_case, s21_add_27);
  tcase_add_test(t_case, s21_add_28);
  tcase_add_test(t_case, s21_add_29);
  tcase_add_test(t_case, s21_add_30);
  tcase_add_test(t_case, s21_add_31);
  tcase_add_test(t_case, s21_add_32);
  tcase_add_test(t_case, s21_add_33);
  tcase_add_test(t_case, s21_add_34);
  tcase_add_test(t_case, s21_add_35);
  tcase_add_test(t_case, s21_add_36);
  tcase_add_test(t_case, s21_add_37);
  tcase_add_test(t_case, s21_add_38);
  tcase_add_test(t_case, s21_add_39);
  tcase_add_test(t_case, s21_add_40);
  tcase_add_test(t_case, s21_add_41);
  tcase_add_test(t_case, s21_add_42);
  tcase_add_test(t_case, s21_add_43);
  tcase_add_test(t_case, s21_add_44);
  tcase_add_test(t_case, s21_add_45);
  tcase_add_test(t_case, s21_add_46);
  tcase_add_test(t_case, s21_add_47);
  tcase_add_test(t_case, s21_add_48);
  tcase_add_test(t_case, s21_add_49);
  tcase_add_test(t_case, s21_add_50);
  tcase_add_test(t_case, s21_add_51);
  tcase_add_test(t_case, s21_add_52);
  tcase_add_test(t_case, s21_add_53);
  tcase_add_test(t_case, s21_add_54);
  tcase_add_test(t_case, s21_add_55);
  tcase_add_test(t_case, s21_add_56);
  tcase_add_test(t_case, s21_add_57);
  tcase_add_test(t_case, s21_add_58);
  tcase_add_test(t_case, s21_add_59);
  tcase_add_test(t_case, s21_add_60);
  tcase_add_test(t_case, s21_add_61);
  tcase_add_test(t_case, s21_add_62);
  tcase_add_test(t_case, s21_add_63);
  tcase_add_test(t_case, s21_add_64);
  tcase_add_test(t_case, s21_add_65);
  tcase_add_test(t_case, s21_add_66);
  tcase_add_test(t_case, s21_add_67);
  tcase_add_test(t_case, s21_add_68);
  tcase_add_test(t_case, s21_add_69);
  tcase_add_test(t_case, s21_add_70);
  tcase_add_test(t_case, s21_add_71);
  tcase_add_test(t_case, s21_add_72);
  tcase_add_test(t_case, s21_add_73);
  tcase_add_test(t_case, s21_add_74);
  tcase_add_test(t_case, s21_add_75);
  tcase_add_test(t_case, s21_add_76);
  tcase_add_test(t_case, s21_add_77);
  tcase_add_test(t_case, s21_add_78);
  tcase_add_test(t_case, s21_add_79);
  tcase_add_test(t_case, s21_add_80);
  tcase_add_test(t_case, s21_add_81);
  tcase_add_test(t_case, s21_add_82);
  tcase_add_test(t_case, s21_add_83);
  tcase_add_test(t_case, s21_add_84);
  tcase_add_test(t_case, s21_add_85);
  tcase_add_test(t_case, s21_add_86);
  tcase_add_test(t_case, s21_add_87);
  tcase_add_test(t_case, s21_add_88);
  tcase_add_test(t_case, s21_add_89);
  tcase_add_test(t_case, s21_add_90);
  tcase_add_test(t_case, s21_add_91);
  tcase_add_test(t_case, s21_add_92);
  tcase_add_test(t_case, s21_add_93);
  tcase_add_test(t_case, s21_add_94);
  tcase_add_test(t_case, s21_add_95);
  tcase_add_test(t_case, s21_add_96);
  tcase_add_test(t_case, s21_add_97);
  tcase_add_test(t_case, s21_add_98);
  tcase_add_test(t_case, s21_add_99);
  tcase_add_test(t_case, s21_add_100);
  tcase_add_test(t_case, s21_add_101);
  tcase_add_test(t_case, s21_add_102);
  tcase_add_test(t_case, s21_add_103);
  tcase_add_test(t_case, s21_add_104);
  tcase_add_test(t_case, s21_add_105);
  tcase_add_test(t_case, s21_add_106);
  tcase_add_test(t_case, s21_add_107);
  tcase_add_test(t_case, s21_add_108);
  tcase_add_test(t_case, s21_add_109);
  tcase_add_test(t_case, s21_add_110);
  tcase_add_test(t_case, s21_add_111);
  tcase_add_test(t_case, s21_add_112);
  tcase_add_test(t_case, s21_add_113);
  tcase_add_test(t_case, s21_add_114);
  tcase_add_test(t_case, s21_add_115);
  tcase_add_test(t_case, s21_add_116);
  tcase_add_test(t_case, s21_add_117);
  tcase_add_test(t_case, s21_add_118);
  tcase_add_test(t_case, s21_add_119);
  tcase_add_test(t_case, s21_add_120);
  tcase_add_test(t_case, s21_add_121);
  tcase_add_test(t_case, s21_add_122);
  tcase_add_test(t_case, s21_add_123);
  tcase_add_test(t_case, s21_add_124);
  tcase_add_test(t_case, s21_add_125);
  tcase_add_test(t_case, s21_add_126);
  tcase_add_test(t_case, s21_add_127);
  tcase_add_test(t_case, s21_add_128);
  tcase_add_test(t_case, s21_add_129);
  tcase_add_test(t_case, s21_add_130);
  tcase_add_test(t_case, s21_add_131);
  tcase_add_test(t_case, s21_add_132);
  tcase_add_test(t_case, s21_add_133);
  tcase_add_test(t_case, s21_add_134);
  tcase_add_test(t_case, s21_add_135);
  tcase_add_test(t_case, s21_add_136);
  tcase_add_test(t_case, s21_add_137);
  tcase_add_test(t_case, s21_add_138);
  tcase_add_test(t_case, s21_add_139);
  tcase_add_test(t_case, s21_add_140);
  tcase_add_test(t_case, s21_add_141);
  tcase_add_test(t_case, s21_add_142);
  tcase_add_test(t_case, s21_add_143);
  tcase_add_test(t_case, s21_add_144);
  tcase_add_test(t_case, s21_add_145);
  tcase_add_test(t_case, s21_add_146);

  return suite;
}