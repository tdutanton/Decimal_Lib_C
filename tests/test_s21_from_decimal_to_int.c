#include "s21_test.h"

START_TEST(s21_from_decimal_to_int_1) {
  s21_decimal decimal = {{1535, 0, 0, 0b00000000000000100000000000000000}};
  int res = 0;
  int check = 15;
  int err = s21_from_decimal_to_int(decimal, &res);
  ck_assert_int_eq(res, check);
  ck_assert_int_eq(0, err);
}
END_TEST

START_TEST(s21_from_decimal_to_int_2) {
  s21_decimal decimal = {{1351546, 0, 0, 0b00000000000001000000000000000000}};
  int res = 0;
  int check = 135;
  int err = s21_from_decimal_to_int(decimal, &res);
  ck_assert_int_eq(res, check);
  ck_assert_int_eq(0, err);
}
END_TEST

START_TEST(s21_from_decimal_to_int_3) {
  s21_decimal decimal = {
      {0xFFFFFFFF, 15, 0, 0b00000000000001110000000000000000}};
  int res = 0;
  int check = 6871;
  int err = s21_from_decimal_to_int(decimal, &res);
  ck_assert_int_eq(res, check);
  ck_assert_int_eq(0, err);
}
END_TEST

START_TEST(s21_from_decimal_to_int_4) {
  s21_decimal decimal = {
      {0xFFFFFFFF, 15, 0, 0b00000000000000010000000000000000}};
  int res = 0;
  int err = s21_from_decimal_to_int(decimal, &res);
  ck_assert_int_eq(1, err);
}
END_TEST

START_TEST(s21_from_decimal_to_int_5) {
  s21_decimal decimal = {
      {0xFFFFFFFF, 0xFFFFFFFF, 10, 0b00000000000001110000000000000000}};
  int res = 0;
  int err = s21_from_decimal_to_int(decimal, &res);
  ck_assert_int_eq(1, err);
}
END_TEST

START_TEST(s21_from_decimal_to_int_6) {
  int expected = INT_MAX, result;
  s21_decimal src = {{INT_MAX, 0, 0}};

  // add_trailing_numbers(&src, _i, 0);
  int status = s21_from_decimal_to_int(src, &result);

  ck_assert_int_eq(result, expected);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_int_7) {
  int expected = INT_MIN, result = 0;
  s21_decimal src = {{INT_MIN, 0, 0, init_sign_and_scale(1, 0)}};

  // add_trailing_numbers(&src, _i, 1);
  int status = s21_from_decimal_to_int(src, &result);

  ck_assert_int_eq(result, expected);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_int_8) {
  s21_decimal src = {{INT_MIN, 0, 0}};
  int result;
  // add_trailing_numbers(&src, _i, 0);
  int status = s21_from_decimal_to_int(src, &result);

  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(s21_from_decimal_to_int_9) {
  int sign = rand() % 2;
  int expected = rand() % (sign ? INT_MIN : INT_MAX), result;
  if (sign) expected = -expected;
  s21_decimal src = {
      {sign ? -expected : expected, 0, 0, init_sign_and_scale(sign, 0)}};

  // add_trailing_numbers(&src, rand() % 19, sign);
  int status = s21_from_decimal_to_int(src, &result);

  ck_assert_int_eq(result, expected);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_int_10) {
  s21_decimal val = {{123456789, 0, 0, 0}};
  set_power(&val, 5);
  int res = 1234;
  int tmp = 0;
  int *dst = &tmp;
  s21_from_decimal_to_int(val, dst);
  ck_assert_int_eq(*dst, res);
}
END_TEST

START_TEST(s21_from_decimal_to_int_11) {
  s21_decimal val = {{123456789, 0, 0, 0}};
  set_bit_in_decimal(&val, 127, 1);
  set_power(&val, 5);
  int res = -1234;
  int tmp = 0.;
  int *dst = &tmp;
  s21_from_decimal_to_int(val, dst);
  ck_assert_int_eq(*dst, res);
}
END_TEST

Suite *test_s21_from_decimal_to_int() {
  Suite *suite = suite_create("s21_from_decimal_to_int");
  TCase *t_case = tcase_create("s21_from_decimal_to_int");

  suite_add_tcase(suite, t_case);
  tcase_add_test(t_case, s21_from_decimal_to_int_1);
  tcase_add_test(t_case, s21_from_decimal_to_int_2);
  tcase_add_test(t_case, s21_from_decimal_to_int_3);
  tcase_add_test(t_case, s21_from_decimal_to_int_4);
  tcase_add_test(t_case, s21_from_decimal_to_int_5);
  tcase_add_test(t_case, s21_from_decimal_to_int_6);
  tcase_add_loop_test(t_case, s21_from_decimal_to_int_7, 0, 18);
  tcase_add_loop_test(t_case, s21_from_decimal_to_int_8, 0, 18);
  tcase_add_loop_test(t_case, s21_from_decimal_to_int_9, 0, 1000);
  tcase_add_test(t_case, s21_from_decimal_to_int_10);
  tcase_add_test(t_case, s21_from_decimal_to_int_11);

  return suite;
}
