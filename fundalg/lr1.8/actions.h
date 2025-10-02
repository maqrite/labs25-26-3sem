#ifndef ACTIONS_H
#define ACTIONS_H

#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
  OK = 0,
  INVALID_NUMBER_OF_ARGS = 1,
  INVALID_INPUT = 2,
  INVALID_BASE = 3,
  INVALID_NUMBER_FORMAT = 4,
  MEMORY_ALLOCATION_ERROR = 5,
  OVERFLOW = 6,
  NO_VALID_NUMBERS_ENTERED = 7,
  NULL_ARGUMENT = 8,
} StatusCode;

void PrintErrors(StatusCode status);
StatusCode charToDigit(char c, int *digit);
StatusCode readAndValidateBase(int *base);
StatusCode toLongLong(const char *s, int base, long long *result);
StatusCode fromLongLong(long long number, int base, char *resultStr[]);
StatusCode reverseString(char *str);

#endif
