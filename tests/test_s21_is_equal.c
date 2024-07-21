#include "s21_test.h"

START_TEST(s21_is_equal_1) {
  s21_decimal first = {
      {0b00000000000000000000000000000011, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};
  s21_decimal second = {
      {0b00000000000000000000000000000011, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};
  compare_result check = CMP_TRUE;
  int res = s21_is_equal(first, second);
  ck_assert_int_eq(check, res);
}
END_TEST

START_TEST(s21_is_equal_2) {
  s21_decimal first = {
      {0b00000000000000000000000000000011, 0b11100000000000000000000000000000,
       0b11000000000000000000000000000000, 0b00000000000000000000000000000000}};
  s21_decimal second = {
      {0b00000000000000000000000000000011, 0b11100000000000000000000000000000,
       0b11000000000000000000000000000000, 0b00000000000000000000000000000000}};
  compare_result check = CMP_TRUE;
  int res = s21_is_equal(first, second);
  ck_assert_int_eq(check, res);
}
END_TEST

START_TEST(s21_is_equal_3) {
  s21_decimal first = {{133, 45, 12, 0b00000000000000000000000000000000}};
  s21_decimal second = {{133, 45, 12, 0b00000000000000000000000000000000}};
  compare_result check = CMP_TRUE;
  int res = s21_is_equal(first, second);
  ck_assert_int_eq(check, res);
}
END_TEST

START_TEST(s21_is_equal_4) {
  s21_decimal first = {{133, 46, 12, 0b00000000000000000000000000000000}};
  s21_decimal second = {{133, 45, 12, 0b00000000000000000000000000000000}};
  compare_result check = CMP_FALSE;
  int res = s21_is_equal(first, second);
  ck_assert_int_eq(check, res);
}
END_TEST

START_TEST(s21_is_equal_5) {
  s21_decimal first = {{0, 0, 0, 0b10000000011000000000000000000000}};
  s21_decimal second = {{0, 0, 0, 0b00000000001000000000000000000000}};
  compare_result check = CMP_TRUE;
  int res = s21_is_equal(first, second);
  ck_assert_int_eq(check, res);
}
END_TEST

START_TEST(s21_is_equal_6) {
  s21_decimal first = {{130, 0, 0, 0b00000000000000010000000000000000}};
  s21_decimal second = {{13, 0, 0, 0b00000000000000000000000000000000}};
  compare_result check = CMP_TRUE;
  int res = s21_is_equal(first, second);
  ck_assert_int_eq(check, res);
}
END_TEST

START_TEST(s21_is_equal_7) {
  s21_decimal first = {{13, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal second = {{1300, 0, 0, 0b00000000000000100000000000000000}};
  compare_result check = CMP_TRUE;
  int res = s21_is_equal(first, second);
  ck_assert_int_eq(check, res);
}
END_TEST

START_TEST(s21_is_equal_8) {
  s21_decimal first = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  compare_result check = CMP_TRUE;
  int res = s21_is_equal(first, max_decimal());
  ck_assert_int_eq(check, res);
}
END_TEST

START_TEST(s21_is_equal_9) {
  s21_decimal first = {{0, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal second = {{0, 0, 0, 0b10000000000000000000000000000000}};
  compare_result check = CMP_TRUE;
  int res = s21_is_equal(first, second);
  ck_assert_int_eq(check, res);
}
END_TEST

START_TEST(s21_is_equal_10) {
  s21_decimal val1 = {{0, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  set_sign(&val2, 1);
  ck_assert_int_eq(1, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_equal_11) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  set_bit_in_decimal(&val2, 3, 1);
  ck_assert_int_eq(0, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_equal_12) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  set_bit_in_decimal(&val2, 127, 1);
  set_bit_in_decimal(&val1, 33, 1);
  set_bit_in_decimal(&val2, 33, 1);
  ck_assert_int_eq(0, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_equal_13) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  set_bit_in_decimal(&val1, 3, 1);
  set_bit_in_decimal(&val2, 3, 1);
  ck_assert_int_eq(1, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_equal_14) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  set_bit_in_decimal(&val1, 3, 1);
  set_bit_in_decimal(&val2, 4, 1);
  ck_assert_int_eq(0, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_equal_15) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  set_power(&val1, 3);
  set_power(&val2, 3);
  ck_assert_int_eq(1, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_equal_16) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  set_bit_in_decimal(&val1, 3, 1);
  set_bit_in_decimal(&val2, 4, 1);
  set_power(&val1, 3);
  set_power(&val2, 3);
  ck_assert_int_eq(0, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_equal_17) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  set_power(&val1, 3);
  set_power(&val2, 2);
  ck_assert_int_eq(1, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_equal_18) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  ck_assert_int_eq(1, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_equal_19) {
  s21_decimal a = {{1, 2, 3, 0}};
  s21_decimal b = {{1, 2, 3, 0}};

  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(s21_is_equal_20) {
  s21_decimal a = {{1, 2, 3, 0}};
  s21_decimal b = {{1, 2, 3, 0}};
  set_power(&a, 2);
  set_power(&b, 1);

  ck_assert_int_eq(s21_is_equal(a, b), 0);
}
END_TEST

START_TEST(s21_is_equal_21) {
  s21_decimal a = {{1, 2, 3, 0}};
  s21_decimal b = {{1, 2, 3, 0}};
  set_sign(&b, 1);

  ck_assert_int_eq(s21_is_equal(a, b), 0);
}
END_TEST

START_TEST(s21_is_equal_22) {
  s21_decimal a = {{3, 2, 1, 0}};
  s21_decimal b = {{3, 2, 1, 0}};
  set_sign(&b, 1);

  ck_assert_int_eq(s21_is_equal(a, b), 0);
}
END_TEST

START_TEST(s21_is_equal_23) {
  s21_decimal a = {{0, 0, 0, 0}};
  s21_decimal b = {{0, 0, 0, 0}};
  set_sign(&b, 1);

  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

Suite *test_s21_is_equal() {
  Suite *suite = suite_create("s21_is_equal");
  TCase *t_case = tcase_create("s21_is_equal");

  suite_add_tcase(suite, t_case);
  tcase_add_test(t_case, s21_is_equal_1);
  tcase_add_test(t_case, s21_is_equal_2);
  tcase_add_test(t_case, s21_is_equal_3);
  tcase_add_test(t_case, s21_is_equal_4);
  tcase_add_test(t_case, s21_is_equal_5);
  tcase_add_test(t_case, s21_is_equal_6);
  tcase_add_test(t_case, s21_is_equal_7);
  tcase_add_test(t_case, s21_is_equal_8);
  tcase_add_test(t_case, s21_is_equal_9);
  tcase_add_test(t_case, s21_is_equal_10);
  tcase_add_test(t_case, s21_is_equal_11);
  tcase_add_test(t_case, s21_is_equal_12);
  tcase_add_test(t_case, s21_is_equal_13);
  tcase_add_test(t_case, s21_is_equal_14);
  tcase_add_test(t_case, s21_is_equal_15);
  tcase_add_test(t_case, s21_is_equal_16);
  tcase_add_test(t_case, s21_is_equal_17);
  tcase_add_test(t_case, s21_is_equal_18);
  tcase_add_test(t_case, s21_is_equal_19);
  tcase_add_test(t_case, s21_is_equal_20);
  tcase_add_test(t_case, s21_is_equal_21);
  tcase_add_test(t_case, s21_is_equal_22);
  tcase_add_test(t_case, s21_is_equal_23);

  return suite;
}