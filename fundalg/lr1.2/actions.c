#include "actions.h"

void printExceptions(const StatusCode status) {
  switch (status) {

  case INCORRECT_NUMBER_OF_STRINGS:
    printf("Недопустимое количество строк или введено не число\n");
    break;

  case STRING_READ_ERROR:
    printf("Ошибка чтения строки\n");
    break;

  case INCORRECT_NUMBER_IN_STRING:
    printf("Недопустимое число в строке или введено не число\n");
    break;

  default:
    break;
  }

  return;
}

bool isPrime(const long long int x) {
  long int i = 0;
  if (x == 1) {
    return false;
  }
  if (x <= 3) {
    return true;
  }
  if (x % 2 == 0 || x % 3 == 0) {
    return false;
  }
  for (i = 5; i * i <= x; i = i + 6) {
    if (x % i == 0 || x % (i + 2) == 0) {
      return false;
    }
  }
  return true;
}

StatusCode findPrimeBasedOnSequenceNumber(const int n, long long int *answer) {
  if (n <= 0) {
    return INCORRECT_NUMBER_IN_STRING;
  }

  if (n == 1) {
    *answer = 2;
    return OK;
  }

  int counter = 1;
  long long int number = 3;
  while (counter < n) {
    if (isPrime(number)) {
      ++counter;
    }
    if (counter == n) {
      *answer = number;
      return OK;
    }
    number += 2;
  }
  return INCORRECT_NUMBER_IN_STRING;
}
