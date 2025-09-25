#include "actions.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>

#define ASSERT_CLOSE(a, b, epsilon)                                            \
  assert(fabs((a) - (b)) < (epsilon) && "Values are not close enough")

void test_stringToDouble();
void test_calculations();

int main() {
  test_stringToDouble();
  test_calculations();

  printf("All internal tests passed successfully!\n");
  return 0;
}

void test_stringToDouble() {
  printf("Running tests for stringToDouble...\n");
  double value;
  assert(stringToDouble("123.45", &value) == OK);
  ASSERT_CLOSE(value, 123.45, 1e-9);

  assert(stringToDouble("-0.5", &value) == OK);
  ASSERT_CLOSE(value, -0.5, 1e-9);

  assert(stringToDouble("1.2e3", &value) == OK);
  ASSERT_CLOSE(value, 1200.0, 1e-9);

  assert(stringToDouble("xyz", &value) == INVALID_ARGUMENT);
  assert(stringToDouble("", &value) == INVALID_ARGUMENT);
  assert(stringToDouble("3.14a", &value) == INVALID_ARGUMENT);
}

void test_calculations() {
  printf("Running tests for calculation functions...\n");
  const double epsilon = 0.01;

  const double M_E_VAL = M_E;
  const double M_PI_VAL = M_PI;
  const double M_LN2_VAL = M_LN2;
  const double M_SQRT2_VAL = M_SQRT2;
  const double EULER_GAMMA = 0.5772156649;

  ASSERT_CLOSE(calculateExpSeries(epsilon), M_E_VAL, epsilon);
  ASSERT_CLOSE(calculateExpLimit(epsilon), M_E_VAL, epsilon * 100);
  ASSERT_CLOSE(calculateExpEquation(epsilon), M_E_VAL, epsilon);

  ASSERT_CLOSE(calculatePiSeries(epsilon), M_PI_VAL, epsilon * 10);
  ASSERT_CLOSE(calculatePiLimit(epsilon), M_PI_VAL, epsilon * 100);
  ASSERT_CLOSE(calculatePiEquation(epsilon), M_PI_VAL, epsilon);

  ASSERT_CLOSE(calculateLn2Series(epsilon), M_LN2_VAL, epsilon);
  ASSERT_CLOSE(calculateLn2Limit(epsilon), M_LN2_VAL, epsilon * 10);
  ASSERT_CLOSE(calculateLn2Equation(epsilon), M_LN2_VAL, epsilon);

  ASSERT_CLOSE(calculateSqrt2Series(epsilon), M_SQRT2_VAL, epsilon * 10);
  ASSERT_CLOSE(calculateSqrt2Limit(epsilon), M_SQRT2_VAL, epsilon);
  ASSERT_CLOSE(calculateSqrt2Equation(epsilon), M_SQRT2_VAL, epsilon);

  ASSERT_CLOSE(calculateGammaSeries(epsilon), EULER_GAMMA, epsilon * 1000);
  ASSERT_CLOSE(calculateGammaLimit(epsilon), EULER_GAMMA, epsilon * 1000);
  ASSERT_CLOSE(calculateGammaEquation(epsilon), EULER_GAMMA, epsilon * 1000);
}
