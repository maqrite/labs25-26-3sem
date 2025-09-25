#ifndef ACTIONS_H
#define ACTIONS_H

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char option;
  bool isN;
} InputFlag;

typedef enum {
  OK = 0,
  INVALID_NUMBER_OF_ARGS = 1,
  FLAG_ERROR = 2,
  MEMORY_ALLOC_ERROR = 3,
  FILE_OPEN_ERROR = 4,

} StatusCode;

void PrintExceptions(StatusCode status);
StatusCode FlagParse(InputFlag *flag, char *argv[], int argc);
StatusCode forD(const char *input, char *output[]);
StatusCode forI(const char *input, char *output[]);
StatusCode forS(const char *input, char *output[]);
StatusCode forA(const char *input, char *output[]);

#endif
