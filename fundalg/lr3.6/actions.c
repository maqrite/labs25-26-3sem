#include "actions.h"

void printErrors(StatusCode status) {
  switch (status) {

  case INVALID_INPUT:
    printf("неверный ввод\n");
    break;

  case MEMORY_ALLOC_ERROR:
    printf("ошибка выделения памяти\n");
    break;

  default:
    break;
  }
}
