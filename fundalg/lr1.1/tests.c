#include <assert.h>
#include <stdio.h>

#include "actions.h"

void test_CalculateSum();
void test_IsPrime();
void test_Factorial();
void test_FlagFirstElementCheck();

int main() {
  test_CalculateSum();
  test_IsPrime();
  test_Factorial();
  test_FlagFirstElementCheck();

  printf("All tests passed successfully!\n");
  return 0;
}

void test_CalculateSum() {
  printf("Running tests for CalculateSum...\n");
  assert(CalculateSum(1) == 1);      // Сумма до 1
  assert(CalculateSum(5) == 15);     // Сумма до 5 (1+2+3+4+5)
  assert(CalculateSum(10) == 55);    // Сумма до 10
  assert(CalculateSum(100) == 5050); // Сумма до 100
}

void test_IsPrime() {
  printf("Running tests for IsPrime...\n");

  assert(IsPrime(2) == true);
  assert(IsPrime(3) == true);
  assert(IsPrime(5) == true);
  assert(IsPrime(7) == true);
  assert(IsPrime(97) == true);

  assert(IsPrime(1) == false);
  assert(IsPrime(4) == false);
  assert(IsPrime(6) == false);
  assert(IsPrime(9) == false);
  assert(IsPrime(100) == false);
}

void test_Factorial() {
  printf("Running tests for Factorial...\n");
  assert(Factorial(0) == 1);
  assert(Factorial(1) == 1);
  assert(Factorial(5) == 120);
  assert(Factorial(10) == 3628800);
}

void test_FlagFirstElementCheck() {
  printf("Running tests for FlagFirstElementCheck...\n");
  assert(FlagFirstElementCheck('-') == true);
  assert(FlagFirstElementCheck('/') == true);
  assert(FlagFirstElementCheck('a') == false);
  assert(FlagFirstElementCheck('1') == false);
  assert(FlagFirstElementCheck(' ') == false);
}
