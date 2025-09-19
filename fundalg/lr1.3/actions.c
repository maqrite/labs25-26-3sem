#include "actions.h"

void PrintExceptions(StatusCode status) {
  switch (status) {
  case INVALID_NUMBER_OF_ARGS:
    printf("Недопустимое количество аргументов\n");
    break;

  case UNKNOWN_FLAG:
    printf("Передан неизвестный флаг\n");
    break;

  case INVALID_NUMBER_OF_ARGS_FOR_FLAG:
    printf("Недопустимое количество аргументов для флага\n");
    break;

  case INVALID_ARGUMENT:
    printf("Неверный формат числового аргумента\n");
    break;

  case OVERFLOW_ERROR:
    printf("Переполнение типа\n");
    break;

  default:
    break;
  }
}

StatusCode StringToInt(const char *string, int *value) {
  const int base = 10;
  char *pEnd;

  if (string == NULL || *string == '\0') {
    return INVALID_ARGUMENT;
  }

  const long lvalue = strtol(string, &pEnd, base);

  if (string == pEnd) {
    return INVALID_ARGUMENT;
  }

  while (isspace((unsigned char)*pEnd)) {
    ++pEnd;
  }
  if (*pEnd != '\0') {
    return INVALID_ARGUMENT;
  }

  if (lvalue < INT_MIN || lvalue > INT_MAX) {
    return OVERFLOW_ERROR;
  }

  *value = (int)lvalue;

  return OK;
}

StatusCode StringToDouble(const char *string, double *value) {
  char *pEnd;

  if (string == NULL || *string == '\0') {
    return INVALID_ARGUMENT;
  }

  const double dvalue = strtod(string, &pEnd);

  if (string == pEnd) {
    return INVALID_ARGUMENT;
  }

  while (isspace((unsigned char)*pEnd)) {
    ++pEnd;
  }
  if (*pEnd != '\0') {
    return INVALID_ARGUMENT;
  }

  *value = dvalue;

  return OK;
}

bool CheckMultiplicity(const int number1, const int number2) {
  if (number2 == 0) {
    return false;
  }
  return (number1 % number2 == 0);
}

bool IsTriangle(const double a, const double b, const double c) {
  return (a + b > c && a + c > b && b + c > a);
}

bool CheckPifagor(const double eps, const double a, const double b,
                  const double c) {
  bool check1 = fabs(a * a + b * b - c * c) < eps;
  bool check2 = fabs(a * a + c * c - b * b) < eps;
  bool check3 = fabs(b * b + c * c - a * a) < eps;
  return check1 || check2 || check3;
}

bool CheckRightTriangle(const double epsilon, const double a, const double b,
                        const double c) {
  if (a <= 0 || b <= 0 || c <= 0) {
    return false;
  }

  if (!IsTriangle(a, b, c)) {
    return false;
  }

  if (!CheckPifagor(epsilon, a, b, c)) {
    return false;
  }

  return true;
}

StatusCode SolveQuadEquation(const double epsilon, const double a,
                             const double b, const double c, double *x1,
                             double *x2, int *rootsAmount) {

  if (fabs(a) < epsilon) {
    if (fabs(b) < epsilon) {
      *rootsAmount = 0;
    } else {
      *x1 = -c / b;
      *rootsAmount = 1;
    }
    return OK;
  }

  const double discriminant = b * b - 4 * a * c;

  if (discriminant > epsilon) {
    const double sqrtDiscriminant = sqrt(discriminant);
    *x1 = (-b + sqrtDiscriminant) / (2 * a);
    *x2 = (-b - sqrtDiscriminant) / (2 * a);
    *rootsAmount = 2;
  } else if (fabs(discriminant) < epsilon) {
    *x1 = -b / (2 * a);
    *rootsAmount = 1;
  } else {
    *rootsAmount = 0;
  }

  return OK;
}

void SolveAndAddRoots(const double epsilon, const double a, const double b,
                      const double c, double allRoots[], int *rootsCount) {
  double x1, x2;
  int rootsAmount;

  SolveQuadEquation(epsilon, a, b, c, &x1, &x2, &rootsAmount);

  switch (rootsAmount) {
  case 1:
    allRoots[(*rootsCount)++] = x1;
    break;

  case 2:
    allRoots[(*rootsCount)++] = x1;
    allRoots[(*rootsCount)++] = x2;
    break;

  case 0:
    break;
  }
}

void PrintQuadSolves(const double epsilon, const double a, const double b,
                     const double c) {
  double allRoots[12];
  int rootsCount = 0;

  SolveAndAddRoots(epsilon, a, b, c, allRoots, &rootsCount);
  SolveAndAddRoots(epsilon, a, c, b, allRoots, &rootsCount);
  SolveAndAddRoots(epsilon, b, a, c, allRoots, &rootsCount);
  SolveAndAddRoots(epsilon, b, c, a, allRoots, &rootsCount);
  SolveAndAddRoots(epsilon, c, a, b, allRoots, &rootsCount);
  SolveAndAddRoots(epsilon, c, b, a, allRoots, &rootsCount);

  double uniqueRoots[12];
  int uniqueCount = 0;

  for (int i = 0; i < rootsCount; ++i) {
    bool isDuplicate = false;
    for (int j = 0; j < uniqueCount; ++j) {
      if (fabs(allRoots[i] - uniqueRoots[j]) < epsilon) {
        isDuplicate = true;
        break;
      }
    }
    if (!isDuplicate) {
      uniqueRoots[uniqueCount++] = allRoots[i];
    }
  }
  if (uniqueCount == 0) {
    printf("Действительных корней не найдено ни для одной перестановки\n");
  } else {
    printf("Уникальные корни для всех перестановок:\n");
    for (int i = 0; i < uniqueCount; ++i) {
      printf("x%d = %f\n", i + 1, uniqueRoots[i]);
    }
  }
  return;
}
