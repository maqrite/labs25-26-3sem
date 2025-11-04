#include "actions.h"

void printErrors(StatusCode status) {
  switch (status) {

  case INVALID_INPUT:
    printf("ошибка, неверный ввод\n");
    break;

  default:
    break;
  }
}
