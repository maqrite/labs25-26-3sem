// File: tests.c
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include "actions.h"

void test_isPrime();
void test_findPrimeBasedOnSequenceNumber();

int main() {

  test_isPrime();
  test_findPrimeBasedOnSequenceNumber();

  printf("All tests passed successfully!\n");
  return 0;
}

void test_isPrime() {
  printf("Running tests for isPrime...\n");

  assert(isPrime(2) == true);
  assert(isPrime(3) == true);
  assert(isPrime(5) == true);
  assert(isPrime(7) == true);
  assert(isPrime(97) == true);
  assert(isPrime(541) == true);

  assert(isPrime(1) == false);
  assert(isPrime(4) == false);
  assert(isPrime(9) == false);
  assert(isPrime(25) == false);
  assert(isPrime(100) == false);
}

void test_findPrimeBasedOnSequenceNumber() {
  printf("Running tests for findPrimeBasedOnSequenceNumber...\n");
  long long int answer;
  StatusCode status;

  status = findPrimeBasedOnSequenceNumber(1, &answer);
  assert(status == OK && answer == 2);

  status = findPrimeBasedOnSequenceNumber(2, &answer);
  assert(status == OK && answer == 3);

  status = findPrimeBasedOnSequenceNumber(3, &answer);
  assert(status == OK && answer == 5);

  status = findPrimeBasedOnSequenceNumber(10, &answer);
  assert(status == OK && answer == 29);

  status = findPrimeBasedOnSequenceNumber(100, &answer);
  assert(status == OK && answer == 541);

  status = findPrimeBasedOnSequenceNumber(0, &answer);
  assert(status == INCORRECT_NUMBER_IN_STRING);

  status = findPrimeBasedOnSequenceNumber(-5, &answer);
  assert(status == INCORRECT_NUMBER_IN_STRING);
}
