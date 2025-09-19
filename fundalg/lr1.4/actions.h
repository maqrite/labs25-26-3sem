#ifndef ACTIONS_H
#define ACTIONS_H

#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
  OK = 0,
  INVALID_ARGUMENT = 1,
  INVALID_NUMBER_OF_ARGS = 2,
  FLAG_ERROR = 3,
  CALCULATION_ERROR = 4,
} StatusCode;

typedef struct {
  char *constName;
  char *methodName;
  double epsilon;
  bool constProvided;
  bool methodProvided;
  bool epsilonProvided;
} Input;

bool *sieveOfEratosthenes(int limit);
void printExceptions(const StatusCode status);
double nlog(const double x, const double epsilon);
double nlogFactorial(const int x, const double epsilon);
double calculatePiSeries(const double epsilon);
double calculatePiLimit(const double epsilon);
double calculatePiEquation(const double epsilon);
double calculateExpSeries(const double epsilon);
double calculateExpLimit(const double epsilon);
double calculateExpEquation(const double epsilon);
double calculateLn2Series(const double epsilon);
double calculateLn2Limit(const double epsilon);
double calculateLn2Equation(const double epsilon);
double calculateSqrt2Series(const double epsilon);
double calculateSqrt2Limit(const double epsilon);
double calculateSqrt2Equation(const double epsilon);
double calculateGammaSeries(const double epsilon);
double calculateGammaLimit(const double epsilon);
double calculateMertensLimit(const double epsilon);
double calculateGammaEquation(const double epsilon);
StatusCode stringToDouble(const char *string, double *value);

#endif
