#include "s21_test.h"

START_TEST(s21_from_int_to_decimal_1) {
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};
  s21_decimal decimal_result;

  s21_from_int_to_decimal(1, &decimal_result);
  compare(decimal_check, decimal_result);
}
END_TEST

START_TEST(s21_from_int_to_decimal_2) {
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};
  s21_decimal decimal_result;

  s21_from_int_to_decimal(-1, &decimal_result);
  compare(decimal_check, decimal_result);
}
END_TEST

START_TEST(s21_from_int_to_decimal_3) {
  int src = INT_MIN;
  s21_decimal expected = {{INT_MIN, 0, 0, init_sign_and_scale(1, 0)}};
  s21_decimal result = init_zero_decimal();
  int status = s21_from_int_to_decimal(src, &result);

  compare(result, expected);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(s21_from_int_to_decimal_4) {
  int src = INT_MAX;
  s21_decimal expected = {{INT_MAX, 0, 0, init_sign_and_scale(0, 0)}};
  s21_decimal result = init_zero_decimal();
  int status = s21_from_int_to_decimal(src, &result);

  compare(result, expected);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(s21_from_int_to_decimal_5) {
  int src = 0;
  s21_decimal expected = {{0}};
  s21_decimal result = init_zero_decimal();
  int status = s21_from_int_to_decimal(src, &result);

  compare(result, expected);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(s21_from_int_to_decimal_6) {
  int src = rand() % INT_MAX;
  int sign = rand() % 2;
  s21_decimal expected = {{src, 0, 0, init_sign_and_scale(sign, 0)}};
  s21_decimal result = init_zero_decimal();
  if (sign) src = -src;
  int status = s21_from_int_to_decimal(src, &result);

  compare(result, expected);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(s21_from_int_to_decimal_7) {
  s21_decimal val = {{0, 0, 0, 0}};
  int res = 0;
  int tmp = 123456789;
  s21_from_int_to_decimal(tmp, &val);
  s21_from_decimal_to_int(val, &res);
  ck_assert_int_eq(res, tmp);
}
END_TEST

START_TEST(s21_from_int_to_decimal_8) {
  s21_decimal val = {{0, 0, 0, 0}};
  int res = 0;
  int tmp = -123456789;
  s21_from_int_to_decimal(tmp, &val);
  s21_from_decimal_to_int(val, &res);
  ck_assert_int_eq(res, tmp);
}
END_TEST

Suite *test_s21_from_int_to_decimal() {
  Suite *suite = suite_create("s21_from_int_to_decimal");
  TCase *t_case = tcase_create("s21_from_int_to_decimal");

  suite_add_tcase(suite, t_case);
  tcase_add_test(t_case, s21_from_int_to_decimal_1);
  tcase_add_test(t_case, s21_from_int_to_decimal_2);
  tcase_add_test(t_case, s21_from_int_to_decimal_3);
  tcase_add_test(t_case, s21_from_int_to_decimal_4);
  tcase_add_test(t_case, s21_from_int_to_decimal_5);
  tcase_add_loop_test(t_case, s21_from_int_to_decimal_6, 0, 1000);
  tcase_add_test(t_case, s21_from_int_to_decimal_7);
  tcase_add_test(t_case, s21_from_int_to_decimal_8);

  return suite;
}
