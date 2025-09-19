#ifndef ACTIONS_H
#define ACTIONS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
  OK = 0,
  INVALID_NUMBER_OF_ARGS = 1,
  UNKNOWN_FLAG = 2,
  INCORRECT_NUMBER = 3,
  INCORRECT_NUMBER_FOR_FLAG = 4,
} StatusCode;

long int StringToNumber(const char *string, char **endptr, int base);
long long CalculateSum(const long int x);
long long Factorial(const long int x);
bool IsPrime(const long int x);
bool FlagFirstElementCheck(const char element);
void PrintMultiples(const long int x);
void PrintHexDigits(const long int x);
void PrintPowersTable(const long int x);
void PrintExceptions(const StatusCode status);

#endif
