#include "s21_test.h"

START_TEST(s21_mul_test_1) {
  s21_decimal first = {
      {0b00000000000000000000111111111111, 0b00000000000000000000000000000001,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};

  s21_decimal second = {
      {0b00000000000000000000000000000111, 0b00000000000000000000000000000001,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};

  s21_decimal decimal_check = {
      {0b00000000000000000110111111111001, 0b00000000000000000001000000000110,
       0b00000000000000000000000000000001, 0b00000000000000000000000000000000}};

  s21_decimal decimal_result = init_zero_decimal();
  ck_assert_int_eq((s21_mul(first, second, &decimal_result)), 0);
  compare(decimal_check, decimal_result);
}
END_TEST

START_TEST(s21_mul_test_2) {
  s21_decimal first = {
      {0b11111111111111111111111111111111, 0b00000000000000000000000000000001,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};

  s21_decimal second = {
      {0b11111111111111111111111111111111, 0b00000000000000000000000000000001,
       0b00000000000000000000000000000000, 0b10000000000000000000000000000000}};

  s21_decimal decimal_check = {
      {0b00000000000000000000000000000001, 0b11111111111111111111111111111100,
       0b00000000000000000000000000000011, 0b10000000000000000000000000000000}};

  s21_decimal decimal_result = init_zero_decimal();
  ck_assert_int_eq((s21_mul(first, second, &decimal_result)), 0);
  compare(decimal_check, decimal_result);
}
END_TEST

START_TEST(s21_mul_test_3) {
  s21_decimal first = {
      {0b11111111111111111111111111111111, 0b00000001000000000000000100000001,
       0b00000000000000000000000000000000, 0b10000000000000000000000000000000}};

  s21_decimal second = {
      {0b11111011101001111111110001110111, 0b00000000000000000000000000000001,
       0b00000000000000000000000000000000, 0b10000000000000000000000000000000}};

  s21_decimal decimal_check = {
      {0b00000100010110000000001110001001, 0b00010110010011000110111111101100,
       0b00000001111110111010100111111100, 0b00000000000000000000000000000000}};

  s21_decimal decimal_result = init_zero_decimal();
  ck_assert_int_eq((s21_mul(first, second, &decimal_result)), 0);
  compare(decimal_check, decimal_result);
}
END_TEST

START_TEST(s21_mul_test_4) {
  s21_decimal first = {{13, 0b00000000000000000000000000000000,
                        0b00000000000000000000000000000000,
                        0b00000000000000010000000000000000}};

  s21_decimal second = {{11, 0b00000000000000000000000000000000,
                         0b00000000000000000000000000000000,
                         0b00000000000101110000000000000000}};

  s21_decimal decimal_check = {
      {0b00000000000000000000000010001111, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000110000000000000000000}};

  s21_decimal decimal_result = init_zero_decimal();
  ck_assert_int_eq((s21_mul(first, second, &decimal_result)), 0);
  compare(decimal_check, decimal_result);
}
END_TEST

// 64438.2323 * 21.1 = 1359646.70153
START_TEST(s21_mul_test_5) {
  s21_decimal input1 = {{0x26687e73, 0, 0, 0b00000000000001000000000000000000}};
  s21_decimal input2 = {{0xd3, 0, 0, 0b00000000000000010000000000000000}};
  s21_decimal expected = {{0xA82038C9, 0x0000001F, 0x00000000, 0x00050000}};
  s21_decimal result = init_zero_decimal();
  int status = s21_mul(input1, input2, &result);

  compare(result, expected);
  ck_assert_int_eq(status, 0);
}
END_TEST
// -10.24 * 10.24 = 104.8576
START_TEST(s21_mul_test_6) {
  s21_decimal input1 = {{0x400, 0, 0, 0b10000000000000100000000000000000}};
  s21_decimal input2 = {{0x400, 0, 0, 0b10000000000000100000000000000000}};
  s21_decimal expected = {{0x00100000, 0x00000000, 0x00000000, 0x00040000}};
  s21_decimal result = init_zero_decimal();
  int status = s21_mul(input1, input2, &result);

  compare(result, expected);
  ck_assert_int_eq(status, 0);
}
END_TEST
// 1e-28 * 1e-28 = 0
START_TEST(s21_mul_test_7) {
  s21_decimal input1 = {{0x1, 0, 0, init_sign_and_scale(0, 28)}};
  s21_decimal input2 = {{0x1, 0, 0, init_sign_and_scale(0, 28)}};
  s21_decimal expected = {{0, 0, 0, 0}};
  s21_decimal result = init_zero_decimal();
  int status = s21_mul(input1, input2, &result);

  compare(result, expected);
  ck_assert_int_eq(status, 0);
}
END_TEST
// 1e-14 * 1e-14 = 1e-28
START_TEST(s21_mul_test_8) {
  s21_decimal input1 = {{0x1, 0, 0, init_sign_and_scale(1, 14)}};
  s21_decimal input2 = {{0x1, 0, 0, init_sign_and_scale(1, 14)}};
  s21_decimal expected = {{0x1, 0, 0, init_sign_and_scale(0, 28)}};
  s21_decimal result = init_zero_decimal();
  int status = s21_mul(input1, input2, &result);

  compare(result, expected);
  ck_assert_int_eq(status, 0);
}
END_TEST
// 6e-15 * 1e-14 = 1e-28
START_TEST(s21_mul_test_9) {
  s21_decimal input1 = {{0x6, 0, 0, init_sign_and_scale(1, 15)}};
  s21_decimal input2 = {{0x1, 0, 0, init_sign_and_scale(1, 14)}};
  s21_decimal expected = {{0x1, 0, 0, init_sign_and_scale(0, 28)}};
  s21_decimal result = init_zero_decimal();
  int status = s21_mul(input1, input2, &result);

  compare(result, expected);
  ck_assert_int_eq(status, 0);
}
END_TEST
// 0 * -42949672.95 = 0
START_TEST(s21_mul_test_10) {
  s21_decimal input1 = {{0}};
  s21_decimal input2 = {{0xffffffff, 0, 0, 0b10000000000000100000000000000000}};
  s21_decimal expected = {{0, 0, 0, 0}};
  s21_decimal result = init_zero_decimal();
  int status = s21_mul(input1, input2, &result);

  compare(result, expected);
  ck_assert_int_eq(status, 0);
}
END_TEST
// 18446744073709.551615 * 1 = 18446744073709.551615
START_TEST(s21_mul_test_11) {
  s21_decimal input1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0, init_sign_and_scale(1, 6)}};
  s21_decimal input2 = {{1}};
  s21_decimal expected = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0, init_sign_and_scale(1, 6)}};
  s21_decimal result = init_zero_decimal();
  int status = s21_mul(input1, input2, &result);

  compare(result, expected);
  ck_assert_int_eq(status, 0);
}
END_TEST
// 644388461.24564323 * 100 = 64438846124.56432300
START_TEST(s21_mul_test_12) {
  s21_decimal input1 = {{0x4fd9f63, 0xe4eeca, 0, init_sign_and_scale(0, 8)}};
  s21_decimal input2 = {{0x64, 0, 0, init_sign_and_scale(0, 0)}};
  s21_decimal expected = {
      {0xf31242ac, 0x596d46e9, 0, init_sign_and_scale(0, 8)}};
  s21_decimal result = init_zero_decimal();
  int status = s21_mul(input1, input2, &result);

  compare(result, expected);
  ck_assert_int_eq(status, 0);
}
END_TEST
// 75628.4783749104619446 * 7562849.389272378 = 571966791489.29083373022722365
START_TEST(s21_mul_test_13) {
  s21_decimal input1 = {
      {0xee7f4fb6, 0xff8f4bd9, 0x28, init_sign_and_scale(0, 16)}};
  s21_decimal input2 = {{0x17565d3a, 0x1ade5f, 0, init_sign_and_scale(0, 9)}};
  s21_decimal expected = {
      {0xebedb93d, 0x9c7bbf94, 0xb8cffbed, init_sign_and_scale(0, 17)}};
  s21_decimal result = init_zero_decimal();
  int status = s21_mul(input1, input2, &result);

  compare(result, expected);
  ck_assert_int_eq(status, 0);
}
END_TEST
// 75628.478374910555555 * 7562849.389555555 = 571966791510.70778731235573959
START_TEST(s21_mul_test_14) {
  s21_decimal input1 = {
      {0x97daf5a3, 0x198e5462, 0x4, init_sign_and_scale(0, 15)}};
  s21_decimal input2 = {{0x175aaf63, 0x1ade5f, 0, init_sign_and_scale(0, 9)}};
  s21_decimal expected = {
      {0xaf4f00c7, 0xba349429, 0xb8cffbed, init_sign_and_scale(0, 17)}};
  s21_decimal result = init_zero_decimal();
  int status = s21_mul(input1, input2, &result);

  compare(result, expected);
  ck_assert_int_eq(status, 0);
}
END_TEST
// -7.9228162514264337593543950335 * 7.9228162514264337593543950335 =
// -62.771017353866807638357894230
START_TEST(s21_mul_test_15) {
  s21_decimal input1 = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, init_sign_and_scale(1, 28)}};
  s21_decimal input2 = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, init_sign_and_scale(0, 28)}};
  s21_decimal expected = {
      {0x96EE456, 0x359A3B3E, 0xCAD2F7F5, init_sign_and_scale(1, 27)}};
  s21_decimal result = init_zero_decimal();
  int status = s21_mul(input1, input2, &result);

  compare(result, expected);
  ck_assert_int_eq(status, 0);
}
END_TEST
// 27824724378.43634677634 * 46513.1237326723 = 1294214847841713.1524935845060
START_TEST(s21_mul_test_16) {
  s21_decimal input1 = {
      {0x4903e782, 0xd68fe40c, 0x96, init_sign_and_scale(1, 11)}};
  s21_decimal input2 = {{0xce2cbf83, 0x1a708, 0, init_sign_and_scale(0, 10)}};
  s21_decimal expected = {
      {0xffa304c4, 0xd8b3a201, 0x29d17e8a, init_sign_and_scale(1, 13)}};
  s21_decimal result = init_zero_decimal();
  int status = s21_mul(input1, input2, &result);

  compare(result, expected);
  ck_assert_int_eq(status, 0);
}
END_TEST
// 79228162514264337593543950335 * 1.1 = INF
START_TEST(s21_mul_test_17) {
  s21_decimal input1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  s21_decimal input2 = {{11, 0, 0, init_sign_and_scale(0, 1)}};
  s21_decimal result = init_zero_decimal();
  int status = s21_mul(input1, input2, &result);

  ck_assert_int_eq(status, 1);
}
END_TEST
// -79228162514264337593543950335 * 79228162514264337593543950335 = -INF
START_TEST(s21_mul_test_18) {
  s21_decimal input1 = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, init_sign_and_scale(1, 0)}};
  s21_decimal input2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  s21_decimal result = init_zero_decimal();
  int status = s21_mul(input1, input2, &result);

  ck_assert_int_eq(status, 2);
}
END_TEST

START_TEST(s21_mul_test_19) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(s21_mul_test_20) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(s21_mul_test_21) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(s21_mul_test_22) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(s21_mul_test_23) {
  s21_decimal val1 = {{8, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(s21_mul_test_24) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(s21_mul_test_25) {
  s21_decimal val1 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(s21_mul_test_26) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(s21_mul_test_27) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(1, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(s21_mul_test_28) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(2, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(s21_mul_test_29) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(1, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(s21_mul_test_30) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(s21_mul_test_31) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  set_power(&val1, 1);
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(s21_mul_test_32) {
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal val1 = {{20, 0, 0, 0}};
  s21_decimal res = {{0}};
  set_power(&val2, 1);
  set_power(&val2, 2);
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(s21_mul_test_33) {
  // 792281625.14264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_eq(code, OK);
}
END_TEST

START_TEST(s21_mul_test_34) {
  // 7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // 7.8228162514264337593543950335
  s21_decimal decimal2 = {{0x17FFFFFF, 0x602F7FC3, 0xFCC4D1C3, 0x1C0000}};
  // 61.978735728724164262422454727
  s21_decimal check = {{0xE07921C7, 0x3FD7ABE1, 0xC8439BCC, 0x1B0000}};
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(code, OK);
  compare(result, check);
}
END_TEST

START_TEST(s21_mul_test_35) {
  // 7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // -0.8228162514264337593543950335
  s21_decimal decimal2 = {{0x4F63FFFF, 0xBB0D25CF, 0x1A962D2F, 0x801C0000}};
  // -6.5190219687391279469416894926
  s21_decimal check = {{0x23B23CAE, 0xEC60363A, 0xD2A415FA, 0x801C0000}};
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(code, OK);
  compare(result, check);
}
END_TEST

START_TEST(s21_mul_test_36) {
  // -7.000000000000025
  s21_decimal decimal1 = {{0x816D8019, 0x18DE76, 0x0, 0x800F0000}};
  // -0.00000000000005
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x800E0000}};
  // 0.0000000000003500000000000012
  s21_decimal check = {{0x40B6C00C, 0xC6F3B, 0x0, 0x1C0000}};
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(code, OK);
  compare(check, result);
}
END_TEST

START_TEST(s21_mul_test_37) {
  // -7922816251426.4337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80100000}};
  // 78228162514264.337593543950335
  s21_decimal decimal2 = {{0x17FFFFFF, 0x602F7FC3, 0xFCC4D1C3, 0xF0000}};
  // -619787357287241642624224547.27
  s21_decimal check = {{0xE07921C7, 0x3FD7ABE1, 0xC8439BCC, 0x80020000}};
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(code, OK);
  compare(result, check);
}
END_TEST

START_TEST(s21_mul_test_38) {
  // -79228162514264.337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800F0000}};
  // 782281625142643.37593543950335
  s21_decimal decimal2 = {{0x17FFFFFF, 0x602F7FC3, 0xFCC4D1C3, 0xE0000}};
  // -61978735728724164262422454727
  s21_decimal check = {{0xE07921C7, 0x3FD7ABE1, 0xC8439BCC, 0x80000000}};

  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(code, OK);
  compare(result, check);
}
END_TEST

START_TEST(s21_mul_test_39) {
  // 79228162514264.1
  s21_decimal decimal1 = {{0x70D42571, 0x2D093, 0x0, 0x10000}};
  // 78228162514264.5
  s21_decimal decimal2 = {{0x22618575, 0x2C77B, 0x0, 0x10000}};
  // 6197873572872410706900970254.4
  s21_decimal check = {{0x7F6C2E90, 0x3FD777DD, 0xC8439BCC, 0x10000}};

  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(code, OK);
  compare(result, check);
}
END_TEST

START_TEST(s21_mul_test_40) {
  // 79228162514265.1
  s21_decimal decimal1 = {{0x70D4257B, 0x2D093, 0x0, 0x10000}};
  // 78228162514264.5
  s21_decimal decimal2 = {{0x22618575, 0x2C77B, 0x0, 0x10000}};
  // 6197873572872488935063484519.0
  s21_decimal check = {{0xA1CDB406, 0x3FDA3F58, 0xC8439BCC, 0x10000}};

  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(code, OK);
  compare(result, check);
}
END_TEST

START_TEST(s21_mul_test_41) {
  // 5.0
  s21_decimal decimal1 = {{0x32, 0x0, 0x0, 0x10000}};
  // 4.5
  s21_decimal decimal2 = {{0x2D, 0x0, 0x0, 0x10000}};
  // 22.50
  s21_decimal check = {{0x8CA, 0x0, 0x0, 0x20000}};

  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(code, OK);
  compare(result, check);
}
END_TEST

START_TEST(s21_mul_test_42) {
  // 79228162.5
  s21_decimal decimal1 = {{0x2F394219, 0x0, 0x0, 0x10000}};
  // 78228162.5555555555555
  s21_decimal decimal2 = {{0xB20798E3, 0x6856A1BC, 0x2A, 0xD0000}};
  // 6197873575027970.8333289317688
  s21_decimal check = {{0x34C52538, 0x6AFC5902, 0xC8439BCD, 0xD0000}};

  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(code, OK);
  compare(result, check);
}

START_TEST(s21_mul_test_43) {
  // -7.000000000000025
  s21_decimal decimal1 = {{0x816D8019, 0x18DE76, 0x0, 0x800F0000}};
  // -2.00000000000005
  s21_decimal decimal2 = {{0x20F48005, 0xB5E6, 0x0, 0x800E0000}};
  // 14.000000000000400000000000001
  s21_decimal check = {{0xF1E90001, 0xBD686F20, 0x2D3C8750, 0x1B0000}};

  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(code, OK);
  compare(result, check);
}
END_TEST

START_TEST(s21_mul_test_44) {
  // -7.000000000000025
  s21_decimal decimal1 = {{0x816D8019, 0x18DE76, 0x0, 0x800F0000}};
  // -0.0000000000005
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x800D0000}};
  // 0.0000000000035000000000000125
  s21_decimal check = {{0x8723807D, 0x7C5850, 0x0, 0x1C0000}};
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(code, OK);
  compare(result, check);
}
END_TEST

START_TEST(s21_mul_test_45) {
  // -7.000000000000025
  s21_decimal decimal1 = {{0x816D8019, 0x18DE76, 0x0, 0x800F0000}};
  // -0.000000000000005
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x800F0000}};
  // 0.0000000000000350000000000001
  s21_decimal check = {{0xB9ABE001, 0x13E52, 0x0, 0x1C0000}};
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(code, OK);
  compare(result, check);
}
END_TEST

START_TEST(s21_mul_test_46) {
  // 7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // 0.00000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x50000}};
  // 0
  s21_decimal check = {{0, 0, 0, 0}};

  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(code, OK);
  compare(result, check);
}
END_TEST

START_TEST(s21_mul_test_47) {
  // 7922816251426433759354395032.8
  s21_decimal decimal1 = {{0xFFFFFFF8, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 10.000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1B0000}};
  // overflow
  s21_decimal check = {{0, 0, 0, 0}};
  int code = s21_mul(decimal1, decimal2, &check);
  int code_check = TOO_BIG;
  ck_assert_int_eq(code, code_check);
}
END_TEST

START_TEST(s21_mul_test_48) {
  // 7922816251426433759354395032.8
  s21_decimal decimal1 = {{0xFFFFFFF8, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -10.000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x801B0000}};
  // overflow
  s21_decimal check = {{0, 0, 0, 0}};
  int code = s21_mul(decimal1, decimal2, &check);
  int code_check = TOO_SMALL;
  ck_assert_int_eq(code, code_check);
}
END_TEST

START_TEST(s21_mul_test_49) {
  // -7922816251426433759354395032.7
  s21_decimal decimal1 = {{0xFFFFFFF7, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 10.000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1B0000}};
  // -79228162514264337593543950335
  s21_decimal decimal_check = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);
  int code_check = OK;
  ck_assert_int_eq(code, code_check);
  compare(result, decimal_check);
}
END_TEST

START_TEST(s21_mul_test_50) {
  // -7922816251426433759354395032.7
  s21_decimal decimal1 = {{0xFFFFFFF7, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -10.000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x801B0000}};
  // 79228162514264337593543950335
  s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);
  int code_check = OK;
  ck_assert_int_eq(code, code_check);
  compare(result, decimal_check);
}
END_TEST

START_TEST(s21_mul_test_51) {
  // -0.0000000000000025
  s21_decimal decimal1 = {{0x19, 0x0, 0x0, 0x80100000}};
  // -0.0000000000000005
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80100000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);
  int code_check = OK;
  ck_assert_int_eq(code, code_check);
  compare(result, decimal_check);
}
END_TEST

START_TEST(s21_mul_test_52) {
  // 792281625142643.37593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xE0000}};
  // -782281625142643.37593543950335
  s21_decimal decimal2 = {{0x17FFFFFF, 0x602F7FC3, 0xFCC4D1C3, 0x800E0000}};
  // overflow
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal result = {0};
  int code = s21_mul(decimal1, decimal2, &result);
  int code_check = TOO_SMALL;
  ck_assert_int_eq(code, code_check);
  compare(decimal_check, result);
}
END_TEST

START_TEST(s21_mul_test_53) {
  // 792281625142643.37593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xE0000}};
  // 782281625142643.37593543950335
  s21_decimal decimal2 = {{0x17FFFFFF, 0x602F7FC3, 0xFCC4D1C3, 0xE0000}};
  // overflow
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);
  int code_check = TOO_BIG;
  ck_assert_int_eq(code, code_check);
}
END_TEST

START_TEST(s21_mul_test_54) {
  // -7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // 0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // -3.9614081257132168796771975175
  s21_decimal decimal_check = {{0x7, 0x0, 0x80000000, 0x801C0000}};

  s21_decimal result = {0};
  int code = s21_mul(decimal1, decimal2, &result);
  int code_check = OK;
  ck_assert_int_eq(code, code_check);
  compare(decimal_check, result);
}
END_TEST

START_TEST(s21_mul_test_55) {
  // 7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // 0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x1C0000}};
  // 0.0000000000000000000000000079
  s21_decimal decimal_check = {{0x4F, 0x0, 0x0, 0x1C0000}};
  s21_decimal result = {0};
  int code = s21_mul(decimal1, decimal2, &result);
  int code_check = OK;
  ck_assert_int_eq(code, code_check);
  compare(decimal_check, result);
}
END_TEST

START_TEST(s21_mul_test_56) {
  // -7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // 0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // -0.0000000000000000000000000008
  s21_decimal decimal_check = {{0x8, 0x0, 0x0, 0x801C0000}};
  s21_decimal result = {0};
  int code = s21_mul(decimal1, decimal2, &result);
  int code_check = OK;
  ck_assert_int_eq(code, code_check);
  compare(decimal_check, result);
}
END_TEST

START_TEST(s21_mul_test_57) {
  // 0.7922816251426433759354395034
  s21_decimal decimal1 = {{0x9999999A, 0x99999999, 0x19999999, 0x1C0000}};
  // -7055.820576069728775806815669
  s21_decimal decimal2 = {{0x69168DB5, 0xDCB4F4B1, 0x16CC701F, 0x80180000}};
  // -5590.1969927234268947708082480
  s21_decimal decimal_check = {
      {0x2DC77930, 0x10FB6E4E, 0xB4A10696, 0x80190000}};

  s21_decimal result = {0};
  int code = s21_mul(decimal1, decimal2, &result);
  int code_check = OK;
  ck_assert_int_eq(code, code_check);
  compare(decimal_check, result);
}

START_TEST(s21_mul_test_58) {
  // 0.7922816251426433759354395034
  s21_decimal decimal1 = {{0x9999999A, 0x99999999, 0x19999999, 0x1C0000}};
  // 7055.820576069728775806815669
  s21_decimal decimal2 = {{0x69168DB5, 0xDCB4F4B1, 0x16CC701F, 0x180000}};
  // 5590.1969927234268947708082480
  s21_decimal decimal_check = {{0x2DC77930, 0x10FB6E4E, 0xB4A10696, 0x190000}};
  s21_decimal result = {0};
  int code = s21_mul(decimal1, decimal2, &result);
  int code_check = OK;
  ck_assert_int_eq(code, code_check);
  compare(decimal_check, result);
}

START_TEST(s21_mul_test_59) {
  // -0.7922816251426433759354395034
  s21_decimal decimal1 = {{0x9999999A, 0x99999999, 0x19999999, 0x801C0000}};
  // 26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -20923672451288935879452631411
  s21_decimal decimal_check = {
      {0xADCFA173, 0x67336914, 0x439BA7FC, 0x80000000}};
  s21_decimal result = {0};
  int code = s21_mul(decimal1, decimal2, &result);
  int code_check = OK;
  ck_assert_int_eq(code, code_check);
  compare(decimal_check, result);
}

START_TEST(s21_mul_test_60) {
  // -0.7922816251426433759354395034
  s21_decimal decimal1 = {{0x9999999A, 0x99999999, 0x19999999, 0x801C0000}};
  // -26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // 20923672451288935879452631411
  s21_decimal decimal_check = {{0xADCFA173, 0x67336914, 0x439BA7FC, 0x0}};
  s21_decimal result = {0};
  int code = s21_mul(decimal1, decimal2, &result);
  int code_check = OK;
  ck_assert_int_eq(code, code_check);
  compare(decimal_check, result);
}

START_TEST(s21_mul_test_61) {
  // -0.7922816251426433759354395034
  s21_decimal decimal1 = {{0x9999999A, 0x99999999, 0x19999999, 0x801C0000}};
  // 26409387498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // -20923672446417263756150562907
  s21_decimal decimal_check = {
      {0x8A37E05B, 0x2397C118, 0x439BA7FC, 0x80000000}};
  s21_decimal result = {0};
  int code = s21_mul(decimal1, decimal2, &result);
  int code_check = OK;
  ck_assert_int_eq(code, code_check);
  compare(decimal_check, result);
}

START_TEST(s21_mul_test_62) {
  // -0.7922816251426433759354395034
  s21_decimal decimal1 = {{0x9999999A, 0x99999999, 0x19999999, 0x801C0000}};
  // -26409387498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // 20923672446417263756150562907
  s21_decimal decimal_check = {{0x8A37E05B, 0x2397C118, 0x439BA7FC, 0x0}};
  s21_decimal result = {0};
  int code = s21_mul(decimal1, decimal2, &result);
  int code_check = OK;
  ck_assert_int_eq(code, code_check);
  compare(decimal_check, result);
}

START_TEST(s21_mul_test_63) {
  // -0.7922816251426433759354395034
  s21_decimal decimal1 = {{0x9999999A, 0x99999999, 0x19999999, 0x801C0000}};
  // 6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // -4871672124436343060.4148555676
  s21_decimal decimal_check = {
      {0xD4B7BF9C, 0x79B8EBC2, 0x9D6986FE, 0x800A0000}};
  s21_decimal result = {0};
  int code = s21_mul(decimal1, decimal2, &result);
  int code_check = OK;
  ck_assert_int_eq(code, code_check);
  compare(decimal_check, result);
}

START_TEST(s21_mul_test_64) {
  // -0.7922816251426433759354395034
  s21_decimal decimal1 = {{0x9999999A, 0x99999999, 0x19999999, 0x801C0000}};
  // -6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // 4871672124436343060.4148555676
  s21_decimal decimal_check = {{0xD4B7BF9C, 0x79B8EBC2, 0x9D6986FE, 0xA0000}};
  s21_decimal result = {0};
  int code = s21_mul(decimal1, decimal2, &result);
  int code_check = OK;
  ck_assert_int_eq(code, code_check);
  compare(decimal_check, result);
}

START_TEST(s21_mul_test_65) {
  // -0.7922816251426433759354395034
  s21_decimal decimal1 = {{0x9999999A, 0x99999999, 0x19999999, 0x801C0000}};
  // 6148914689804861440
  s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x0}};
  // -4871672123302068504.2758212311
  s21_decimal decimal_check = {
      {0xF8685AD7, 0xDC4F64C4, 0x9D6986FD, 0x800A0000}};
  s21_decimal result = {0};
  int code = s21_mul(decimal1, decimal2, &result);
  int code_check = OK;
  ck_assert_int_eq(code, code_check);
  compare(decimal_check, result);
}

START_TEST(s21_mul_test_66) {
  // -0.7922816251426433759354395034
  s21_decimal decimal1 = {{0x9999999A, 0x99999999, 0x19999999, 0x801C0000}};
  // -6148914689804861440
  s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x80000000}};
  // 4871672123302068504.2758212311
  s21_decimal decimal_check = {{0xF8685AD7, 0xDC4F64C4, 0x9D6986FD, 0xA0000}};
  s21_decimal result = {0};
  int code = s21_mul(decimal1, decimal2, &result);
  int code_check = OK;
  ck_assert_int_eq(code, code_check);
  compare(decimal_check, result);
}

START_TEST(s21_mul_test_67) {
  // -0.7922816251426433759354395034
  s21_decimal decimal1 = {{0x9999999A, 0x99999999, 0x19999999, 0x801C0000}};
  // 1431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x0}};
  // -1134274556.1390343364970342329
  s21_decimal decimal_check = {
      {0xA940E7B9, 0xFB0123D2, 0x24A67FCC, 0x80130000}};
  s21_decimal result = {0};
  int code = s21_mul(decimal1, decimal2, &result);
  int code_check = OK;
  ck_assert_int_eq(code, code_check);
  compare(decimal_check, result);
}

START_TEST(s21_mul_test_68) {
  // -0.7922816251426433759354395034
  s21_decimal decimal1 = {{0x9999999A, 0x99999999, 0x19999999, 0x801C0000}};
  // -1431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x80000000}};
  // 1134274556.1390343364970342329
  s21_decimal decimal_check = {{0xA940E7B9, 0xFB0123D2, 0x24A67FCC, 0x130000}};
  s21_decimal result = {0};
  int code = s21_mul(decimal1, decimal2, &result);
  int code_check = OK;
  ck_assert_int_eq(code, code_check);
  compare(decimal_check, result);
}

START_TEST(s21_mul_test_69) {
  // -0.7922816251426433759354395034
  s21_decimal decimal1 = {{0x9999999A, 0x99999999, 0x19999999, 0x801C0000}};
  // 26409387.504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x150000}};
  // -20923672.451288935879452631411
  s21_decimal decimal_check = {
      {0xADCFA173, 0x67336914, 0x439BA7FC, 0x80150000}};
  s21_decimal result = {0};
  int code = s21_mul(decimal1, decimal2, &result);
  int code_check = OK;
  ck_assert_int_eq(code, code_check);
  compare(decimal_check, result);
}

START_TEST(s21_mul_test_70) {
  // -0.7922816251426433759354395034
  s21_decimal decimal1 = {{0x9999999A, 0x99999999, 0x19999999, 0x801C0000}};
  // -26409387.504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80150000}};
  // 20923672.451288935879452631411
  s21_decimal decimal_check = {{0xADCFA173, 0x67336914, 0x439BA7FC, 0x150000}};
  s21_decimal result = {0};
  int code = s21_mul(decimal1, decimal2, &result);
  int code_check = OK;
  ck_assert_int_eq(code, code_check);
  compare(decimal_check, result);
}

START_TEST(s21_mul_test_71) {
  // -0.7922816251426433759354395034
  s21_decimal decimal1 = {{0x9999999A, 0x99999999, 0x19999999, 0x801C0000}};
  // 26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x150000}};
  // -20923672.446417263756150562907
  s21_decimal decimal_check = {
      {0x8A37E05B, 0x2397C118, 0x439BA7FC, 0x80150000}};
  s21_decimal result = {0};
  int code = s21_mul(decimal1, decimal2, &result);
  int code_check = OK;
  ck_assert_int_eq(code, code_check);
  compare(decimal_check, result);
}

START_TEST(s21_mul_test_72) {
  // -0.7922816251426433759354395034
  s21_decimal decimal1 = {{0x9999999A, 0x99999999, 0x19999999, 0x801C0000}};
  // -26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80150000}};
  // 20923672.446417263756150562907
  s21_decimal decimal_check = {{0x8A37E05B, 0x2397C118, 0x439BA7FC, 0x150000}};
  s21_decimal result = {0};
  int code = s21_mul(decimal1, decimal2, &result);
  int code_check = OK;
  ck_assert_int_eq(code, code_check);
  compare(decimal_check, result);
}

START_TEST(s21_mul_test_73) {
  // -0.7922816251426433759354395034
  s21_decimal decimal1 = {{0x9999999A, 0x99999999, 0x19999999, 0x801C0000}};
  // 26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x0}};
  // -20923672.051380999118065508860
  s21_decimal decimal_check = {
      {0x3BF421FC, 0xB95D0366, 0x439BA7E6, 0x80150000}};
  s21_decimal result = {0};
  int code = s21_mul(decimal1, decimal2, &result);
  int code_check = OK;
  ck_assert_int_eq(code, code_check);
  compare(decimal_check, result);
}

START_TEST(s21_mul_test_74) {
  // -0.7922816251426433759354395034
  s21_decimal decimal1 = {{0x9999999A, 0x99999999, 0x19999999, 0x801C0000}};
  // -26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x80000000}};
  // 20923672.051380999118065508860
  s21_decimal decimal_check = {{0x3BF421FC, 0xB95D0366, 0x439BA7E6, 0x150000}};
  s21_decimal result = {0};
  int code = s21_mul(decimal1, decimal2, &result);
  int code_check = OK;
  ck_assert_int_eq(code, code_check);
  compare(decimal_check, result);
}

START_TEST(s21_mul_test_75) {
  // -0.7922816251426433759354395034
  s21_decimal decimal1 = {{0x9999999A, 0x99999999, 0x19999999, 0x801C0000}};
  // 1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // -1.5845632502852867518708789276
  s21_decimal decimal_check = {
      {0x3333301C, 0x33333333, 0x33333333, 0x801C0000}};
  s21_decimal result = {0};
  int code = s21_mul(decimal1, decimal2, &result);
  int code_check = OK;
  ck_assert_int_eq(code, code_check);
  compare(decimal_check, result);
}

START_TEST(s21_mul_test_76) {
  // -0.9999999999999999999999999999
  s21_decimal decimal1 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // 1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x0}};
  // -0.9999999999999999999999999999
  s21_decimal decimal_check = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  s21_decimal result = {0};
  int code = s21_mul(decimal1, decimal2, &result);
  int code_check = OK;
  ck_assert_int_eq(code, code_check);
  compare(decimal_check, result);
}
END_TEST

START_TEST(s21_mul_test_77) {
  // -0.9999999999999999999999999999
  s21_decimal decimal1 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // 0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x10000}};
  // -0.5000000000000000000000000000
  s21_decimal decimal_check = {
      {0x88000000, 0x1F128130, 0x1027E72F, 0x801C0000}};
  s21_decimal result = {0};
  int code = s21_mul(decimal1, decimal2, &result);
  int code_check = OK;
  ck_assert_int_eq(code, code_check);
  compare(decimal_check, result);
}
END_TEST

START_TEST(s21_mul_test_78) {
  // -0.9999999999999999999999999999
  s21_decimal decimal1 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -79228162514264337593543950327
  s21_decimal decimal_check = {
      {0xFFFFFFF7, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal result = {0};
  int code = s21_mul(decimal1, decimal2, &result);
  int code_check = OK;
  ck_assert_int_eq(code, code_check);
  compare(decimal_check, result);
}
END_TEST

START_TEST(s21_mul_test_79) {
  // -0.9999999999999999999999999999
  s21_decimal decimal1 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // 0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // -0.0000000000000000000000000001
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x801C0000}};
  s21_decimal result = {0};
  int code = s21_mul(decimal1, decimal2, &result);
  int code_check = OK;
  ck_assert_int_eq(code, code_check);
  compare(decimal_check, result);
}
END_TEST

START_TEST(s21_mul_test_80) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // overflow
  s21_decimal result = {0};
  int code = s21_mul(decimal1, decimal2, &result);
  int code_check = TOO_BIG;
  ck_assert_int_eq(code, code_check);
}
END_TEST

START_TEST(s21_mul_test_81) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  s21_decimal result = {0};
  int code = s21_mul(decimal1, decimal2, &result);
  int code_check = OK;
  ck_assert_int_eq(code, code_check);
  compare(decimal_check, result);
}
END_TEST

Suite *test_s21_mul() {
  Suite *suite = suite_create("s21_mul");
  TCase *t_case = tcase_create("s21_mul");

  suite_add_tcase(suite, t_case);
  tcase_add_test(t_case, s21_mul_test_1);
  tcase_add_test(t_case, s21_mul_test_2);
  tcase_add_test(t_case, s21_mul_test_3);
  tcase_add_test(t_case, s21_mul_test_4);
  tcase_add_test(t_case, s21_mul_test_5);
  tcase_add_test(t_case, s21_mul_test_6);
  tcase_add_test(t_case, s21_mul_test_7);
  tcase_add_test(t_case, s21_mul_test_8);
  tcase_add_test(t_case, s21_mul_test_9);
  tcase_add_test(t_case, s21_mul_test_10);
  tcase_add_test(t_case, s21_mul_test_11);
  tcase_add_test(t_case, s21_mul_test_12);
  tcase_add_test(t_case, s21_mul_test_13);
  tcase_add_test(t_case, s21_mul_test_14);
  tcase_add_test(t_case, s21_mul_test_15);
  tcase_add_test(t_case, s21_mul_test_16);
  tcase_add_test(t_case, s21_mul_test_17);
  tcase_add_test(t_case, s21_mul_test_18);
  tcase_add_test(t_case, s21_mul_test_19);
  tcase_add_test(t_case, s21_mul_test_20);
  tcase_add_test(t_case, s21_mul_test_21);
  tcase_add_test(t_case, s21_mul_test_22);
  tcase_add_test(t_case, s21_mul_test_23);
  tcase_add_test(t_case, s21_mul_test_24);
  tcase_add_test(t_case, s21_mul_test_25);
  tcase_add_test(t_case, s21_mul_test_26);
  tcase_add_test(t_case, s21_mul_test_27);
  tcase_add_test(t_case, s21_mul_test_28);
  tcase_add_test(t_case, s21_mul_test_29);
  tcase_add_test(t_case, s21_mul_test_30);
  tcase_add_test(t_case, s21_mul_test_31);
  tcase_add_test(t_case, s21_mul_test_32);
  tcase_add_test(t_case, s21_mul_test_33);
  tcase_add_test(t_case, s21_mul_test_34);
  tcase_add_test(t_case, s21_mul_test_35);
  tcase_add_test(t_case, s21_mul_test_36);
  tcase_add_test(t_case, s21_mul_test_37);
  tcase_add_test(t_case, s21_mul_test_38);
  tcase_add_test(t_case, s21_mul_test_39);
  tcase_add_test(t_case, s21_mul_test_40);
  tcase_add_test(t_case, s21_mul_test_41);
  tcase_add_test(t_case, s21_mul_test_42);
  tcase_add_test(t_case, s21_mul_test_43);
  tcase_add_test(t_case, s21_mul_test_44);
  tcase_add_test(t_case, s21_mul_test_45);
  tcase_add_test(t_case, s21_mul_test_46);
  tcase_add_test(t_case, s21_mul_test_47);
  tcase_add_test(t_case, s21_mul_test_48);
  tcase_add_test(t_case, s21_mul_test_49);
  tcase_add_test(t_case, s21_mul_test_50);
  tcase_add_test(t_case, s21_mul_test_51);
  tcase_add_test(t_case, s21_mul_test_52);
  tcase_add_test(t_case, s21_mul_test_53);
  tcase_add_test(t_case, s21_mul_test_54);
  tcase_add_test(t_case, s21_mul_test_55);
  tcase_add_test(t_case, s21_mul_test_56);
  tcase_add_test(t_case, s21_mul_test_57);
  tcase_add_test(t_case, s21_mul_test_58);
  tcase_add_test(t_case, s21_mul_test_59);
  tcase_add_test(t_case, s21_mul_test_60);
  tcase_add_test(t_case, s21_mul_test_61);
  tcase_add_test(t_case, s21_mul_test_62);
  tcase_add_test(t_case, s21_mul_test_63);
  tcase_add_test(t_case, s21_mul_test_64);
  tcase_add_test(t_case, s21_mul_test_65);
  tcase_add_test(t_case, s21_mul_test_66);
  tcase_add_test(t_case, s21_mul_test_67);
  tcase_add_test(t_case, s21_mul_test_68);
  tcase_add_test(t_case, s21_mul_test_69);
  tcase_add_test(t_case, s21_mul_test_70);
  tcase_add_test(t_case, s21_mul_test_71);
  tcase_add_test(t_case, s21_mul_test_72);
  tcase_add_test(t_case, s21_mul_test_73);
  tcase_add_test(t_case, s21_mul_test_74);
  tcase_add_test(t_case, s21_mul_test_75);
  tcase_add_test(t_case, s21_mul_test_76);
  tcase_add_test(t_case, s21_mul_test_77);
  tcase_add_test(t_case, s21_mul_test_78);
  tcase_add_test(t_case, s21_mul_test_79);
  tcase_add_test(t_case, s21_mul_test_80);
  tcase_add_test(t_case, s21_mul_test_81);
  return suite;
}