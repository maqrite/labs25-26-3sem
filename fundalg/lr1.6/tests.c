// File: tests.c
#include "actions.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>

#define ASSERT_CLOSE(a, b, epsilon)                                            \
  assert(fabs((a) - (b)) < (epsilon) && "Values are not close enough")

void test_InputParse();
void test_math_functions();
void test_calculateIntegral();

int main() {
  test_InputParse();
  test_math_functions();
  test_calculateIntegral();

  printf("All internal tests passed successfully!\n");
  return 0;
}

void test_InputParse() {
  printf("Running tests for InputParse...\n");
  UserInput input;
  StatusCode status;

  char *argv1[] = {"./app", "-e", "0.001", "-a"};
  status = InputParse(&input, argv1, 4);
  assert(status == OK && input.option == 'a' &&
         fabs(input.epsilon - 0.001) < 1e-9);

  char *argv2[] = {"./app", "-b", "-e", "0.01"};
  status = InputParse(&input, argv2, 4);
  assert(status == OK && input.option == 'b' &&
         fabs(input.epsilon - 0.01) < 1e-9);

  // Ошибки
  char *argv_err1[] = {"./app", "-e"};
  assert(InputParse(&input, argv_err1, 2) == EPSILON_PARSE_ERROR);

  char *argv_err2[] = {"./app", "-e", "-0.1", "-a"};
  assert(InputParse(&input, argv_err2, 4) == EPSILON_PARSE_ERROR);

  char *argv_err3[] = {"./app", "-e", "0.01"};
  assert(InputParse(&input, argv_err3, 3) == OK && input.option == 0);

  char *argv_err4[] = {"./app", "-x", "-e", "0.01"};
  assert(InputParse(&input, argv_err4, 4) == FLAG_ERROR);

  char *argv_err5[] = {"./app", "-a", "-b", "-e", "0.01"};
  assert(InputParse(&input, argv_err5, 5) == OPTION_ERROR);
}

void test_math_functions() {
  printf("Running tests for math functions...\n");
  ASSERT_CLOSE(funcA(0.0), 1.0, 1e-9);
  ASSERT_CLOSE(funcB(0.0), 1.0, 1e-9);
  ASSERT_CLOSE(funcC(0.0), 0.0, 1e-9);
  ASSERT_CLOSE(funcD(0.0), 1.0, 1e-9);
}

double linear_func(double x) { return 2.0 * x; }

void test_calculateIntegral() {
  printf("Running tests for calculateIntegral...\n");
  double result;
  StatusCode status = calculateIntegral(0.0, 1.0, 0.0001, linear_func, &result);
  assert(status == OK);
  ASSERT_CLOSE(result, 1.0, 0.0001);
}
