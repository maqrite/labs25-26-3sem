#include "actions.h"
#include <stdbool.h>

#define maxIterations 100
#define defaultEpsilon 0.000000001

void printErrors(StatusCode status) {
  switch (status) {
  case INVALID_NUMBER_OF_ARGS:
    printf("Недопустимое количество аргументов\n");
    break;

  case INVALID_INPUT:
    printf("передано некорректное число\n");
    break;

  case INVALID_BASE:
    printf("некорректное основание с/с\n");
    break;

  case INVALID_FRACTION:
    printf("Дробь должна быть в диапазоне от (0, 1)\n");
    break;

  default:
    break;
  }
}

bool hasFinReprImpl(double fraction, const int base, const double epsilon) {
  double history[maxIterations];
  int historyCounter = 0;

  for (int i = 0; i < maxIterations; i++) {

    fraction *= base;

    if (fabs(fraction - round(fraction)) < epsilon) {
      return true;
    }

    fraction -= floor(fraction);

    if (fraction < epsilon) {
      return true;
    }

    for (int j = 0; j < historyCounter; j++) {

      if (fabs(history[j] - fraction) < epsilon) {
        return false;
      }
    }

    if (historyCounter < maxIterations) {
      historyCounter++;
      history[historyCounter] = fraction;
    }
  }

  return false;
}

StatusCode checkFinRepres(bool *results, const int base, int count, ...) {

  if (base <= 1) {
    return INVALID_BASE;
  }

  va_list args;
  va_start(args, count);

  for (int i = 0; i < count; i++) {
    double currentDouble = va_arg(args, double);

    if (currentDouble <= 0 || currentDouble >= 1) {
      va_end(args);

      return INVALID_FRACTION;
    }

    results[i] = hasFinReprImpl(currentDouble, base, defaultEpsilon);
  }

  va_end(args);

  return OK;
}

void demonstrateFunction(void) {

  int base1 = 10;
  double d11 = 0.5;
  double d12 = 0.12321;
  double d13 = 1.0 / 3.0;
  int count1 = 3;
  bool results1[count1];

  printf("Проверка для основания %d:\n", base1);
  StatusCode status = checkFinRepres(results1, base1, count1, d11, d12, d13);

  if (status == OK) {
    printf("  %.10f -> %s\n", d11, results1[0] ? "Конечное" : "Бесконечное");
    printf("  %.10f -> %s\n", d12, results1[1] ? "Конечное" : "Бесконечное");
    printf("  %.10f -> %s\n", d13, results1[2] ? "Конечное" : "Бесконечное");
  } else {
    printErrors(status);
  }
}
