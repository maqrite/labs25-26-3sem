#include "actions.h"
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

StatusCode convertToBase2r(const unsigned int n, const int r, char *buffer,
                           const size_t bufferSize) {

  if (r < 1 || r > 5 || buffer == NULL) {
    return INVALID_ARGS;
  }

  return OK;
}
