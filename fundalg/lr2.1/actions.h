#ifndef ACTIONS_H
#define ACTIONS_H

#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>

typedef enum {
  OK = 0,
  INVALID_NUMBER_OF_ARGS = 1,
  INVALID_INPUT = 2,
  INVALID_BASE = 3,
  INVALID_FRACTION = 4,
} StatusCode;

void printErrors(StatusCode status);
void demonstrateFunction(void);

bool hasFinReprImpl(double fraction, const int base, const double epsilon);
StatusCode checkFinRepres(bool results[], const int base, int count, ...);

#endif
