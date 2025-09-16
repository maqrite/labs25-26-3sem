#ifndef ACTIONS_H
#define ACTIONS_H

#include <stdbool.h>

typedef enum {
  OK = 0,
  INVALID_NUMBER_OF_ARGS = 1,
  UNKNOWN_FLAG = 2,
  INCORRECT_NUMBER = 3,
  INCORRECT_NUMBER_FOR_FLAG = 4,
} StatusCode;

long int StringToNumber(const char *string, char **endptr, int base);
long long CalculateSum(long int x);
long long Factorial(long int x);
bool IsPrime(long int x);
bool FlagFirstElementCheck(char element);
void PrintMultiples(long int x);
void PrintHexDigits(long int x);
void PrintPowersTable(long int x);
void PrintExceptions(StatusCode status);

#endif
