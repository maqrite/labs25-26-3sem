#ifndef ACTIONS_H
#define ACTIONS_H

#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
  OK = 0,
  INVALID_INPUT = 1,
  MEMORY_ALLOCATION_ERROR = 2,
  INVALID_PARAMETER = 3,
} StatusCode;

void printErrors(StatusCode status);

int overfprintf(FILE *stream, const char *format, ...);
int oversprintf(char *str, const char *format, ...);

StatusCode convertToRoman(int num, char **resultStr);
StatusCode zeckendorfRepr(unsigned int n, char **resultStr);

void reverseString(char *str);
StatusCode convertToBase(long long num, int base, bool uppercase,
                         char **resultStr);

int getCharValue(char c);
StatusCode convertFromBase(const char *numStr, int base, long long *result);

StatusCode dumpMemory(const void *data, size_t size, char **resultStr);

StatusCode convertDoubleToString(double num, char **resultStr);

void testAllFlags(void);
#endif
