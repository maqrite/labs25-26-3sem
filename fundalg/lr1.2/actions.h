#include <stdbool.h>
#include <stdio.h>

typedef enum {
  OK = 0,
  INCORRECT_NUMBER_OF_STRINGS = 1,
  STRING_READ_ERROR = 2,
  INCORRECT_NUMBER_IN_STRING = 3,
} StatusCode;

void printExceptions(const StatusCode status);
StatusCode findPrimeBasedOnSequenceNumber(const int n, long long int *answer);
bool isPrime(const long long int n);
