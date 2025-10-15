#include "actions.h"
#include <stdbool.h>

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

long long gcd(long long a, long long b) {
  while (b) {
    a %= b;
    long long temp = a;
    a = b;
    b = temp;
  }
  return a;
}

bool hasFinReprImpl(double fraction, const int base) {
  const long long maxDenominator = 1000000000000000LL;
  long long denominator = 1;

  while (fabs(fraction * denominator - (long long)(fraction * denominator)) >
             1e-9 &&
         denominator < maxDenominator) {
    denominator *= 10;
  }

  long long numerator = (long long)(fraction * denominator);

  if (numerator == 0) {
    return true;
  }

  long long commonDivisor = gcd(numerator, denominator);
  long long q = denominator / commonDivisor;

  while (q > 1) {
    long long commonFactor = gcd(q, (long long)base);

    if (commonFactor == 1) {
      return false;
    }

    while (q % commonFactor == 0) {
      q /= commonFactor;
    }
  }

  return true;
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

    results[i] = hasFinReprImpl(currentDouble, base);
  }

  va_end(args);

  return OK;
}

void demonstrateFunction(void) {
  int base1 = 10;
  double d11 = 0.5;
  double d12 = 0.125;
  double d13 = 1.0 / 3.0;
  int count1 = 3;
  bool results1[count1];

  printf("Проверка для основания %d:\n", base1);
  StatusCode status1 = checkFinRepres(results1, base1, count1, d11, d12, d13);

  if (status1 == OK) {
    printf("  %.10f -> %s\n", d11, results1[0] ? "Конечное" : "Бесконечное");
    printf("  %.10f -> %s\n", d12, results1[1] ? "Конечное" : "Бесконечное");
    printf("  %.10f -> %s\n", d13, results1[2] ? "Конечное" : "Бесконечное");
  } else {
    printErrors(status1);
  }
  printf("\n");

  int base2 = 3;
  double d21 = 1.0 / 3.0;
  double d22 = 1.0 / 2.0;
  double d23 = 4.0 / 9.0;
  int count2 = 3;
  bool results2[count2];

  printf("Проверка для основания %d:\n", base2);
  StatusCode status2 = checkFinRepres(results2, base2, count2, d21, d22, d23);

  if (status2 == OK) {
    printf("  %.10f -> %s\n", d21, results2[0] ? "Конечное" : "Бесконечное");
    printf("  %.10f -> %s\n", d22, results2[1] ? "Конечное" : "Бесконечное");
    printf("  %.10f -> %s\n", d23, results2[2] ? "Конечное" : "Бесконечное");
  } else {
    printErrors(status2);
  }
}
