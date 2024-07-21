#include "s21_test.h"

START_TEST(s21_is_greater_or_equal_1) {
  s21_decimal first = {
      {0b00000000000000000000000000111111, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};
  s21_decimal second = {
      {0b00000000000000000000000000000111, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};
  compare_result check = CMP_TRUE;
  int res = s21_is_greater_or_equal(first, second);
  ck_assert_int_eq(check, res);
}
END_TEST

START_TEST(s21_is_greater_or_equal_2) {
  s21_decimal first = {
      {0b00000000000000000000000000000011, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};
  s21_decimal second = {
      {0b00000000000000000000000000000011, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};
  compare_result check = CMP_TRUE;
  int res = s21_is_greater_or_equal(first, second);
  ck_assert_int_eq(check, res);
}
END_TEST

START_TEST(s21_is_greater_or_equal_3) {
  s21_decimal first = {
      {0b00000000000000000000000000001111, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};
  s21_decimal second = {
      {0b00000000000000000000000001111111, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};
  compare_result check = CMP_FALSE;
  int res = s21_is_greater_or_equal(first, second);
  ck_assert_int_eq(check, res);
}
END_TEST

START_TEST(s21_is_greater_or_equal_4) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_greater_or_equal_5) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 255;
  val2.bits[0] = 256;
  ck_assert_int_eq(0, s21_is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_greater_or_equal_6) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 256;
  val2.bits[0] = 256;
  ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_greater_or_equal_7) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 257;
  val2.bits[0] = 256;
  ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_greater_or_equal_8) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  set_bit_in_decimal(&val1, 127, 1);
  ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_greater_or_equal_9) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 257;
  val2.bits[0] = 257;
  val1.bits[2] = 256;
  val2.bits[2] = 257;
  set_power(&val1, 11);
  set_power(&val2, 10);
  ck_assert_int_eq(0, s21_is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_greater_or_equal_10) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 257;
  val2.bits[0] = 257;
  val1.bits[2] = 256;
  val2.bits[2] = 257;
  set_power(&val1, 10);
  set_power(&val2, 11);
  ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_greater_or_equal_11) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val2.bits[2] = 257;
  set_bit_in_decimal(&val1, 127, 1);
  set_bit_in_decimal(&val2, 127, 1);
  ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
}
END_TEST

Suite *test_s21_is_greater_or_equal() {
  Suite *suite = suite_create("s21_is_greater_or_equal");
  TCase *t_case = tcase_create("s21_is_greater_or_equal");

  suite_add_tcase(suite, t_case);
  tcase_add_test(t_case, s21_is_greater_or_equal_1);
  tcase_add_test(t_case, s21_is_greater_or_equal_2);
  tcase_add_test(t_case, s21_is_greater_or_equal_3);
  tcase_add_test(t_case, s21_is_greater_or_equal_4);
  tcase_add_test(t_case, s21_is_greater_or_equal_5);
  tcase_add_test(t_case, s21_is_greater_or_equal_6);
  tcase_add_test(t_case, s21_is_greater_or_equal_7);
  tcase_add_test(t_case, s21_is_greater_or_equal_8);
  tcase_add_test(t_case, s21_is_greater_or_equal_9);
  tcase_add_test(t_case, s21_is_greater_or_equal_10);
  tcase_add_test(t_case, s21_is_greater_or_equal_11);

  return suite;
}