#ifndef ACTIONS_H
#define ACTIONS_H

#include <stdarg.h>
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
StatusCode convert_to_base(long long num, int base, bool uppercase,
                           char **result_str);

#endif
