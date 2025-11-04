#ifndef ACTIONS_H
#define ACTIONS_H

#include <limits.h>
#include <stdio.h>

typedef enum {
  OK = 0,
  INVALID_INPUT = 1,
  INVALID_ARGS = 2,
  BUFFER_TOO_SMALL = 3,
} StatusCode;

void printErrors(StatusCode status);

void reverseString(char *str, int len);

StatusCode convertToBase2r(const unsigned int nIn, const int r, char *buffer,
                           const size_t bufferSize);

#endif
