#include "actions.h"

void printErrors(StatusCode status) {
  switch (status) {

  case INVALID_INPUT:
    printf("неверный ввод\n");
    break;

  case MEMORY_ALLOC_ERROR:
    printf("ошибка выделения памяти\n");
    break;

  case UNEXPECTED_TOKEN:
    printf("неожиданный токен\n");
    break;

  case INVALID_VARIABLE_NAME:
    printf("некорректное имя для переменной\n");
    break;

  case DIVISION_BY_ZERO:
    printf("деление на ноль\n");
    break;

  case UNKNOWN_COMMAND:
    printf("неизвестная команда\n");
    break;

  default:
    break;
  }
}
