#ifndef ACTIONS_H
#define ACTIONS_H

#include <stdio.h>

typedef enum {
  OK = 0,
  INVALID_INPUT = 1,
  INVALID_ARGS = 2,
  BUFFER_TOO_SMALL = 3,
} StatusCode;

void printErrors(StatusCode status);

StatusCode convertToBase2r(const unsigned int n, const int r, char *buffer,
                           const size_t bufferSize);

#endif
