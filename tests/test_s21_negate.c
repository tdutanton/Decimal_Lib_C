#include "s21_test.h"

START_TEST(s21_negate_1) {
  s21_decimal first = {
      {0b00000000000000000000000000000001, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b10000000000000000000000000000000}};
  s21_decimal decimal_check = {{1, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal decimal_result = init_zero_decimal();
  s21_negate(first, &decimal_result);
  ck_assert_int_eq((s21_negate(first, &decimal_result)), 0);
  compare(decimal_check, decimal_result);
}
END_TEST

START_TEST(s21_negate_2) {
  s21_decimal first = {{10, 1545151, 0, 0b00000000000000000000000000000000}};
  s21_decimal decimal_check = {
      {10, 1545151, 0, 0b10000000000000000000000000000000}};
  s21_decimal decimal_result = init_zero_decimal();
  s21_negate(first, &decimal_result);
  ck_assert_int_eq((s21_negate(first, &decimal_result)), 0);
  compare(decimal_check, decimal_result);
}
END_TEST

START_TEST(s21_negate_3) {
  s21_decimal val = {{2, 0, 0, 0}};
  s21_decimal res = {0};
  int sign_before = get_sign(val);
  s21_negate(val, &res);
  int sign_after = get_sign(res);

  ck_assert_int_ne(sign_before, sign_after);
}
END_TEST

START_TEST(s21_negate_4) {
  s21_decimal val = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {0};
  int sign_before = get_sign(val);
  s21_negate(val, &res);
  int sign_after = get_sign(res);
  ck_assert_int_ne(sign_before, sign_after);
}
END_TEST

START_TEST(s21_negate_5) {
  s21_decimal val = {{0, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {0};
  int sign_before = get_sign(val);
  s21_negate(val, &res);
  int sign_after = get_sign(res);
  ck_assert_int_ne(sign_before, sign_after);
}
END_TEST

START_TEST(s21_negate_6) {
  s21_decimal val = {0};
  s21_decimal res = {0};
  int sign_before = get_sign(val);
  s21_negate(val, &res);
  int sign_after = get_sign(res);
  ck_assert_int_ne(sign_before, sign_after);
}
END_TEST

Suite *test_s21_negate() {
  Suite *suite = suite_create("s21_negate");
  TCase *t_case = tcase_create("s21_negate");

  suite_add_tcase(suite, t_case);
  tcase_add_test(t_case, s21_negate_1);
  tcase_add_test(t_case, s21_negate_2);
  tcase_add_test(t_case, s21_negate_3);
  tcase_add_test(t_case, s21_negate_4);
  tcase_add_test(t_case, s21_negate_5);
  tcase_add_test(t_case, s21_negate_6);

  return suite;
}