#include "s21_test.h"

START_TEST(s21_floor_test_1) {
  s21_decimal first = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800D0000}};

  s21_decimal decimal_check = {
      {0x68497682, 0x001C25C2, 0x00000000, 0x80000000}};

  s21_decimal decimal_result = init_zero_decimal();
  ck_assert_int_eq((s21_floor(first, &decimal_result)), 0);
  compare(decimal_check, decimal_result);
}
END_TEST

START_TEST(s21_floor_test_2) {
  s21_decimal first = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};

  s21_decimal decimal_check = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};

  s21_decimal decimal_result = init_zero_decimal();
  ck_assert_int_eq((s21_floor(first, &decimal_result)), 0);
  compare(decimal_check, decimal_result);
}
END_TEST

START_TEST(s21_floor_test_3) {
  s21_decimal first = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  s21_decimal decimal_check = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  s21_decimal decimal_result = init_zero_decimal();
  ck_assert_int_eq((s21_floor(first, &decimal_result)), 0);
  compare(decimal_check, decimal_result);
}
END_TEST

START_TEST(s21_floor_test_4) {
  s21_decimal first = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};

  s21_decimal decimal_check = {
      {0x00000008, 0x00000000, 0x00000000, 0x80000000}};

  s21_decimal decimal_result = init_zero_decimal();
  ck_assert_int_eq((s21_floor(first, &decimal_result)), 0);
  compare(decimal_check, decimal_result);
}
END_TEST

START_TEST(s21_floor_test_5) {
  s21_decimal first = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x001C0000}};

  s21_decimal decimal_check = {
      {0x00000007, 0x00000000, 0x00000000, 0x00000000}};

  s21_decimal decimal_result = init_zero_decimal();
  ck_assert_int_eq((s21_floor(first, &decimal_result)), 0);
  compare(decimal_check, decimal_result);
}
END_TEST

START_TEST(s21_floor_test_6) {
  s21_decimal first = {{0xFFFFFFFC, 0xFFFFFFFF, 0xFFFFFFFF, 0x00010000}};

  s21_decimal decimal_check = {
      {0x99999999, 0x99999999, 0x19999999, 0x00000000}};

  s21_decimal decimal_result = init_zero_decimal();
  ck_assert_int_eq((s21_floor(first, &decimal_result)), 0);
  compare(decimal_check, decimal_result);
}
END_TEST

START_TEST(s21_floor_test_7) {
  s21_decimal first = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};

  s21_decimal decimal_check = {
      {0x00000000, 0x00000000, 0x00000000, 0x00000000}};

  s21_decimal decimal_result = init_zero_decimal();
  ck_assert_int_eq((s21_floor(first, &decimal_result)), 0);
  compare(decimal_check, decimal_result);
}
END_TEST

START_TEST(s21_floor_test_8) {
  s21_decimal first = {{0xCF6EE463, 0x00000001, 0x00000000, 0x000A0000}};

  s21_decimal decimal_check = {
      {0x00000000, 0x00000000, 0x00000000, 0x00000000}};

  s21_decimal decimal_result = init_zero_decimal();
  ck_assert_int_eq((s21_floor(first, &decimal_result)), 0);
  compare(decimal_check, decimal_result);
}
END_TEST

START_TEST(s21_floor_test_9) {
  s21_decimal first = {{0xCF6EE463, 0xCF6EE463, 0xCF6EE463, 0xCF6EE463}};

  s21_decimal decimal_result = init_zero_decimal();
  ck_assert_int_eq((s21_floor(first, &decimal_result)), 1);
}
END_TEST

START_TEST(s21_floor_test_10) {
  s21_decimal input = {{0, 0, 0, init_sign_and_scale(0, 15)}};
  s21_decimal expected = {{0, 0, 0, init_sign_and_scale(0, 0)}};
  s21_decimal result = init_zero_decimal();
  s21_floor(input, &result);
  compare(result, expected);
}
END_TEST

START_TEST(s21_floor_test_11) {
  s21_decimal input = {{362732873, 0, 0, init_sign_and_scale(1, 0)}};
  s21_decimal expected = {{362732873, 0, 0, init_sign_and_scale(1, 0)}};
  s21_decimal result = init_zero_decimal();
  s21_floor(input, &result);
  compare(result, expected);
}
END_TEST

START_TEST(s21_floor_test_12) {
  s21_decimal input = {{572963473, 0, 0, init_sign_and_scale(0, 4)}};
  s21_decimal expected = {{57296, 0, 0, init_sign_and_scale(0, 0)}};
  s21_decimal result = init_zero_decimal();
  s21_floor(input, &result);
  compare(result, expected);
}
END_TEST

START_TEST(s21_floor_test_13) {
  s21_decimal input = {{0xb54ac285, 0x9bde85, 0, init_sign_and_scale(1, 8)}};
  s21_decimal expected = {{0x1a268849, 0, 0, init_sign_and_scale(1, 0)}};
  s21_decimal result = init_zero_decimal();
  s21_floor(input, &result);
  compare(result, expected);
}
END_TEST

START_TEST(s21_floor_test_14) {
  s21_decimal input = {{0x4C577A00, 0xC0D845D, 0, init_sign_and_scale(0, 8)}};
  s21_decimal expected = {{0x5A9F2BA, 0x2, 0, init_sign_and_scale(0, 0)}};
  s21_decimal result = init_zero_decimal();
  s21_floor(input, &result);
  compare(result, expected);
}
END_TEST

START_TEST(s21_floor_test_15) {
  s21_decimal input = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, init_sign_and_scale(1, 28)}};
  s21_decimal expected = {{8, 0, 0, init_sign_and_scale(1, 0)}};
  s21_decimal result = init_zero_decimal();
  s21_floor(input, &result);
  compare(result, expected);
}
END_TEST

START_TEST(s21_floor_test_16) {
  s21_decimal val = {{2, 0, 0, 0}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_floor(val, &res));
}
END_TEST

Suite *test_s21_floor() {
  Suite *suite = suite_create("s21_floor");
  TCase *t_case = tcase_create("s21_floor");

  suite_add_tcase(suite, t_case);
  tcase_add_test(t_case, s21_floor_test_1);
  tcase_add_test(t_case, s21_floor_test_2);
  tcase_add_test(t_case, s21_floor_test_3);
  tcase_add_test(t_case, s21_floor_test_4);
  tcase_add_test(t_case, s21_floor_test_5);
  tcase_add_test(t_case, s21_floor_test_6);
  tcase_add_test(t_case, s21_floor_test_7);
  tcase_add_test(t_case, s21_floor_test_8);
  tcase_add_test(t_case, s21_floor_test_9);
  tcase_add_test(t_case, s21_floor_test_10);
  tcase_add_test(t_case, s21_floor_test_11);
  tcase_add_test(t_case, s21_floor_test_12);
  tcase_add_test(t_case, s21_floor_test_13);
  tcase_add_test(t_case, s21_floor_test_14);
  tcase_add_test(t_case, s21_floor_test_15);
  tcase_add_test(t_case, s21_floor_test_16);

  return suite;
}