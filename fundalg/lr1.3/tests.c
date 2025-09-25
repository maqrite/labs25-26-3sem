#include "actions.h"
#include <assert.h>
#include <stdio.h>

void test_StringToInt();
void test_StringToDouble();
void test_CheckMultiplicity();
void test_CheckRightTriangle();
void test_SolveQuadEquation();

int main() {
  test_StringToInt();
  test_StringToDouble();
  test_CheckMultiplicity();
  test_CheckRightTriangle();
  test_SolveQuadEquation();

  printf("All internal tests passed successfully!\n");
  return 0;
}

void test_StringToInt() {
  printf("Running tests for StringToInt...\n");
  int value;
  assert(StringToInt("123", &value) == OK && value == 123);
  assert(StringToInt("-45", &value) == OK && value == -45);
  assert(StringToInt("0", &value) == OK && value == 0);
  assert(StringToInt("  50  ", &value) == OK && value == 50);
  assert(StringToInt("abc", &value) == INVALID_ARGUMENT);
  assert(StringToInt("12x", &value) == INVALID_ARGUMENT);
  assert(StringToInt("", &value) == INVALID_ARGUMENT);
  assert(StringToInt("2147483648", &value) == OVERFLOW_ERROR);
}

void test_StringToDouble() {
  printf("Running tests for StringToDouble...\n");
  double value;
  assert(StringToDouble("123.45", &value) == OK && fabs(value - 123.45) < 1e-9);
  assert(StringToDouble("-0.5", &value) == OK && fabs(value - (-0.5)) < 1e-9);
  assert(StringToDouble("  1.2e3  ", &value) == OK &&
         fabs(value - 1200.0) < 1e-9);
  assert(StringToDouble("xyz", &value) == INVALID_ARGUMENT);
}

void test_CheckMultiplicity() {
  printf("Running tests for CheckMultiplicity...\n");
  assert(CheckMultiplicity(10, 5) == true);
  assert(CheckMultiplicity(10, 3) == false);
  assert(CheckMultiplicity(0, 7) == true);
  assert(CheckMultiplicity(10, 0) == false);
}

void test_CheckRightTriangle() {
  printf("Running tests for CheckRightTriangle...\n");
  const double eps = 0.001;
  assert(CheckRightTriangle(eps, 3, 4, 5) == true);
  assert(CheckRightTriangle(eps, 5, 3, 4) == true);
  assert(CheckRightTriangle(eps, 3, 4, 6) == false);
  assert(CheckRightTriangle(eps, 1, 1, 10) == false);
  assert(CheckRightTriangle(eps, 3, 4, -5) == false);
}

void test_SolveQuadEquation() {
  printf("Running tests for SolveQuadEquation...\n");
  const double eps = 0.001;
  double x1, x2;
  int rootsAmount;

  SolveQuadEquation(eps, 1, -3, 2, &x1, &x2, &rootsAmount);
  assert(rootsAmount == 2);

  SolveQuadEquation(eps, 1, -2, 1, &x1, &x2, &rootsAmount);
  assert(rootsAmount == 1 && fabs(x1 - 1.0) < eps);

  SolveQuadEquation(eps, 1, 1, 1, &x1, &x2, &rootsAmount);
  assert(rootsAmount == 0);

  SolveQuadEquation(eps, 0, 2, -4, &x1, &x2, &rootsAmount);
  assert(rootsAmount == 1 && fabs(x1 - 2.0) < eps);
}
