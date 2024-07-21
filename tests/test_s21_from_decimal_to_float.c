#include "s21_test.h"

START_TEST(s21_from_decimal_to_float_1) {
  s21_decimal decimal = {{1351546, 0, 0, 0b00000000000001110000000000000000}};
  float res = 0;
  float check = 0.135155;
  int err = s21_from_decimal_to_float(decimal, &res);
  ck_assert_float_eq_tol(res, check, 10e-6);
  ck_assert_int_eq(0, err);
}
END_TEST

START_TEST(s21_from_decimal_to_float_2) {
  s21_decimal decimal = {{1351546, 25, 0, 0b00000000000000110000000000000000}};
  float res = 0;
  float check = 107375536.000000;
  int err = s21_from_decimal_to_float(decimal, &res);
  ck_assert_float_eq_tol(res, check, 10e-6);
  ck_assert_int_eq(0, err);
}
END_TEST

START_TEST(s21_from_decimal_to_float_3) {
  s21_decimal dec_1 = {{123456, 0, 0, 196608}};
  float res;
  s21_from_decimal_to_float(dec_1, &res);
  ck_assert_float_eq(res, 123.456);
}
END_TEST

START_TEST(s21_from_decimal_to_float_4) {
  s21_decimal dec_1 = {{12345678, 0, 0, -2147155968}};
  float res;
  s21_from_decimal_to_float(dec_1, &res);
  ck_assert_float_eq(res, -123.45678);
}
END_TEST

START_TEST(s21_from_decimal_to_float_5) {
  s21_decimal dec_1 = {{1, 0, 0, -2147418112}};
  float res;
  s21_from_decimal_to_float(dec_1, &res);
  ck_assert_float_eq(res, -0.1);
}
END_TEST

START_TEST(s21_from_decimal_to_float_6) {
  s21_decimal val = {{123456789, 0, 0, 0}};
  set_power(&val, 5);
  float res = 1234.56789;
  float tmp = 0.;
  float *dst = &tmp;
  s21_from_decimal_to_float(val, dst);
  ck_assert_float_eq(*dst, res);
}
END_TEST

START_TEST(s21_from_decimal_to_float_7) {
  s21_decimal val = {{123456789, 0, 0, 0}};
  set_bit_in_decimal(&val, 127, 1);
  set_power(&val, 5);
  float res = -1234.56789;
  float tmp = 0.;
  float *dst = &tmp;
  s21_from_decimal_to_float(val, dst);
  ck_assert_float_eq(*dst, res);
}
END_TEST

START_TEST(s21_from_decimal_to_float_8) {
  s21_decimal val = {{123456789, 0, 0, 0}};
  set_power(&val, 5);
  float res = 1234.56789;
  float tmp = 0.;
  float *dst = &tmp;
  s21_from_decimal_to_float(val, dst);
  ck_assert_float_eq(*dst, res);
}
END_TEST

START_TEST(s21_from_decimal_to_float_9) {
  s21_decimal val = {{123456789, 0, 0, 0}};
  set_sign(&val, 1);
  set_power(&val, 5);
  float res = -1234.56789;
  float tmp = 0.;
  float *dst = &tmp;
  s21_from_decimal_to_float(val, dst);
  ck_assert_float_eq(*dst, res);
}
END_TEST

START_TEST(s21_from_decimal_to_float_10) {
  s21_decimal val = {{0, 0, 0, 0}};
  float res = 0.0;
  float tmp = 0.0;
  float *dst = &tmp;
  s21_from_decimal_to_float(val, dst);
  ck_assert_float_eq(*dst, res);
}
END_TEST

Suite *test_s21_from_decimal_to_float() {
  Suite *suite = suite_create("s21_from_decimal_to_float");
  TCase *t_case = tcase_create("s21_from_decimal_to_float");

  suite_add_tcase(suite, t_case);
  tcase_add_test(t_case, s21_from_decimal_to_float_1);
  tcase_add_test(t_case, s21_from_decimal_to_float_2);
  tcase_add_test(t_case, s21_from_decimal_to_float_3);
  tcase_add_test(t_case, s21_from_decimal_to_float_4);
  tcase_add_test(t_case, s21_from_decimal_to_float_5);
  tcase_add_test(t_case, s21_from_decimal_to_float_6);
  tcase_add_test(t_case, s21_from_decimal_to_float_7);
  tcase_add_test(t_case, s21_from_decimal_to_float_8);
  tcase_add_test(t_case, s21_from_decimal_to_float_9);
  tcase_add_test(t_case, s21_from_decimal_to_float_10);

  return suite;
}
