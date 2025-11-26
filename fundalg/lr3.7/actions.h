#ifndef ACTIONS_H
#define ACTIONS_H

#include <stdbool.h>
#include <stdio.h>

typedef enum {
  OK = 0,
  INVALID_INPUT = 1,
  MEMORY_ALLOC_ERROR = 2,
  FILE_OPEN_ERROR = 3,
  UNEXPECTED_TOKEN = 4,
  INVALID_VARIABLE_NAME = 5,
  DIVISION_BY_ZERO = 6,
  UNKNOWN_COMMAND = 7,
} StatusCode;

void printErrors(StatusCode status);

#endif
