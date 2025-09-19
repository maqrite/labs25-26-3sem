#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
  OK = 0,
  INVALID_NUMBER_OF_ARGS = 1,
  UNKNOWN_FLAG = 2,
  INVALID_NUMBER_OF_ARGS_FOR_FLAG = 3,
  INVALID_ARGUMENT = 4,
  OVERFLOW_ERROR = 5,

} StatusCode;

void PrintExceptions(StatusCode status);
void PrintQuadSolves(const double epsilon, const double a, const double b,
                     const double c);
StatusCode StringToInt(const char *string, int *value);
StatusCode StringToDouble(const char *string, double *value);
StatusCode SolveQuadEquation(const double epsilon, const double a,
                             const double b, const double c, double *x1,
                             double *x2, int *rootsAmount);
bool CheckMultiplicity(const int number1, const int number2);
bool CheckRightTriangle(const double epsilon, const double a, const double b,
                        const double c);
bool IsTriangle(const double a, const double b, const double c);
bool CheckPifagor(const double eps, const double a, const double b,
                  const double c);
