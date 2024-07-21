#include "s21_test.h"

START_TEST(s21_from_float_to_decimal_1) {
  float value1 = 3.14f;
  s21_decimal decimal_result;
  s21_decimal decimal_check = {
      {0x0000013A, 0x00000000, 0x00000000, 0x00020000}};
  ck_assert_int_eq((s21_from_float_to_decimal(value1, &decimal_result)), 0);
  compare(decimal_check, decimal_result);
}
END_TEST

START_TEST(s21_from_float_to_decimal_2) {
  float value1 = -6544635622.8484f;
  s21_decimal decimal_result;
  s21_decimal decimal_check = {
      {0x86173478, 0x00000001, 0x00000000, 0x80000000}};
  ck_assert_int_eq((s21_from_float_to_decimal(value1, &decimal_result)), 0);
  compare(decimal_check, decimal_result);
}
END_TEST

START_TEST(s21_from_float_to_decimal_3) {
  float value1 = -0.46356228484f;
  s21_decimal decimal_result;
  s21_decimal decimal_check = {
      {0x0046BBE7, 0x00000000, 0x00000000, 0x80070000}};
  ck_assert_int_eq((s21_from_float_to_decimal(value1, &decimal_result)), 0);
  compare(decimal_check, decimal_result);
}
END_TEST

START_TEST(s21_from_float_to_decimal_4) {
  float value1 = INFINITY;
  s21_decimal decimal_result;
  ck_assert_int_eq((s21_from_float_to_decimal(value1, &decimal_result)), 1);
}
END_TEST

START_TEST(s21_from_float_to_decimal_5) {
  float value1 = -INFINITY;
  s21_decimal decimal_result;
  ck_assert_int_eq((s21_from_float_to_decimal(value1, &decimal_result)), 1);
}
END_TEST

START_TEST(s21_from_float_to_decimal_6) {
  float value1 = NAN;
  s21_decimal decimal_result;
  ck_assert_int_eq((s21_from_float_to_decimal(value1, &decimal_result)), 1);
}
END_TEST

START_TEST(s21_from_float_to_decimal_7) {
  float value1 = 79228157791897854723898736640.0f;
  s21_decimal decimal_result;
  s21_decimal decimal_check = {
      {0x20000000, 0xB392B21A, 0xFFFFFF77, 0x00000000}};
  ck_assert_int_eq((s21_from_float_to_decimal(value1, &decimal_result)), 0);
  compare(decimal_check, decimal_result);
}
END_TEST

START_TEST(s21_from_float_to_decimal_8) {
  float value1 =
      0.00000000000000000000000000010000000031710768509710513471352647538147514756461109f;
  s21_decimal decimal_result;
  s21_decimal decimal_check = {
      {0x00000001, 0x00000000, 0x00000000, 0x001C0000}};
  ck_assert_int_eq((s21_from_float_to_decimal(value1, &decimal_result)), 0);
  compare(decimal_check, decimal_result);
}
END_TEST

START_TEST(s21_from_float_to_decimal_9) {
  float value1 = 55.4e+30f;
  s21_decimal decimal_result;
  ck_assert_int_eq((s21_from_float_to_decimal(value1, &decimal_result)), 1);
}
END_TEST

START_TEST(s21_from_float_to_decimal_10) {
  float value1 = 17.541224e-32f;
  s21_decimal decimal_result;
  ck_assert_int_eq((s21_from_float_to_decimal(value1, &decimal_result)), 1);
}
END_TEST

START_TEST(s21_from_float_to_decimal_11) {
  float zero = 0.0, val = (0 / zero);
  s21_decimal dec_1;
  int res = s21_from_float_to_decimal(val, &dec_1);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(s21_from_float_to_decimal_12) {
  float zero = 0.0, val = (1.0 / zero);
  s21_decimal dec_1;
  int res = s21_from_float_to_decimal(val, &dec_1);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(s21_from_float_to_decimal_13) {
  float val = 1e-29;
  s21_decimal dec_1;
  int res = s21_from_float_to_decimal(val, &dec_1);
  ck_assert_int_eq(res, 1);
  ck_assert_int_eq(dec_1.bits[0], 0);
}
END_TEST

START_TEST(s21_from_float_to_decimal_14) {
  float val = 79228162514264337593543950336.0;
  s21_decimal dec_1;
  int res = s21_from_float_to_decimal(val, &dec_1);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(s21_from_float_to_decimal_15) {
  float val = -79228162514264337593543950336.0;
  s21_decimal dec_1;
  int res = s21_from_float_to_decimal(val, &dec_1);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(s21_from_float_to_decimal_16) {
  s21_decimal val = {{0, 0, 0, 0}};
  s21_decimal check = {{0x0012D688, 0x00000000, 0x00000000, 0x80030000}};
  float tmp = -1234.56789;
  int code = s21_from_float_to_decimal(tmp, &val);
  ck_assert_int_eq(code, 0);
  compare(val, check);
}
END_TEST

Suite *test_s21_from_float_to_decimal() {
  Suite *suite = suite_create("s21_from_float_to_decimal");
  TCase *t_case = tcase_create("s21_from_float_to_decimal");

  suite_add_tcase(suite, t_case);
  tcase_add_test(t_case, s21_from_float_to_decimal_1);
  tcase_add_test(t_case, s21_from_float_to_decimal_2);
  tcase_add_test(t_case, s21_from_float_to_decimal_3);
  tcase_add_test(t_case, s21_from_float_to_decimal_4);
  tcase_add_test(t_case, s21_from_float_to_decimal_5);
  tcase_add_test(t_case, s21_from_float_to_decimal_6);
  tcase_add_test(t_case, s21_from_float_to_decimal_7);
  tcase_add_test(t_case, s21_from_float_to_decimal_8);
  tcase_add_test(t_case, s21_from_float_to_decimal_9);
  tcase_add_test(t_case, s21_from_float_to_decimal_10);
  tcase_add_test(t_case, s21_from_float_to_decimal_11);
  tcase_add_test(t_case, s21_from_float_to_decimal_12);
  tcase_add_test(t_case, s21_from_float_to_decimal_13);
  tcase_add_test(t_case, s21_from_float_to_decimal_14);
  tcase_add_test(t_case, s21_from_float_to_decimal_15);
  tcase_add_test(t_case, s21_from_float_to_decimal_16);

  return suite;
}
