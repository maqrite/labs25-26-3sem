#include "actions.h"

void printErrors(StatusCode status) {
  switch (status) {

  case INVALID_INPUT:
    printf("неверный ввод\n");
    break;

  case MEMORY_ALLOC_ERROR:
    printf("ошибка выделения памяти\n");
    break;

  case EMPTY_LIST_ERROR:
    printf("список пуст\n");
    break;

  case INDEX_OUT_OF_BOUNDS:
    printf("выход за пределы (индекс вне диапазона)\n");
    break;

  default:
    break;
  }
}
