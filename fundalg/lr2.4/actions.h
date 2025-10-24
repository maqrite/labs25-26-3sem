#ifndef ACTIONS_H
#define ACTIONS_H

#include <ctype.h>
#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef enum {
  OK = 0,
  INVALID_INPUT = 1,
  MEMORY_ALLOCATION_ERROR = 2,
  INVALID_PARAMETER = 3,
} StatusCode;

void printErrors(StatusCode status);

int getRomanValue(char c);
StatusCode convertFromRoman(const char *numStr, int *result);

StatusCode convertFromZeck(const char *zeckStr, unsigned int *result);

int getCharValue(char c, bool uppercase);
int getCharValueIns(char c);
StatusCode convertFromBase(const char *numStr, int base, bool uppercase,
                           long long *result);

StatusCode parseInt(const char *token, int base, long long *result);
StatusCode parseDouble(const char *token, double *result);
StatusCode parsePointer(const char *token, void **result);

StatusCode handleToken(const char *token, const char **format, va_list *args,
                       int *assignments);

int oversscanf(const char *str, const char *format, ...);
int overfscanf(FILE *stream, const char *format, ...);

void testAllFlags(void);

#endif
