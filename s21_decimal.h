#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define BITS_IN_DECIMAL 128
#define BITS_IN_ONE_INT 32
#define BITS_IN_MANTISSA 96
#define MAX_CONV_FLOAT 79228157791897854723898736640.0f
#define MIN_CONV_FLOAT \
  0.00000000000000000000000000010000000031710768509710513471352647538147514756461109f
#define NUMS_IN_DECIMAL 29

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  unsigned int bits[8];
} double_decimal;

typedef union bits_bit3 {
  unsigned int a;
  struct {
    unsigned int empty_1 : 16;  // 1 - 16 bit
    unsigned int pow : 8;       // 17 - 24 bit
    unsigned int empty_2 : 7;   // 25 - 31 bit
    unsigned int sign : 1;      // 32 bit
  } bits_3_part;
} bits_bit3;

typedef union {
  float float_num;
  unsigned int bits;
} float_bits;

s21_decimal max_decimal(void);     // maximum
s21_decimal one_decimal(void);     // 1
s21_decimal o_five_decimal(void);  // 0.5

// MAIN FUNCTIONS
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);

int s21_is_equal(s21_decimal, s21_decimal);
int s21_is_not_equal(s21_decimal, s21_decimal);
int s21_is_less(s21_decimal, s21_decimal);
int s21_is_less_or_equal(s21_decimal, s21_decimal);
int s21_is_greater(s21_decimal, s21_decimal);
int s21_is_greater_or_equal(s21_decimal, s21_decimal);

// 0 - ошибка конвертации, 1 - ОК
int s21_from_int_to_decimal(int src, s21_decimal* dst);
int s21_from_float_to_decimal(float src, s21_decimal* dst);
int s21_from_decimal_to_int(s21_decimal src, int* dst);
int s21_from_decimal_to_float(s21_decimal src, float* dst);

int s21_floor(s21_decimal value, s21_decimal* result);
int s21_round(s21_decimal value, s21_decimal* result);
int s21_truncate(s21_decimal value, s21_decimal* result);
int s21_negate(s21_decimal value, s21_decimal* result);
//

typedef enum {
  CMP_FALSE,
  CMP_TRUE,
} compare_result;

typedef enum {
  POSITIVE,
  NEGATIVE,
} decimal_sign;

typedef enum {
  BITS_LESS = -1,
  BITS_EQUAL = 0,
  BITS_GREAT = 1,
} binary_compare_result;

typedef enum {
  OK,
  TOO_BIG,
  TOO_SMALL,
  DIV_BY_ZERO,
} arithmetic_result;

typedef enum {
  NO_ERROR,
  ERROR,
} error_code;

typedef enum {
  FAIL,
  SCALED,
  BIGGER_THAN_MANTISSA,
} normalize_result;

// SERVICE FUNCS
int get_sign(s21_decimal decimal);
int get_power(s21_decimal decimal);
int get_bit(unsigned int bits, unsigned int index);
int get_bit_in_decimal(s21_decimal* value, unsigned int index);
int set_bit(unsigned int bits, unsigned int index, int bit);
s21_decimal* set_bit_in_decimal(s21_decimal* value, unsigned int index,
                                int bit);
s21_decimal* set_sign(s21_decimal* value, int sign);
s21_decimal decimals_and(s21_decimal value_1, s21_decimal value_2);
s21_decimal decimals_xor(s21_decimal value_1, s21_decimal value_2);
s21_decimal decimals_inverse(s21_decimal value);

s21_decimal* decimal_abs(s21_decimal* value);
int binary_compare_mantissa(s21_decimal* value_1, s21_decimal* value_2);
int binary_compare_decimal(s21_decimal* value_1, s21_decimal* value_2);
s21_decimal init_zero_decimal(void);
s21_decimal mantissa_shift_left_step(s21_decimal* value);
s21_decimal mantissa_shift_right_step(s21_decimal* value);
s21_decimal mantissa_shifts_left(s21_decimal* value, unsigned int steps);

/**
 * Возвращает 1, если мантисса пустая (только нули)
 */
int check_zero_mantissa(s21_decimal* value);
int check_acceptable_pow(s21_decimal* value);
void set_power(s21_decimal* number, unsigned char power);
int mantissa_bit_length(s21_decimal number);

void mantissa_mul_by_ten(s21_decimal* number);
void mantissa_div_by_ten(s21_decimal* number);
void decimal_mul_by_ten(s21_decimal* number);
void decimal_div_by_ten(s21_decimal* number);

/**
 * Приведение к одной степени (к бОльшей)
 * Возвращает 1, если нет ошибок, иначе 0.
 */
int normalize_decimals(s21_decimal* value_1, s21_decimal* value_2);

/**
 * Проверка на допустимые децималы.
 * Возвращает 1, если децималы допустимые, иначе 0.
 */
int check_acceptable_decimal(s21_decimal* value);
int check_even_decimal(s21_decimal value);
int check_zero_one_bits(unsigned int bits);
int check_empty_parts_bits_3(s21_decimal* value);
int available_mul_by_ten(s21_decimal value);
int available_div_by_ten(s21_decimal value);
int basic_add(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
int basic_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
int available_normalize_by_mul(s21_decimal value, int add_pow,
                               int* available_pow);
void decimal_div_by_ten_rounded(s21_decimal* value);

int get_exp_from_float(char str_float[]);
unsigned int get_mantissa_from_float(char str_float[], int* pow);

int binary_is_less(s21_decimal value_1, s21_decimal value_2);
int binary_is_equal(s21_decimal value_1, s21_decimal value_2);
int binary_is_not_equal(s21_decimal value_1, s21_decimal value_2);
int binary_is_greater(s21_decimal value_1, s21_decimal value_2);
int number_of_nums_in_decimal(s21_decimal value);
s21_decimal first_num_in_decimal(s21_decimal value);
void multiple_mulling_decimal_by_ten(s21_decimal* value, int pow);
void scaling_decimal_for_add(s21_decimal* value, int pow);
void banking_for_add(s21_decimal* sum_int, s21_decimal* sum_rem,
                     arithmetic_result* message);
void get_sum_remainders(s21_decimal value_1, s21_decimal value_2,
                        s21_decimal value_1_int, s21_decimal value_2_int,
                        s21_decimal* sum_rem, arithmetic_result* message);
void make_zero_to_empty_decimal(s21_decimal* value);

double_decimal create_double_decimal(s21_decimal number);
int d_decimal_is_zero(double_decimal number);
void d_decimal_shift_left(double_decimal* number, int count);
void d_decimal_shift_right(double_decimal* number, int count);
void d_decimal_add(double_decimal value_1, double_decimal value_2,
                   double_decimal* result);
void d_decimal_sub(double_decimal value_1, double_decimal value_2,
                   double_decimal* result);
double_decimal d_decimal_div_by_ten(double_decimal value,
                                    double_decimal* remainder);
double_decimal d_decimal_mul_by_ten(double_decimal number);
int d_decimal_bit_length(double_decimal number);
int d_decimal_compare(double_decimal value_1, double_decimal value_2);
double_decimal d_decimal_division(double_decimal value_1,
                                  double_decimal value_2,
                                  double_decimal* remainder, int* power);
int count_digits(double_decimal number);
void convert_to_decimal(s21_decimal* result, double_decimal res, int* power,
                        int sign);

// void print_bits(unsigned int num);
// void print_decimal(s21_decimal number);
// void print_float_binary(float src);
// void print_hex_decimal(s21_decimal number);
// void print_double_decimal(double_decimal number);
#endif