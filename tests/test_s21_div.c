#include "s21_test.h"

START_TEST(s21_div_test_1) {
  s21_decimal first = {
      {0b10001011000101000111101100001111, 0b00000000110000100010000110110000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};

  s21_decimal second = {
      {0b00000000000000000000000000000101, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};

  s21_decimal decimal_check = {
      {0b10110101011010100111111100000011, 0b00000000001001101101001110001001,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};

  s21_decimal decimal_result = init_zero_decimal();
  ck_assert_int_eq((s21_div(first, second, &decimal_result)), 0);
  compare(decimal_check, decimal_result);
}
END_TEST

START_TEST(s21_div_test_2) {
  s21_decimal first = {
      {0b11010000100000000000000111110100, 0b00001101111001110110011001110110,
       0b00000000000000000110100111100001, 0b00000000000000000000000000000000}};

  s21_decimal second = {
      {0b11110110100000000000000001100100, 0b00000010110001111110000101001010,
       0b00000000000000000001010100101101, 0b00000000000000000000000000000000}};

  s21_decimal decimal_check = {
      {0b00000000000000000000000000000101, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};

  s21_decimal decimal_result = init_zero_decimal();
  ck_assert_int_eq((s21_div(first, second, &decimal_result)), 0);
  compare(decimal_check, decimal_result);
}
END_TEST

START_TEST(s21_div_test_3) {
  s21_decimal first = {
      {0b11010000100000000000000111110100, 0b00001101111001110110011001110110,
       0b00000000000000000110100111100001, 0b00000000000000000000000000000000}};

  s21_decimal second = {
      {0b11010000100000000000000111110100, 0b00001101111001110110011001110110,
       0b00000000000000000110100111100001, 0b00000000000000000000000000000000}};

  s21_decimal decimal_check = {
      {0b00000000000000000000000000000001, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};

  s21_decimal decimal_result = init_zero_decimal();
  ck_assert_int_eq((s21_div(first, second, &decimal_result)), 0);
  compare(decimal_check, decimal_result);
}
END_TEST

START_TEST(s21_div_test_4) {
  s21_decimal first = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal second = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x80000000}};
  s21_decimal decimal_result = init_zero_decimal();
  ck_assert_int_eq((s21_div(first, second, &decimal_result)), 0);
  compare(decimal_check, decimal_result);
}
END_TEST

START_TEST(s21_div_test_5) {
  s21_decimal first = {
      {0b11010000100000000000000111110100, 0b00001101111001110110011001110110,
       0b00000000000000000110100111100001, 0b00000000000000000000000000000000}};

  s21_decimal second = {
      {0b00000000000000000000000000000000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};

  s21_decimal decimal_result = init_zero_decimal();
  ck_assert_int_eq((s21_div(first, second, &decimal_result)), 3);
}
END_TEST

START_TEST(s21_div_test_6) {
  s21_decimal first = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  s21_decimal second = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal decimal_check = {
      {0x00000001, 0x00000000, 0x00000000, 0x80000000}};
  s21_decimal decimal_result = init_zero_decimal();
  ck_assert_int_eq((s21_div(first, second, &decimal_result)), 0);
  compare(decimal_check, decimal_result);
}
END_TEST

START_TEST(s21_div_test_7) {
  s21_decimal first = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x001C0000}};
  s21_decimal second = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal decimal_check = {
      {0x00000001, 0x00000000, 0x00000000, 0x801C0000}};
  s21_decimal decimal_result = init_zero_decimal();
  ck_assert_int_eq((s21_div(first, second, &decimal_result)), 0);
  compare(decimal_check, decimal_result);
}
END_TEST

// 4294967295 / 0 = NaN
START_TEST(s21_div_test_8) {
  s21_decimal input1 = {{0xFFFFFFFF, 0, 0, init_sign_and_scale(0, 2)}};
  s21_decimal input2 = {{0, 0, 0, init_sign_and_scale(1, 23)}};
  s21_decimal result = init_zero_decimal();
  int status = s21_div(input1, input2, &result);
  ck_assert_int_eq(status, 3);
}
END_TEST

// 0.0000 / 7.5 = 0
START_TEST(s21_div_test_9) {
  s21_decimal input1 = {{0, 0, 0, 0b10000000000001000000000000000000}};
  s21_decimal input2 = {{75, 0, 0, init_sign_and_scale(0, 1)}};
  s21_decimal result = init_zero_decimal();
  int status = s21_div(input1, input2, &result);
  ck_assert_int_eq(status, 0);
}
END_TEST

// 2.25 / -1.5 = -1.5
START_TEST(s21_div_test_10) {
  s21_decimal input1 = {{225, 0, 0, init_sign_and_scale(0, 2)}};
  s21_decimal input2 = {{15, 0, 0, init_sign_and_scale(1, 1)}};
  s21_decimal expected = {{15, 0, 0, init_sign_and_scale(1, 1)}};
  s21_decimal result = init_zero_decimal();
  int status = s21_div(input1, input2, &result);
  ck_assert_int_eq(status, 0);
  compare(result, expected);
}
END_TEST

// 2 / 3 = 0.6666666666666666666666666667
START_TEST(s21_div_test_11) {
  s21_decimal input1 = {{2, 0, 0, init_sign_and_scale(0, 0)}};
  s21_decimal input2 = {{3, 0, 0, init_sign_and_scale(0, 0)}};
  s21_decimal expected = {
      {0xaaaaaab, 0x296e0196, 0x158a8994, init_sign_and_scale(0, 28)}};
  s21_decimal result = init_zero_decimal();
  int status = s21_div(input1, input2, &result);
  ck_assert_int_eq(status, 0);
  compare(result, expected);
}
END_TEST

// 1e-28 / 5 = 0
START_TEST(s21_div_test_12) {
  s21_decimal input1 = {{1, 0, 0, init_sign_and_scale(0, 28)}};
  s21_decimal input2 = {{5, 0, 0, init_sign_and_scale(0, 0)}};
  s21_decimal expected = {{0}};
  s21_decimal result = init_zero_decimal();
  int status = s21_div(input1, input2, &result);
  ck_assert_int_eq(status, 0);
  compare(result, expected);
}
END_TEST

// 20 / 1e-5 = 400000
START_TEST(s21_div_test_13) {
  s21_decimal input1 = {{20, 0, 0, init_sign_and_scale(0, 0)}};
  s21_decimal input2 = {{5, 0, 0, init_sign_and_scale(0, 5)}};
  s21_decimal expected = {{400000}};
  s21_decimal result = init_zero_decimal();
  int status = s21_div(input1, input2, &result);
  ck_assert_int_eq(status, 0);
  compare(result, expected);
}
END_TEST

// 4449249363747.434387 / 43764 = 101664595.64362111294671419431
START_TEST(s21_div_test_14) {
  s21_decimal input1 = {{0x234C6F93, 0x3DBEE8B9, 0, init_sign_and_scale(0, 6)}};
  s21_decimal input2 = {{0xAAF4, 0, 0, init_sign_and_scale(0, 0)}};
  s21_decimal expected = {
      {0x373BF827, 0x4ef17458, 0x20d97f8d, init_sign_and_scale(0, 20)}};
  s21_decimal result = init_zero_decimal();
  int status = s21_div(input1, input2, &result);
  ck_assert_int_eq(status, 0);
  compare(result, expected);
}
END_TEST

// -936582642837 / 0.1041747302401649 = 8990497414083.03230156190427
START_TEST(s21_div_test_15) {
  s21_decimal input1 = {{0x10ACFC95, 0xDA, 0, init_sign_and_scale(1, 0)}};
  s21_decimal input2 = {{0xB1E7C671, 0x3B376, 0, init_sign_and_scale(0, 16)}};
  s21_decimal expected = {
      {0x662EB2DB, 0x23EF54FF, 0x2E7AD30, init_sign_and_scale(1, 14)}};
  s21_decimal result = init_zero_decimal();
  int status = s21_div(input1, input2, &result);
  ck_assert_int_eq(status, 0);
  compare(result, expected);
}
END_TEST

// -0.3183718237812378127 / -0.3183718237812378127 = 1
START_TEST(s21_div_test_16) {
  s21_decimal input1 = {
      {0x85BD4A0F, 0x2c2ed6de, 0, init_sign_and_scale(1, 19)}};
  s21_decimal input2 = {
      {0x85BD4A0F, 0x2c2ed6de, 0, init_sign_and_scale(1, 19)}};
  s21_decimal expected = {{1}};
  s21_decimal result = init_zero_decimal();
  int status = s21_div(input1, input2, &result);
  ck_assert_int_eq(status, 0);
  compare(result, expected);
}
END_TEST

// 948347948.43877834 / 1e+16 = 9.4834794843877834e-11
START_TEST(s21_div_test_17) {
  s21_decimal input1 = {{0x530431CA, 0x150EBBE, 0, init_sign_and_scale(1, 8)}};
  s21_decimal input2 = {{0x89E80000, 0x8AC72304}};
  s21_decimal expected = {
      {0x530431CA, 0x150EBBE, 0, init_sign_and_scale(1, 27)}};
  s21_decimal result = {{0}};
  int status = s21_div(input1, input2, &result);
  ck_assert_int_eq(status, 0);
  compare(result, expected);
}
END_TEST

// -184838746726726348023 / 0.00000000193289 = -INF
START_TEST(s21_div_test_18) {
  s21_decimal input1 = {
      {0x8EEBACF7, 0x52724D4, 0xA, init_sign_and_scale(1, 0)}};
  s21_decimal input2 = {{0x2F309, 0, 0, init_sign_and_scale(0, 14)}};
  s21_decimal result = init_zero_decimal();
  int status = s21_div(input1, input2, &result);
  ck_assert_int_eq(status, 2);
}
END_TEST

// 45284674874386437639m / 0.00000000048934 = INF
START_TEST(s21_div_test_19) {
  s21_decimal input1 = {
      {0xA8DC5607, 0x4737BDEA, 0x27, init_sign_and_scale(0, 0)}};
  s21_decimal input2 = {{0x2F309, 0, 0, init_sign_and_scale(0, 14)}};
  s21_decimal result = init_zero_decimal();
  int status = s21_div(input1, input2, &result);
  ck_assert_int_eq(status, 1);
}
END_TEST

// 75384834.34934734873487 / 1349.34984 = 55867.52383603302516037649658
START_TEST(s21_div_test_20) {
  s21_decimal input1 = {
      {0xE36AE38F, 0xA9793779, 0x198, init_sign_and_scale(0, 14)}};
  s21_decimal input2 = {{0x80AF1C8, 0, 0, init_sign_and_scale(0, 5)}};
  s21_decimal expected = {
      {0x972204FA, 0x9272C199, 0x120D40D5, init_sign_and_scale(0, 23)}};
  s21_decimal result = init_zero_decimal();
  int status = s21_div(input1, input2, &result);
  ck_assert_int_eq(status, 0);
  compare(result, expected);
}
END_TEST

// 7.9228162514264337593543950335 / 0.5 = 15.845632502852867518708790067
START_TEST(s21_div_test_21) {
  s21_decimal input1 = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, init_sign_and_scale(0, 28)}};
  s21_decimal input2 = {{5, 0, 0, init_sign_and_scale(0, 1)}};
  s21_decimal expected = {
      {0x33333333, 0x33333333, 0x33333333, init_sign_and_scale(0, 27)}};
  s21_decimal result = init_zero_decimal();
  int status = s21_div(input1, input2, &result);
  ck_assert_int_eq(status, 0);
  compare(result, expected);
}
END_TEST

// 7922816251426433759354395033.5 / 0.01 = INF
START_TEST(s21_div_test_22) {
  s21_decimal input1 = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, init_sign_and_scale(0, 1)}};
  s21_decimal input2 = {{1, 0, 0, init_sign_and_scale(0, 2)}};
  s21_decimal result = init_zero_decimal();
  int status = s21_div(input1, input2, &result);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(s21_div_test_23) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(s21_div_test_24) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(s21_div_test_25) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(s21_div_test_26) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(3, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(s21_div_test_27) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(3, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(s21_div_test_28) {
  s21_decimal first = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x001C0000}};
  s21_decimal second = {{0x038E5290, 0x00000000, 0x00000000, 0x00080000}};
  s21_decimal decimal_check = {
      {0x93FE82E1, 0xB9C22731, 0x2AE91E27, 0x001B0000}};
  s21_decimal decimal_result = init_zero_decimal();
  ck_assert_int_eq((s21_div(first, second, &decimal_result)), 0);
  compare(decimal_check, decimal_result);
}
END_TEST

START_TEST(s21_div_test_29) {
  s21_decimal first = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x08000000}};
  s21_decimal second = {{0x00000254, 0x00000000, 0x00000000, 0x00030000}};
  s21_decimal decimal_result = init_zero_decimal();
  ck_assert_int_eq((s21_div(first, second, &decimal_result)), 1);
}
END_TEST

START_TEST(s21_div_test_30) {
  // 1.2640938749860586450804312205
  s21_decimal decimal1 = {{0x1888888D, 0xBE250261, 0x28D856E6, 0x1C0000}};
  // 2
  s21_decimal decimal2 = {{0x2, 0x0, 0x0, 0x0}};
  // 0.6320469374930293225402156102
  s21_decimal check = {{0x8C444446, 0x5F128130, 0x146C2B73, 0x1C0000}};
  s21_decimal result = init_zero_decimal();
  int code = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(code, 0);
  compare(check, result);
}
END_TEST

START_TEST(s21_div_test_31) {
  // 2
  s21_decimal decimal1 = {{0x2, 0x0, 0x0, 0x0}};
  // 1.2640938749860586450804312205
  s21_decimal decimal2 = {{0x1888888D, 0xBE250261, 0x28D856E6, 0x1C0000}};
  // 1.5821609767882606564463392905
  s21_decimal check = {{0x8B80B889, 0x20B8279E, 0x331F5430, 0x1C0000}};
  s21_decimal result = init_zero_decimal();
  int code = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(code, 0);
  compare(check, result);
}
END_TEST

START_TEST(s21_div_test_32) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // 500
  s21_decimal decimal2 = {{0x1F4, 0x0, 0x0, 0x0}};
  // 0.002
  s21_decimal check = {{0x2, 0x0, 0x0, 0x30000}};

  s21_decimal result = init_zero_decimal();
  int code = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(code, 0);
  compare(check, result);
}
END_TEST

START_TEST(s21_div_test_33) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // 10000000000000000000000000000
  s21_decimal check = {{0x10000000, 0x3E250261, 0x204FCE5E, 0x0}};

  s21_decimal result = init_zero_decimal();
  int code = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(code, 0);
  compare(check, result);
}
END_TEST

START_TEST(s21_div_test_34) {
  // 7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.0000000000000000000000000001
  s21_decimal check = {{0x1, 0x0, 0x0, 0x1C0000}};

  s21_decimal result = init_zero_decimal();
  int code = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(code, 0);
  compare(check, result);
}
END_TEST

START_TEST(s21_div_test_35) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -3
  s21_decimal check = {{0x3, 0x0, 0x0, 0x80000000}};

  s21_decimal result = init_zero_decimal();
  int code = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(code, 0);
  compare(check, result);
}
END_TEST

START_TEST(s21_div_test_36) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // 156064767525876035022225408
  s21_decimal decimal2 = {{0x0, 0x0, 0x811800, 0x0}};
  // -169.22068909868474138626644073
  s21_decimal check = {{0x8C085869, 0xC05E68BD, 0x36AD9B79, 0x801A0000}};

  s21_decimal result = init_zero_decimal();
  int code = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(code, 0);
  compare(check, result);
}
END_TEST

START_TEST(s21_div_test_37) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // -79228162514264337593543950327
  s21_decimal check = {{0xFFFFFFF7, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  s21_decimal result = init_zero_decimal();
  int code = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(code, 0);
  compare(check, result);
}
END_TEST

START_TEST(s21_div_test_38) {
  // 1.2640938749860586450804312207
  s21_decimal decimal1 = {{0x1888888F, 0xBE250261, 0x28D856E6, 0x1C0000}};
  // 2.0000000000000000000000000000
  s21_decimal decimal2 = {{0x20000000, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // 0.6320469374930293225402156104
  s21_decimal check = {{0x8C444448, 0x5F128130, 0x146C2B73, 0x1C0000}};

  s21_decimal result = init_zero_decimal();
  int code = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(code, 0);
  compare(check, result);
}
END_TEST

START_TEST(s21_div_test_39) {
  // 3.6336660283201536
  s21_decimal decimal1 = {{0x811800, 0x811800, 0x0, 0x100000}};
  // 0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // 36336660283201536000000000000
  s21_decimal check = {{0x89800000, 0xFEE8FB1C, 0x7568FB1C, 0x0}};

  s21_decimal result = init_zero_decimal();
  int code = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(code, 0);
  compare(check, result);
}
END_TEST

START_TEST(s21_div_test_40) {
  // 7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // 0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // 79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  s21_decimal result = init_zero_decimal();
  int code = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(code, 0);
  compare(check, result);
}
END_TEST

START_TEST(s21_div_test_41) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x80000000}};
  // division by zero
  s21_decimal result = init_zero_decimal();
  int code = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(code, DIV_BY_ZERO);
}
END_TEST

START_TEST(s21_div_test_42) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // overflow
  s21_decimal result = init_zero_decimal();
  int code = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(code, TOO_BIG);
}
END_TEST

START_TEST(s21_div_test_43) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x801C0000}};
  // overflow
  s21_decimal result = init_zero_decimal();
  int code = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(code, TOO_SMALL);
}
END_TEST

START_TEST(s21_div_test_44) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal result = init_zero_decimal();
  int code = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(code, OK);
  compare(decimal_check, result);
}
END_TEST

START_TEST(s21_div_test_45) {
  // 0.0000000074505801528346182749
  s21_decimal decimal1 = {{0xCAD4845D, 0x9F9C7BD, 0x4, 0x1C0000}};
  // 1152921504606846976
  s21_decimal decimal2 = {{0x0, 0x10000000, 0x0, 0x0}};
  // 0.0000000000000000000000000065
  s21_decimal decimal_check = {{0x41, 0x0, 0x0, 0x1C0000}};

  s21_decimal result = init_zero_decimal();
  int code = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(code, 0);
  compare(decimal_check, result);
}
END_TEST

START_TEST(s21_div_test_46) {
  // 0.0000000000000000000020971522
  s21_decimal decimal1 = {{0x1400002, 0x0, 0x0, 0x1C0000}};
  // 8388608
  s21_decimal decimal2 = {{0x800000, 0x0, 0x0, 0x0}};
  // 0.0000000000000000000000000003
  s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x1C0000}};
  s21_decimal result = init_zero_decimal();
  int code = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(code, 0);
  compare(decimal_check, result);
}
END_TEST

START_TEST(s21_div_test_47) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // 39614081257132168796771975168
  s21_decimal decimal2 = {{0x0, 0x0, 0x80000000, 0x0}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal result = init_zero_decimal();
  int code = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(code, OK);
  compare(decimal_check, result);
}
END_TEST

START_TEST(s21_div_test_48) {
  // 79228162514264337593543950320
  s21_decimal decimal1 = {{0xFFFFFFF0, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.9999999999999999999999999998
  s21_decimal decimal2 = {{0xFFFFFFE, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // overflow
  s21_decimal result = init_zero_decimal();
  int code = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(code, TOO_BIG);
}
END_TEST

START_TEST(s21_div_test_49) {
  // -79228162514264337593543950320
  s21_decimal decimal1 = {{0xFFFFFFF0, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0.9999999999999999999999999998
  s21_decimal decimal2 = {{0xFFFFFFE, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // overflow
  s21_decimal result = init_zero_decimal();
  int code = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(code, TOO_SMALL);
}
END_TEST

START_TEST(s21_div_test_50) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

  s21_decimal result = init_zero_decimal();
  int code = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(code, OK);
  compare(decimal_check, result);
}
END_TEST

START_TEST(s21_div_test_51) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -10
  s21_decimal decimal_check = {{0xA, 0x0, 0x0, 0x80000000}};
  s21_decimal result = init_zero_decimal();
  int code = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(code, OK);
  compare(decimal_check, result);
}
END_TEST

START_TEST(s21_div_test_52) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

  s21_decimal result = init_zero_decimal();
  int code = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(code, OK);
  compare(decimal_check, result);
}
START_TEST(s21_div_test_53) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -39614081257132168798919458816
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x80000000, 0x80000000}};
  // -1.9999999999999999998915797827
  s21_decimal decimal_check = {
      {0xDF606343, 0x7C4A04C1, 0x409F9CBC, 0x801C0000}};

  s21_decimal result = init_zero_decimal();
  int code = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(code, OK);
  compare(decimal_check, result);
}
END_TEST

START_TEST(s21_div_test_54) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 3.9614081257132168796771975168
  s21_decimal decimal2 = {{0x0, 0x0, 0x80000000, 0x1C0000}};
  // 20000000000000000000000000000
  s21_decimal decimal_check = {{0x20000000, 0x7C4A04C2, 0x409F9CBC, 0x0}};

  s21_decimal result = init_zero_decimal();
  int code = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(code, OK);
  compare(decimal_check, result);
}
END_TEST

START_TEST(s21_div_test_55) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // 39614081257132168796771977148
  s21_decimal decimal_check = {{0x7BC, 0x0, 0x80000000, 0x0}};

  s21_decimal result = init_zero_decimal();
  int code = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(code, OK);
  compare(decimal_check, result);
}
END_TEST

START_TEST(s21_div_test_56) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.0000000000000000000000000008
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x1C0000}};
  // overflow
  s21_decimal result = init_zero_decimal();
  int code = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(code, TOO_BIG);
}
END_TEST

START_TEST(s21_div_test_57) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x801C0000}};
  // overflow
  s21_decimal result = init_zero_decimal();
  int code = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(code, TOO_SMALL);
}
END_TEST

START_TEST(s21_div_test_58) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.9999999999999999999999999999
  s21_decimal decimal2 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // overflow
  s21_decimal result = init_zero_decimal();
  int code = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(code, TOO_BIG);
}
END_TEST

START_TEST(s21_div_test_59) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
  // overflow
  s21_decimal result = init_zero_decimal();
  int code = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(code, TOO_SMALL);
}

START_TEST(s21_div_test_60) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
  // division by zero
  s21_decimal result = init_zero_decimal();
  int code = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(code, DIV_BY_ZERO);
}
END_TEST

START_TEST(s21_div_test_61) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -10
  s21_decimal decimal_check = {{0xA, 0x0, 0x0, 0x80000000}};

  s21_decimal result = init_zero_decimal();
  int code = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(code, OK);
  compare(decimal_check, result);
}
END_TEST

START_TEST(s21_div_test_62) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 3.9614081257132168796771975168
  s21_decimal decimal2 = {{0x0, 0x0, 0x80000000, 0x1C0000}};
  // -20000000000000000000000000000
  s21_decimal decimal_check = {
      {0x20000000, 0x7C4A04C2, 0x409F9CBC, 0x80000000}};

  s21_decimal result = init_zero_decimal();
  int code = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(code, OK);
  compare(decimal_check, result);
}
END_TEST

START_TEST(s21_div_test_63) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // -79228162514264337593543950327
  s21_decimal decimal_check = {
      {0xFFFFFFF7, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  s21_decimal result = init_zero_decimal();
  int code = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(code, OK);
  compare(decimal_check, result);
}
END_TEST

START_TEST(s21_div_test_64) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0.0000000000000000000000000008
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x801C0000}};
  // overflow
  s21_decimal result = init_zero_decimal();
  int code = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(code, TOO_BIG);
}
END_TEST

START_TEST(s21_div_test_65) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // overflow
  s21_decimal result = init_zero_decimal();
  int code = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(code, TOO_SMALL);
}
END_TEST

START_TEST(s21_div_test_66) {
  // 5
  s21_decimal decimal1 = {{0x00000005, 0x00000000, 0x00000000, 0x00000000}};
  // 11
  s21_decimal decimal2 = {{0x0000000B, 0x00000000, 0x00000000, 0x00000000}};
  // 0,4545454545454545454545454545
  s21_decimal decimal_check = {
      {0x4D1745D1, 0xA7E246E6, 0x0EAFE970, 0x001C0000}};

  s21_decimal result = init_zero_decimal();
  int code = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(code, OK);
  compare(decimal_check, result);
}
END_TEST

START_TEST(s21_div_test_67) {
  // 471
  s21_decimal decimal1 = {{0x000001D7, 0x00000000, 0x00000000, 0x00000000}};
  // 900
  s21_decimal decimal2 = {{0x00000384, 0x00000000, 0x00000000, 0x00000000}};
  // 0,5233333333333333333333333333
  s21_decimal decimal_check = {
      {0xF1555555, 0x778FF471, 0x10E8E970, 0x001C0000}};

  s21_decimal result = init_zero_decimal();
  int code = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(code, OK);
  compare(decimal_check, result);
}
END_TEST

START_TEST(s21_div_test_68) {
  // 1
  s21_decimal decimal1 = {{0x00000001, 0x00000000, 0x00000000, 0x00000000}};
  // 9
  s21_decimal decimal2 = {{0x00000009, 0x00000000, 0x00000000, 0x00000000}};
  //  0,111111111111111111111111111
  s21_decimal decimal_check = {
      {0x571C71C7, 0x06E7AAEE, 0x039716EE, 0x001C0000}};

  s21_decimal result = init_zero_decimal();
  int code = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(code, OK);
  compare(decimal_check, result);
}
END_TEST

START_TEST(s21_div_test_69) {
  // 16
  s21_decimal decimal1 = {{0x00000010, 0x00000000, 0x00000000, 0x00000000}};
  // 18
  s21_decimal decimal2 = {{0x00000012, 0x00000000, 0x00000000, 0x00000000}};
  //  0,8888888888888888888888888889
  s21_decimal decimal_check = {
      {0xB8E38E39, 0x373D5772, 0x1CB8B770, 0x001C0000}};

  s21_decimal result = init_zero_decimal();
  int code = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(code, OK);
  compare(decimal_check, result);
}
END_TEST

START_TEST(s21_div_test_70) {
  // -0.0000000000000000000000000008
  s21_decimal decimal1 = {{0x8, 0x0, 0x0, 0x801C0000}};
  // 0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
  // division by zero
  s21_decimal result = init_zero_decimal();
  int code = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(code, DIV_BY_ZERO);
}

Suite *test_s21_div() {
  Suite *suite = suite_create("s21_div");
  TCase *t_case = tcase_create("s21_div");

  suite_add_tcase(suite, t_case);
  tcase_add_test(t_case, s21_div_test_1);
  tcase_add_test(t_case, s21_div_test_2);
  tcase_add_test(t_case, s21_div_test_3);
  tcase_add_test(t_case, s21_div_test_4);
  tcase_add_test(t_case, s21_div_test_5);
  tcase_add_test(t_case, s21_div_test_6);
  tcase_add_test(t_case, s21_div_test_7);
  tcase_add_test(t_case, s21_div_test_8);
  tcase_add_test(t_case, s21_div_test_9);
  tcase_add_test(t_case, s21_div_test_10);
  tcase_add_test(t_case, s21_div_test_11);
  tcase_add_test(t_case, s21_div_test_12);
  tcase_add_test(t_case, s21_div_test_13);
  tcase_add_test(t_case, s21_div_test_14);
  tcase_add_test(t_case, s21_div_test_15);
  tcase_add_test(t_case, s21_div_test_16);
  tcase_add_test(t_case, s21_div_test_17);
  tcase_add_test(t_case, s21_div_test_18);
  tcase_add_test(t_case, s21_div_test_19);
  tcase_add_test(t_case, s21_div_test_20);
  tcase_add_test(t_case, s21_div_test_21);
  tcase_add_test(t_case, s21_div_test_22);
  tcase_add_test(t_case, s21_div_test_23);
  tcase_add_test(t_case, s21_div_test_24);
  tcase_add_test(t_case, s21_div_test_25);
  tcase_add_test(t_case, s21_div_test_26);
  tcase_add_test(t_case, s21_div_test_27);
  tcase_add_test(t_case, s21_div_test_28);
  tcase_add_test(t_case, s21_div_test_29);
  tcase_add_test(t_case, s21_div_test_30);
  tcase_add_test(t_case, s21_div_test_31);
  tcase_add_test(t_case, s21_div_test_32);
  tcase_add_test(t_case, s21_div_test_33);
  tcase_add_test(t_case, s21_div_test_34);
  tcase_add_test(t_case, s21_div_test_35);
  tcase_add_test(t_case, s21_div_test_36);
  tcase_add_test(t_case, s21_div_test_37);
  tcase_add_test(t_case, s21_div_test_38);
  tcase_add_test(t_case, s21_div_test_39);
  tcase_add_test(t_case, s21_div_test_40);
  tcase_add_test(t_case, s21_div_test_41);
  tcase_add_test(t_case, s21_div_test_42);
  tcase_add_test(t_case, s21_div_test_43);
  tcase_add_test(t_case, s21_div_test_44);
  tcase_add_test(t_case, s21_div_test_45);
  tcase_add_test(t_case, s21_div_test_46);
  tcase_add_test(t_case, s21_div_test_47);
  tcase_add_test(t_case, s21_div_test_48);
  tcase_add_test(t_case, s21_div_test_49);
  tcase_add_test(t_case, s21_div_test_50);
  tcase_add_test(t_case, s21_div_test_51);
  tcase_add_test(t_case, s21_div_test_52);
  tcase_add_test(t_case, s21_div_test_53);
  tcase_add_test(t_case, s21_div_test_54);
  tcase_add_test(t_case, s21_div_test_55);
  tcase_add_test(t_case, s21_div_test_56);
  tcase_add_test(t_case, s21_div_test_57);
  tcase_add_test(t_case, s21_div_test_58);
  tcase_add_test(t_case, s21_div_test_59);
  tcase_add_test(t_case, s21_div_test_60);
  tcase_add_test(t_case, s21_div_test_61);
  tcase_add_test(t_case, s21_div_test_62);
  tcase_add_test(t_case, s21_div_test_63);
  tcase_add_test(t_case, s21_div_test_64);
  tcase_add_test(t_case, s21_div_test_65);
  tcase_add_test(t_case, s21_div_test_66);
  tcase_add_test(t_case, s21_div_test_67);
  tcase_add_test(t_case, s21_div_test_68);
  tcase_add_test(t_case, s21_div_test_69);
  tcase_add_test(t_case, s21_div_test_70);
  return suite;
}