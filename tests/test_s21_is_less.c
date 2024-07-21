#include "s21_test.h"

START_TEST(s21_is_less_1) {
  s21_decimal first = {
      {0b00000000000000000000000000000011, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};
  s21_decimal second = {
      {0b00000000000000000000000000000011, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};
  compare_result check = CMP_FALSE;
  int res = s21_is_less(first, second);
  ck_assert_int_eq(check, res);
}
END_TEST

START_TEST(s21_is_less_2) {
  s21_decimal first = {
      {0b00000000000000000000000000000111, 0b11100000000000000000000000000000,
       0b11000000000000000000000000000000, 0b00000000000000000000000000000000}};
  s21_decimal second = {
      {0b00000000000000000000000000011111, 0b11100000000000000000000000000000,
       0b11000000000000000000000000000000, 0b00000000000000000000000000000000}};
  compare_result check = CMP_TRUE;
  int res = s21_is_less(first, second);
  ck_assert_int_eq(check, res);
}
END_TEST

START_TEST(s21_is_less_3) {
  s21_decimal first = {{133, 45, 12, 0b00000000000000000000000000000000}};
  s21_decimal second = {{133, 45, 12, 0b00000000000000000000000000000000}};
  compare_result check = CMP_FALSE;
  int res = s21_is_less(first, second);
  ck_assert_int_eq(check, res);
}
END_TEST

START_TEST(s21_is_less_4) {
  s21_decimal first = {{133, 13, 12, 0b00000000000000000000000000000000}};
  s21_decimal second = {{133, 45, 12, 0b00000000000000000000000000000000}};
  compare_result check = CMP_TRUE;
  int res = s21_is_less(first, second);
  ck_assert_int_eq(check, res);
}
END_TEST

START_TEST(s21_is_less_5) {
  s21_decimal first = {{133, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal second = {{134, 0, 0, 0b10000000000000000000000000000000}};
  compare_result check = CMP_TRUE;
  int res = s21_is_less(second, first);
  ck_assert_int_eq(check, res);
}
END_TEST

START_TEST(s21_is_less_6) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(s21_is_less_7) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 255;
  val2.bits[0] = 256;
  ck_assert_int_eq(1, s21_is_less(val1, val2));
}
END_TEST

START_TEST(s21_is_less_8) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 256;
  val2.bits[0] = 256;
  ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(s21_is_less_9) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 257;
  val2.bits[0] = 256;
  ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(s21_is_less_10) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  set_bit_in_decimal(&val1, 127, 1);
  ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(s21_is_less_11) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 257;
  val2.bits[0] = 257;
  val1.bits[2] = 256;
  val2.bits[2] = 257;
  set_power(&val1, 11);
  set_power(&val2, 10);
  ck_assert_int_eq(1, s21_is_less(val1, val2));
}
END_TEST

START_TEST(s21_is_less_12) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 257;
  val2.bits[0] = 257;
  val1.bits[2] = 256;
  val2.bits[2] = 257;
  set_power(&val1, 10);
  set_power(&val2, 11);
  ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(s21_is_less_13) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val2.bits[2] = 257;
  set_bit_in_decimal(&val1, 127, 1);
  set_bit_in_decimal(&val2, 127, 1);
  ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(s21_is_less_14) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  set_bit_in_decimal(&val1, 127, 1);
  set_bit_in_decimal(&val2, 127, 1);
  set_bit_in_decimal(&val1, 83, 1);
  set_power(&val1, 12);
  set_power(&val2, 11);
  ck_assert_int_eq(1, s21_is_less(val1, val2));
}
END_TEST

START_TEST(s21_is_less_15) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  set_bit_in_decimal(&val1, 127, 1);
  set_bit_in_decimal(&val2, 127, 1);
  set_bit_in_decimal(&val1, 83, 1);
  set_bit_in_decimal(&val2, 83, 1);
  set_power(&val1, 10);
  set_power(&val2, 11);
  ck_assert_int_eq(1, s21_is_less(val1, val2));
}
END_TEST

START_TEST(s21_is_less_16) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  set_bit_in_decimal(&val1, 127, 1);
  set_bit_in_decimal(&val2, 127, 1);
  set_bit_in_decimal(&val1, 83, 1);
  set_power(&val1, 10);
  set_power(&val2, 10);
  ck_assert_int_eq(1, s21_is_less(val1, val2));
}
END_TEST

START_TEST(s21_is_less_17) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  set_bit_in_decimal(&val1, 127, 1);
  set_bit_in_decimal(&val2, 127, 0);
  set_bit_in_decimal(&val1, 83, 1);
  ck_assert_int_eq(1, s21_is_less(val1, val2));
}
END_TEST

START_TEST(s21_is_less_18) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  set_bit_in_decimal(&val1, 127, 1);
  set_bit_in_decimal(&val2, 127, 0);
  ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(s21_is_less_19) {
  s21_decimal small = {{1}};
  set_sign(&small, 1);
  s21_decimal big_small = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  set_sign(&big_small, 1);
  ck_assert_int_eq(s21_is_less(big_small, small), 1);
}

Suite *test_s21_is_less() {
  Suite *suite = suite_create("s21_is_less");
  TCase *t_case = tcase_create("s21_is_less");

  suite_add_tcase(suite, t_case);
  tcase_add_test(t_case, s21_is_less_1);
  tcase_add_test(t_case, s21_is_less_2);
  tcase_add_test(t_case, s21_is_less_3);
  tcase_add_test(t_case, s21_is_less_4);
  tcase_add_test(t_case, s21_is_less_5);
  tcase_add_test(t_case, s21_is_less_6);
  tcase_add_test(t_case, s21_is_less_7);
  tcase_add_test(t_case, s21_is_less_8);
  tcase_add_test(t_case, s21_is_less_9);
  tcase_add_test(t_case, s21_is_less_10);
  tcase_add_test(t_case, s21_is_less_11);
  tcase_add_test(t_case, s21_is_less_12);
  tcase_add_test(t_case, s21_is_less_13);
  tcase_add_test(t_case, s21_is_less_14);
  tcase_add_test(t_case, s21_is_less_15);
  tcase_add_test(t_case, s21_is_less_16);
  tcase_add_test(t_case, s21_is_less_17);
  tcase_add_test(t_case, s21_is_less_18);
  tcase_add_test(t_case, s21_is_less_19);

  return suite;
}