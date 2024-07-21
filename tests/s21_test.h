#ifndef S21_TEST_H_
#define S21_TEST_H_

#include <check.h>
#include <stdlib.h>

#include "../s21_decimal.h"

#define EXPONENT_PLUS_1 65536
#define EXPONENT_PLUS_2 196608
#define S21_MAX_UINT 4294967295

void compare(s21_decimal check, s21_decimal res);
uint32_t init_sign_and_scale(unsigned int sign, int scale);
Suite *test_suite();

// Arithmetic tests
Suite *test_s21_add();
Suite *test_s21_sub();
Suite *test_s21_mul();
Suite *test_s21_div();

// Comparison tests
Suite *test_s21_is_less();
Suite *test_s21_is_less_or_equal();
Suite *test_s21_is_greater();
Suite *test_s21_is_greater_or_equal();
Suite *test_s21_is_equal();
Suite *test_s21_is_not_equal();

// Conversion tests
Suite *test_s21_from_int_to_decimal();
Suite *test_s21_from_float_to_decimal();
Suite *test_s21_from_decimal_to_int();
Suite *test_s21_from_decimal_to_float();

// Other tests
Suite *test_s21_floor();
Suite *test_s21_round();
Suite *test_s21_truncate();
Suite *test_s21_negate();

// Mutual tests
Suite *tests_mutual();

#endif