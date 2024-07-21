#include "s21_test.h"

START_TEST(s21_is_not_equal_1) {
  s21_decimal first = {
      {0b00000000000000000000000000000011, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};
  s21_decimal second = {
      {0b00000000000000000000000000000011, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};
  compare_result check = CMP_FALSE;
  int res = s21_is_not_equal(first, second);
  ck_assert_int_eq(check, res);
}
END_TEST

START_TEST(s21_is_not_equal_2) {
  s21_decimal first = {
      {0b00000000000000000000000000000111, 0b11100000000000000000000000000000,
       0b11000000000000000000000000000000, 0b00000000000000000000000000000000}};
  s21_decimal second = {
      {0b00000000000000000000000000000011, 0b11100000000000000000000000000000,
       0b11000000000000000000000000000000, 0b00000000000000000000000000000000}};
  compare_result check = CMP_TRUE;
  int res = s21_is_not_equal(first, second);
  ck_assert_int_eq(check, res);
}
END_TEST

START_TEST(s21_is_not_equal_3) {
  s21_decimal first = {{133, 45, 12, 0b00000000000000000000000000000000}};
  s21_decimal second = {{133, 45, 12, 0b00000000000000000000000000000000}};
  compare_result check = CMP_FALSE;
  int res = s21_is_not_equal(first, second);
  ck_assert_int_eq(check, res);
}
END_TEST

START_TEST(s21_is_not_equal_4) {
  s21_decimal first = {{133, 46, 12, 0b00000000000000000000000000000000}};
  s21_decimal second = {{133, 45, 12, 0b00000000000000000000000000000000}};
  compare_result check = CMP_TRUE;
  int res = s21_is_not_equal(first, second);
  ck_assert_int_eq(check, res);
}
END_TEST

START_TEST(s21_is_not_equal_5) {
  s21_decimal first = {{0, 0, 0, 0b10000000000000110000000000000000}};
  s21_decimal second = {{0, 0, 0, 0b00000000000000010000000000000000}};
  compare_result check = CMP_FALSE;
  int res = s21_is_not_equal(first, second);
  ck_assert_int_eq(check, res);
}
END_TEST

START_TEST(s21_is_not_equal_6) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  set_bit_in_decimal(&val1, 127, 1);
  set_bit_in_decimal(&val2, 127, 0);
  ck_assert_int_eq(0, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_not_equal_7) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  set_bit_in_decimal(&val2, 3, 1);
  ck_assert_int_eq(1, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_not_equal_8) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  set_bit_in_decimal(&val2, 127, 1);
  set_bit_in_decimal(&val1, 33, 1);
  set_bit_in_decimal(&val2, 33, 1);
  ck_assert_int_eq(1, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_not_equal_9) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  set_bit_in_decimal(&val1, 3, 1);
  set_bit_in_decimal(&val2, 3, 1);
  ck_assert_int_eq(0, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_not_equal_10) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  set_bit_in_decimal(&val1, 3, 1);
  set_bit_in_decimal(&val2, 4, 1);
  ck_assert_int_eq(1, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_not_equal_11) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  set_power(&val1, 3);
  set_power(&val2, 3);
  ck_assert_int_eq(0, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_not_equal_12) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  set_bit_in_decimal(&val1, 3, 1);
  set_bit_in_decimal(&val2, 4, 1);
  set_power(&val1, 3);
  set_power(&val2, 3);
  ck_assert_int_eq(1, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_not_equal_13) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  set_power(&val1, 3);
  set_power(&val2, 2);
  ck_assert_int_eq(0, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_not_equal_14) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  ck_assert_int_eq(0, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_not_equal_15) {
  s21_decimal a = {{0, 0, 0, 0}};
  s21_decimal b = {{0, 1, 0, 0}};
  set_sign(&b, 1);
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST

START_TEST(s21_is_not_equal_16) {
  s21_decimal a = {{0, 0, 0, 0}};
  s21_decimal b = {{0, 0, 0, 0}};
  set_sign(&b, 1);

  ck_assert_int_eq(s21_is_not_equal(a, b), 0);
}
END_TEST

Suite *test_s21_is_not_equal() {
  Suite *suite = suite_create("s21_is_not_equal");
  TCase *t_case = tcase_create("s21_is_not_equal");

  suite_add_tcase(suite, t_case);
  tcase_add_test(t_case, s21_is_not_equal_1);
  tcase_add_test(t_case, s21_is_not_equal_2);
  tcase_add_test(t_case, s21_is_not_equal_3);
  tcase_add_test(t_case, s21_is_not_equal_4);
  tcase_add_test(t_case, s21_is_not_equal_5);
  tcase_add_test(t_case, s21_is_not_equal_6);
  tcase_add_test(t_case, s21_is_not_equal_7);
  tcase_add_test(t_case, s21_is_not_equal_8);
  tcase_add_test(t_case, s21_is_not_equal_9);
  tcase_add_test(t_case, s21_is_not_equal_10);
  tcase_add_test(t_case, s21_is_not_equal_11);
  tcase_add_test(t_case, s21_is_not_equal_12);
  tcase_add_test(t_case, s21_is_not_equal_13);
  tcase_add_test(t_case, s21_is_not_equal_14);
  tcase_add_test(t_case, s21_is_not_equal_15);
  tcase_add_test(t_case, s21_is_not_equal_16);

  return suite;
}