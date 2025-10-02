#ifndef ACTIONS_H
#define ACTIONS_H

#include <ctype.h>
#include <limits.h>
#include <stdio.h>

typedef enum {
  OK = 0,
  INPUT_FILE_OPEN_ERROR = 1,
  OUTPUT_FILE_OPEN_ERROR = 2,
  INVALID_NUMBER_OF_ARGS = 3,
  INVALID_CHARACTER_IN_NUMBER = 4,
  NUMBER_OVERFLOW = 5,
  NULL_POINTER_ERROR = 6,

} StatusCode;

void PrintErrors(StatusCode status);
StatusCode processFiles(const char *input_path, const char *output_path);
StatusCode processNumber(const char *numberStr, int *outBase,
                         unsigned long long *outValue);
StatusCode getDigitValue(char c, int *out_value);

#endif
