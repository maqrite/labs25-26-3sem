#ifndef ACTIONS_H
#define ACTIONS_H

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
  OK = 0,
  INVALID_NUMBER_OF_ARGS = 1,
  FLAG_ERROR = 2,
  EPSILON_PARSE_ERROR = 3,
  OPTION_ERROR = 4,

} StatusCode;

typedef struct {
  double epsilon;
  char option;
} UserInput;

void PrintErrors(StatusCode status);
double funcA(double x);
double funcB(double x);
double funcC(double x);
double funcD(double x);
StatusCode InputParse(UserInput *input, char *argv[], int argc);
StatusCode calculateIntegral(double a, double b, double epsilon,
                             double (*f)(double), double *result);
StatusCode forA(UserInput *input, double *answer);
StatusCode forB(UserInput *input, double *answer);
StatusCode forC(UserInput *input, double *answer);
StatusCode forD(UserInput *input, double *answer);

#endif
