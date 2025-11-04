#ifndef ACTIONS_H
#define ACTIONS_H

#include <stdio.h>

typedef enum {
  OK = 0,
  INVALID_INPUT = 1,
} StatusCode;

void printErrors(StatusCode status);

#endif
