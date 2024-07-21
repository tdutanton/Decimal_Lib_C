#include "s21_test.h"

START_TEST(mutual_1) {
  s21_decimal a = {{0, 0, 0, 0}};
  s21_decimal b = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less(a, b), 0);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_greater(a, b), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_equal(a, b), 1);
  ck_assert_int_eq(s21_is_not_equal(a, b), 0);
}
END_TEST

START_TEST(mutual_2) {
  s21_decimal a = {{123, 123, 123, 0}};
  s21_decimal b = {{123, 123, 123, 0}};
  ck_assert_int_eq(s21_is_less(a, b), 0);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_greater(a, b), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_equal(a, b), 1);
  ck_assert_int_eq(s21_is_not_equal(a, b), 0);
}
END_TEST

START_TEST(mutual_3) {
  s21_decimal a = {{123, 0, 0, 0}};
  s21_decimal b = {{123, 0, 0, -2147483648}};
  ck_assert_int_eq(s21_is_less(a, b), 0);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 0);
  ck_assert_int_eq(s21_is_greater(a, b), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_equal(a, b), 0);
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST

START_TEST(mutual_4) {
  s21_decimal a = {{0xffffffff, 0xffffffff, 0, 1835008}};
  s21_decimal b = {{0xffffffff, 0xfffffffe, 0, 1835008}};
  ck_assert_int_eq(s21_is_less(a, b), 0);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 0);
  ck_assert_int_eq(s21_is_greater(a, b), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_equal(a, b), 0);
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST

START_TEST(mutual_5) {
  s21_decimal a = {{0xffffffff, 0xffffffff, 0xffffffff, 65536}};
  s21_decimal b = {{0xffffffff, 0xffffffff, 0xffffffff, 196608}};
  ck_assert_int_eq(s21_is_less(a, b), 0);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 0);
  ck_assert_int_eq(s21_is_greater(a, b), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_equal(a, b), 0);
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST

START_TEST(mutual_6) {
  s21_decimal a = {{0xffffffff, 0xffffffff, 0xffffffff, 65536}};
  s21_decimal b = {{0xffffffff, 0xffffffff, 0xffffffff, 196608}};
  ck_assert_int_eq(s21_is_less(a, b), 0);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 0);
  ck_assert_int_eq(s21_is_greater(a, b), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_equal(a, b), 0);
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST

START_TEST(mutual_7) {
  s21_decimal a = {{0x99999999, 0xfefefefe, 0xffffffff, -2147483648}};
  s21_decimal b = {{0x99999999, 0xfefefefe, 0xffffffee, -2147483648}};
  ck_assert_int_eq(s21_is_less(a, b), 1);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_greater(a, b), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 0);
  ck_assert_int_eq(s21_is_equal(a, b), 0);
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST

START_TEST(mutual_8) {
  s21_decimal a = {{12345600, 0, 0, 196608}};
  s21_decimal b = {{123456, 0, 0, 65536}};
  ck_assert_int_eq(s21_is_less(a, b), 0);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_greater(a, b), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_equal(a, b), 1);
  ck_assert_int_eq(s21_is_not_equal(a, b), 0);
}
END_TEST

START_TEST(mutual_9) {
  s21_decimal a = {{12345678, 0, 0, 0}};
  s21_decimal b = {{123456781, 0, 0, 65536}};
  ck_assert_int_eq(s21_is_less(a, b), 1);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_greater(a, b), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 0);
  ck_assert_int_eq(s21_is_equal(a, b), 0);
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST

START_TEST(mutual_10) {
  s21_decimal a = {{0, 0, 0, 0}};
  s21_decimal b = {{0, 0, 0, -2147483648}};
  ck_assert_int_eq(s21_is_less(a, b), 0);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_greater(a, b), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_equal(a, b), 1);
  ck_assert_int_eq(s21_is_not_equal(a, b), 0);
}
END_TEST

START_TEST(mutual_11) {
  float zero = 0.0, val = zero;
  s21_decimal dec_1, dec_2;
  s21_from_float_to_decimal(val, &dec_1);
  ck_assert_float_eq(val, 0.0);
  dec_2 = dec_1;
  float res;
  s21_from_decimal_to_float(dec_2, &res);
  ck_assert_float_eq(val, res);
}
END_TEST

START_TEST(mutual_12) {
  float val = 792281625142643.3;
  s21_decimal dec_1, dec_2;
  s21_from_float_to_decimal(val, &dec_1);
  dec_2 = dec_1;
  float res;
  s21_from_decimal_to_float(dec_2, &res);
  ck_assert_float_eq(val, res);
}
END_TEST

START_TEST(mutual_13) {
  float val = -792281625142643.3;
  s21_decimal dec_1, dec_2;
  s21_from_float_to_decimal(val, &dec_1);
  dec_2 = dec_1;
  float res;
  s21_from_decimal_to_float(dec_2, &res);
  ck_assert_float_eq(val, res);
}
END_TEST

START_TEST(mutual_14) {
  float val = 0.7922816251426433, res;
  s21_decimal dec_1, dec_2;
  s21_from_float_to_decimal(val, &dec_1);
  dec_2 = dec_1;
  s21_from_decimal_to_float(dec_2, &res);
  ck_assert_float_eq(val, res);
}
END_TEST

START_TEST(mutual_15) {
  float val = -0.7922816251426433, res;
  s21_decimal dec_1, dec_2;
  s21_from_float_to_decimal(val, &dec_1);
  dec_2 = dec_1;
  s21_from_decimal_to_float(dec_2, &res);
  ck_assert_float_eq(val, res);
}
END_TEST

START_TEST(mutual_16) {
  float val = 0.0000000000000001, res;
  s21_decimal dec_1, dec_2;
  s21_from_float_to_decimal(val, &dec_1);
  dec_2 = dec_1;
  s21_from_decimal_to_float(dec_2, &res);
  ck_assert_float_eq(val, res);
}
END_TEST

START_TEST(mutual_17) {
  float val = 10000000000000000.0, res;
  s21_decimal dec_1, dec_2;
  s21_from_float_to_decimal(val, &dec_1);
  dec_2 = dec_1;
  s21_from_decimal_to_float(dec_2, &res);
  ck_assert_float_eq(val, res);
}
END_TEST

START_TEST(mutual_18) {
  s21_decimal val = {{7, 7, 7, 0}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_truncate(val, &res));
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  float need = 129127208515966861312.0;
  ck_assert_float_eq(need, fres);
}
END_TEST

START_TEST(mutual_19) {
  s21_decimal val = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_truncate(val, &res));
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  float need = -2.0;
  ck_assert_float_eq(need, fres);
}
END_TEST

START_TEST(mutual_20) {
  s21_decimal val = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_truncate(val, &res));
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  float need = -2.0;
  ck_assert_float_eq(need, fres);
}
END_TEST

START_TEST(mutual_21) {
  s21_decimal val = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {0};
  set_power(&val, 5);
  ck_assert_int_eq(0, s21_truncate(val, &res));
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  float need = -0.0;
  ck_assert_float_eq(need, fres);
}

START_TEST(mutual_22) {
  s21_decimal val = {{128, 0, 0, 0}};
  s21_decimal res = {0};
  set_power(&val, 1);
  ck_assert_int_eq(0, s21_truncate(val, &res));
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  float need = 12;
  ck_assert_float_eq(need, fres);
}

START_TEST(mutual_23) {
  s21_decimal val = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {0};
  s21_floor(val, &res);
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  ck_assert_float_eq(-2, fres);
}
END_TEST

START_TEST(mutual_24) {
  s21_decimal val = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {0};
  set_power(&val, 5);
  s21_floor(val, &res);
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  ck_assert_float_eq(-1, fres);
}
END_TEST

START_TEST(mutual_25) {
  s21_decimal val = {{2, 0, 0, 0}};
  s21_decimal res = {0};
  set_power(&val, 5);
  s21_floor(val, &res);
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  ck_assert_float_eq(0, fres);
}
END_TEST

START_TEST(mutual_26) {
  s21_decimal val = {{7, 7, 7, 0}};
  s21_decimal res = {0};
  s21_round(val, &res);
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  float need = 129127208515966861312.0;
  ck_assert_float_eq(need, fres);
}
END_TEST

START_TEST(mutual_27) {
  s21_decimal val = {{128, 0, 0, 0}};
  s21_decimal res = {0};
  set_power(&val, 1);
  s21_round(val, &res);
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  float need = 13;
  ck_assert_float_eq(need, fres);
}
END_TEST

START_TEST(mutual_28) {
  s21_decimal res_dec = init_zero_decimal();
  s21_decimal a = init_zero_decimal();
  s21_decimal b = init_zero_decimal();
  float fnum1 = 7.25;
  float fnum2 = 9.5;
  float res_origin = 16.75;
  s21_from_float_to_decimal(fnum1, &a);
  s21_from_float_to_decimal(fnum2, &b);
  float res_float = 0.0;
  s21_add(a, b, &res_dec);
  s21_from_decimal_to_float(res_dec, &res_float);
  ck_assert_float_eq(res_float, res_origin);
}
END_TEST

Suite *tests_mutual() {
  Suite *suite = suite_create("mutual");
  TCase *t_case = tcase_create("mutual");

  suite_add_tcase(suite, t_case);
  tcase_add_test(t_case, mutual_1);
  tcase_add_test(t_case, mutual_2);
  tcase_add_test(t_case, mutual_3);
  tcase_add_test(t_case, mutual_4);
  tcase_add_test(t_case, mutual_5);
  tcase_add_test(t_case, mutual_6);
  tcase_add_test(t_case, mutual_7);
  tcase_add_test(t_case, mutual_8);
  tcase_add_test(t_case, mutual_9);
  tcase_add_test(t_case, mutual_10);
  tcase_add_test(t_case, mutual_11);
  tcase_add_test(t_case, mutual_12);
  tcase_add_test(t_case, mutual_13);
  tcase_add_test(t_case, mutual_14);
  tcase_add_test(t_case, mutual_15);
  tcase_add_test(t_case, mutual_16);
  tcase_add_test(t_case, mutual_17);
  tcase_add_test(t_case, mutual_18);
  tcase_add_test(t_case, mutual_19);
  tcase_add_test(t_case, mutual_20);
  tcase_add_test(t_case, mutual_21);
  tcase_add_test(t_case, mutual_22);
  tcase_add_test(t_case, mutual_23);
  tcase_add_test(t_case, mutual_24);
  tcase_add_test(t_case, mutual_25);
  tcase_add_test(t_case, mutual_26);
  tcase_add_test(t_case, mutual_27);
  tcase_add_test(t_case, mutual_28);

  return suite;
}