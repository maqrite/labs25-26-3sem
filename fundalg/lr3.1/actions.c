#include "actions.h"
#include <limits.h>
#include <stdio.h>

void printErrors(StatusCode status) {
  switch (status) {

  case INVALID_INPUT:
    printf("неверный ввод\n");
    break;

  case INVALID_ARGS:
    printf("переданы неверные аргументы\n");
    break;

  case BUFFER_TOO_SMALL:
    printf("слишком маленький буффер\n");
    break;

  default:
    break;
  }
}

StatusCode convertToBase2r(const unsigned int nIn, const int r, char *buffer,
                           const size_t bufferSize) {

  if (r < 1 || r > 5 || buffer == NULL) {
    return INVALID_ARGS;
  }

  const size_t bits = sizeof(unsigned int) * CHAR_BIT;
  const size_t requiredDigits = (bits + r - 1) / r;
  const size_t minBufferSize = requiredDigits + 1;

  if (bufferSize < minBufferSize) {
    return BUFFER_TOO_SMALL;
  }

  const char *DIGITS_MAP = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

  unsigned int n = nIn;
  int i = 0;

  const unsigned int mask = ~((~0U) << r);

  if (n == 0) {
    buffer[i++] = '\0';
    buffer[i] = '\0';
    return OK;
  }

  while (n != 0) {
    unsigned int digit = n & mask;

    buffer[i] = DIGITS_MAP[digit];

    i++;

    n = n >> r;
  }

  buffer[i] = '\0';

  reverseString(buffer, i);

  return OK;
}
