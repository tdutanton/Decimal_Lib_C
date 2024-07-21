#include "s21_test.h"

START_TEST(s21_round_1) {
  s21_decimal decimal = {{1535, 0, 0, 0b00000000000000100000000000000000}};
  s21_decimal check = {{15, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal res = init_zero_decimal();
  int err = s21_round(decimal, &res);
  ck_assert_int_eq(0, err);
  compare(check, res);
}
END_TEST

START_TEST(s21_round_2) {
  s21_decimal decimal = {{1535, 0, 0, 0b00000000000000110000000000000000}};
  s21_decimal check = {{2, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal res = init_zero_decimal();
  int err = s21_round(decimal, &res);
  ck_assert_int_eq(0, err);
  compare(check, res);
}
END_TEST

START_TEST(s21_round_3) {
  s21_decimal decimal = {
      {UINT_MAX, 155, 0, 0b00000000000010100000000000000000}};
  s21_decimal check = {{67, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal res = init_zero_decimal();
  int err = s21_round(decimal, &res);
  ck_assert_int_eq(0, err);
  compare(check, res);
}
END_TEST

START_TEST(s21_round_4) {
  s21_decimal decimal = {{1256, 0, 0, 0b00000000000000100000000000000000}};
  s21_decimal check = {{13, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal res = init_zero_decimal();
  int err = s21_round(decimal, &res);
  ck_assert_int_eq(0, err);
  compare(check, res);
}
END_TEST

START_TEST(s21_round_5) {
  s21_decimal decimal = {{1256, 0, 0, 0b00001100000000100000000000000000}};
  s21_decimal res = init_zero_decimal();
  int err = s21_round(decimal, &res);
  ck_assert_int_eq(1, err);
}
END_TEST

START_TEST(s21_round_6) {
  // 7922816251426433759354395033.5
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 7922816251426433759354395034
  s21_decimal decimal_check = {{0x9999999A, 0x99999999, 0x19999999, 0x0}};
  s21_decimal res = init_zero_decimal();
  int err = s21_round(decimal, &res);
  compare(res, decimal_check);
  ck_assert_int_eq(0, err);
}
END_TEST

START_TEST(s21_round_7) {
  // 7922816251426433759354.3950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x70000}};
  // 7922816251426433759354
  s21_decimal decimal_check = {
      {0xF485787A, 0x7F29ABCA, 0x000001AD, 0x00000000}};
  s21_decimal res = init_zero_decimal();
  int err = s21_round(decimal, &res);
  compare(res, decimal_check);
  ck_assert_int_eq(0, err);
}
END_TEST

START_TEST(s21_round_8) {
  // -7922816251426433759354.3950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80070000}};
  // -7922816251426433759354
  s21_decimal decimal_check = {{0xF485787A, 0x7F29ABCA, 0x1AD, 0x80000000}};
  s21_decimal res = init_zero_decimal();
  int err = s21_round(decimal, &res);
  compare(res, decimal_check);
  ck_assert_int_eq(0, err);
}
END_TEST

START_TEST(s21_round_9) {
  s21_decimal val = {{3, 3, 3, ~(UINT_MAX / 2)}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(s21_round_10) {
  s21_decimal val = {{3, 3, 3, 0}};
  s21_decimal res = {0};
  set_power(&val, 5);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(s21_round_11) {
  s21_decimal val = {{7, 7, 7, ~(UINT_MAX / 2)}};
  s21_decimal res = {0};
  set_power(&val, 5);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(s21_round_12) {
  s21_decimal val = {{25, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {0};
  set_power(&val, 1);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(s21_round_13) {
  s21_decimal val = {{26, 0, 0, 0}};
  s21_decimal res = {0};
  set_power(&val, 1);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(s21_round_14) {
  s21_decimal val = {{115, 0, 0, 0}};
  s21_decimal res = {0};
  set_power(&val, 1);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(s21_round_15) {
  s21_decimal val = {{118, 0, 0, 0}};
  s21_decimal res = {0};
  set_power(&val, 1);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(s21_round_16) {
  s21_decimal val = {{125, 0, 0, 0}};
  s21_decimal res = {0};
  set_power(&val, 1);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

Suite *test_s21_round() {
  Suite *suite = suite_create("s21_round");
  TCase *t_case = tcase_create("s21_round");

  suite_add_tcase(suite, t_case);
  tcase_add_test(t_case, s21_round_1);
  tcase_add_test(t_case, s21_round_2);
  tcase_add_test(t_case, s21_round_3);
  tcase_add_test(t_case, s21_round_4);
  tcase_add_test(t_case, s21_round_5);
  tcase_add_test(t_case, s21_round_6);
  tcase_add_test(t_case, s21_round_7);
  tcase_add_test(t_case, s21_round_8);
  tcase_add_test(t_case, s21_round_9);
  tcase_add_test(t_case, s21_round_10);
  tcase_add_test(t_case, s21_round_11);
  tcase_add_test(t_case, s21_round_12);
  tcase_add_test(t_case, s21_round_13);
  tcase_add_test(t_case, s21_round_14);
  tcase_add_test(t_case, s21_round_15);
  tcase_add_test(t_case, s21_round_16);

  return suite;
}
