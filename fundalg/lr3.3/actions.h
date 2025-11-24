#ifndef ACTIONS_H
#define ACTIONS_H

#include <stdio.h>

typedef enum {
  OK = 0,
  INVALID_INPUT = 1,
  MEMORY_ALLOC_ERROR = 2,
  EMPTY_LIST_ERROR = 3,
  INDEX_OUT_OF_BOUNDS = 4,
} StatusCode;

void printErrors(StatusCode status);

#endif
