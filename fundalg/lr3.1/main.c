#include "actions.h"

int main(void) {
  unsigned int number;
  int r;
  StatusCode status = OK;

  printf("Введите десятичное число: ");

  if (scanf("%u", &number) != 1) {
    status = INVALID_INPUT;
    printErrors(status);
    return status;
  }

  printf("Введите степень r (1-5) для 2^r: ");

  if (scanf("%d", &r) != 1) {
    status = INVALID_INPUT;
    printErrors(status);
    return status;
  }

  char resultBuffer[(sizeof(unsigned int) * CHAR_BIT) + 1];

  status = convertToBase2r(number, r, resultBuffer, sizeof(resultBuffer));

  if (status == OK) {
    printf("число %u (основание 10)\n", number);
    printf("число %s (основание 2^%d = %d)\n", resultBuffer, r, (1 << r));
  } else {
    printErrors(status);
  }

  return status;
}
