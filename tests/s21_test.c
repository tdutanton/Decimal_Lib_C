#include "s21_test.h"

int main() {
  int n_failed = 0;
  Suite *suite = NULL;
  SRunner *sr = srunner_create(suite);

  Suite *suites[] = {
      test_suite(),

      // Arithmetic tests
      test_s21_add(), test_s21_sub(), test_s21_mul(), test_s21_div(),

      // Comparison tests
      test_s21_is_less(), test_s21_is_less_or_equal(), test_s21_is_greater(),
      test_s21_is_greater_or_equal(), test_s21_is_equal(),
      test_s21_is_not_equal(),

      // Conversion tests
      test_s21_from_int_to_decimal(), test_s21_from_float_to_decimal(),
      test_s21_from_decimal_to_int(), test_s21_from_decimal_to_float(),

      // Other tests
      test_s21_floor(), test_s21_round(), test_s21_truncate(),
      test_s21_negate(),

      // Mutual tests
      tests_mutual(), NULL};

  for (Suite **st = suites; *st != NULL; st++) srunner_add_suite(sr, *st);
  srunner_set_fork_status(sr, CK_NOFORK);  // запрещаем останавливать тесты
                                           // после первой найденной ошибки

  srunner_run_all(sr, CK_NORMAL);
  n_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  (void)n_failed;
  return 0;
}

void compare(s21_decimal check, s21_decimal res) {
  ck_assert_uint_eq(check.bits[0], res.bits[0]);
  ck_assert_uint_eq(check.bits[1], res.bits[1]);
  ck_assert_uint_eq(check.bits[2], res.bits[2]);
  ck_assert_uint_eq(check.bits[3], res.bits[3]);
}

uint32_t init_sign_and_scale(unsigned int sign, int scale) {
  return (sign << 31) | (scale << 16);
}

START_TEST(nothing) { ck_assert_int_eq(1, 1); }
END_TEST

Suite *test_suite(void) {
  Suite *s = suite_create(" ");
  TCase *tc_nothing = tcase_create(" ");
  tcase_add_test(tc_nothing, nothing);
  suite_add_tcase(s, tc_nothing);
  return s;
}