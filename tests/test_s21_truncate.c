#include "s21_test.h"

START_TEST(s21_truncate_1) {
  s21_decimal decimal = {{1535, 0, 0, 0b00000000000000100000000000000000}};
  s21_decimal check = {{15, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal res = init_zero_decimal();
  int err = s21_truncate(decimal, &res);
  ck_assert_int_eq(0, err);
  compare(res, check);
}
END_TEST

START_TEST(s21_truncate_2) {
  s21_decimal decimal = {{1535, 0, 0, 0b00000000000000110000000000000000}};
  s21_decimal check = {{1, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal res = init_zero_decimal();
  int err = s21_truncate(decimal, &res);
  ck_assert_int_eq(0, err);
  compare(res, check);
}
END_TEST

START_TEST(s21_truncate_3) {
  s21_decimal decimal = {
      {UINT_MAX, 155, 0, 0b00000000000010010000000000000000}};
  s21_decimal check = {{670, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal res = init_zero_decimal();
  int err = s21_truncate(decimal, &res);
  ck_assert_int_eq(0, err);
  compare(res, check);
}
END_TEST

START_TEST(s21_truncate_4) {
  s21_decimal decimal = {
      {0xFFFFFFFF, 15, 0, 0b00000000001111110000000000000000}};
  s21_decimal res = init_zero_decimal();
  int err = s21_truncate(decimal, &res);
  ck_assert_int_eq(1, err);
}
END_TEST

START_TEST(s21_truncate_5) {
  // 7922816251426433759354395033.5
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 7922816251426433759354395033
  s21_decimal decimal_check = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  s21_decimal res = init_zero_decimal();
  int err = s21_truncate(decimal, &res);
  compare(res, decimal_check);
  ck_assert_int_eq(0, err);
}

START_TEST(s21_truncate_6) {
  // -7922816251426433759354395033.5
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -7922816251426433759354395033
  s21_decimal decimal_check = {
      {0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  s21_decimal res = init_zero_decimal();
  int err = s21_truncate(decimal, &res);
  compare(res, decimal_check);
  ck_assert_int_eq(0, err);
}

START_TEST(s21_truncate_7) {
  // 792281625142643375935439503.35
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x20000}};
  // 792281625142643375935439503
  s21_decimal decimal_check = {{0x28F5C28F, 0xF5C28F5C, 0x28F5C28, 0x0}};
  s21_decimal res = init_zero_decimal();
  int err = s21_truncate(decimal, &res);
  compare(res, decimal_check);
  ck_assert_int_eq(0, err);
}

START_TEST(s21_truncate_8) {
  // -792281625142643375935439503.35
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80020000}};
  // -792281625142643375935439503
  s21_decimal decimal_check = {{0x28F5C28F, 0xF5C28F5C, 0x28F5C28, 0x80000000}};
  s21_decimal res = init_zero_decimal();
  int err = s21_truncate(decimal, &res);
  compare(res, decimal_check);
  ck_assert_int_eq(0, err);
}

Suite *test_s21_truncate() {
  Suite *suite = suite_create("s21_truncate");
  TCase *t_case = tcase_create("s21_truncate");

  suite_add_tcase(suite, t_case);
  tcase_add_test(t_case, s21_truncate_1);
  tcase_add_test(t_case, s21_truncate_2);
  tcase_add_test(t_case, s21_truncate_3);
  tcase_add_test(t_case, s21_truncate_4);
  tcase_add_test(t_case, s21_truncate_5);
  tcase_add_test(t_case, s21_truncate_6);
  tcase_add_test(t_case, s21_truncate_7);
  tcase_add_test(t_case, s21_truncate_8);

  return suite;
}
