#include "actions.h"
#include <math.h>

void printExceptions(const StatusCode status) {
  switch (status) {

  case INVALID_ARGUMENT:
    printf("Недопустимое количество строк или введено не число\n");
    break;

  case INVALID_NUMBER_OF_ARGS:
    printf("Недопустимое количество аргументов\n");
    break;

  case FLAG_ERROR:
    printf("Ошибка передачи флага\n");
    break;

  case CALCULATION_ERROR:
    printf("Ошибка вычисления\n");
    break;

  default:
    break;
  }

  return;
}

StatusCode stringToDouble(const char *string, double *value) {
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

double nlog(const double x, const double epsilon) {
  if (x <= 0) {
    return NAN;
  }

  if (fabs(x - 1.0) < epsilon) {
    return 0.0;
  }

  double u = (x - 1.0) / (x + 1.0);
  double uSquare = u * u;
  double sum = 0.0;
  double currentPowerOfU = u;

  for (int n = 1; n < 30; n += 2) {
    sum += currentPowerOfU / n;
    currentPowerOfU *= uSquare;
  }

  return 2.0 * sum;
}

double calculateExpLimit(const double epsilon) {
  long long n = 1;
  double currentResult = 0.0;
  double previousResult = -1.0;

  while (fabs(currentResult - previousResult) > epsilon) {
    previousResult = currentResult;
    currentResult = pow(1.0 + 1.0 / n, (double)n);
    ++n;
  }

  return currentResult;
}

double calculateExpSeries(const double epsilon) {
  double sum = 1.0;
  double term = 1.0;
  int n = 1;

  while (fabs(term) > epsilon) {
    sum += term;
    ++n;
    term /= n;
  }

  return sum;
}

double calculateExpEquation(const double epsilon) {
  double a = 2.0;
  double b = 3.0;
  double fa = log(a) - 1;

  while (fabs(b - a) > epsilon) {
    double midpoint = (a + b) / 2.0;
    double fmidpoint = nlog(midpoint, epsilon) - 1.0;

    if ((fmidpoint > 0 && fa > 0) || (fmidpoint < 0 && fa < 0)) {
      a = midpoint;
    } else {
      b = midpoint;
    }
  }

  return (a + b) / 2.0;
}

double calculatePiLimit(const double epsilon) {
  double currentPi = 0.0;
  double previousPi = -1.0;
  double sumLogNFact = 0.0;
  double sumLog2nFact = 0.0;
  const double Ln2 = nlog(2.0, epsilon);

  for (long long n = 1; true; ++n) {
    previousPi = currentPi;
    if (n == 1) {
      sumLogNFact = nlog(1.0, epsilon);
      sumLog2nFact = nlog(1.0, epsilon) + nlog(2.0, epsilon);
    } else {
      sumLogNFact += nlog((double)n, epsilon);
      sumLog2nFact +=
          nlog((double)(2 * n - 1), epsilon) + nlog((double)(2 * n), epsilon);
    }

    double logPi = 4 * (n * Ln2 + sumLogNFact) - nlog((double)n, epsilon) -
                   2 * sumLog2nFact;

    currentPi = exp(logPi);

    if (n > 1 && fabs(currentPi - previousPi) < epsilon) {
      break;
    }
  }

  return currentPi;
}

double calculatePiSeries(const double epsilon) {
  double sum = 0.0;
  double sign = 1.0;

  for (long long n = 1; true; ++n) {
    double denominator = 2.0 * n - 1.0;
    double term = sign / denominator;
    if (fabs(term) < epsilon) {
      break;
    }
    sum += term;
    sign *= -1.0;
  }

  return sum * 4.0;
}

double calculatePiEquation(const double epsilon) {
  double currentX = 3.0;
  double previousX = 0.0;

  while (fabs(currentX - previousX) > epsilon) {
    previousX = currentX;
    double fx = cos(previousX) + 1.0;
    double fPrimeX = -sin(previousX);
    if (fabs(fPrimeX) < epsilon) {
      break;
    }
    currentX = previousX - fx / fPrimeX;
  }

  return currentX;
}

double calculateLn2Series(const double epsilon) {
  double sum = 0.0;
  double sign = 1.0;

  for (long long n = 1; true; ++n) {
    double term = sign / n;
    if (fabs(term) < epsilon) {
      break;
    }
    sum += term;
    sign *= -1.0;
  }

  return sum;
}

double calculateLn2Equation(const double epsilon) {
  double a = 0.0;
  double b = 1.0;

  while (fabs(b - a) > epsilon) {
    double midpoint = (a + b) / 2.0;
    double fmidpoint = exp(midpoint) - 2.0;

    if (fmidpoint < 0) {
      a = midpoint;
    } else {
      b = midpoint;
    }
  }

  return (a + b) / 2.0;
}

double calculateLn2Limit(const double epsilon) {
  long long n = 1;
  double currentResult = 0.0;
  double previousResult = -1.0;

  while (fabs(currentResult - previousResult) > epsilon) {
    previousResult = currentResult;
    currentResult = n * (pow(2.0, 1.0 / n) - 1.0);
    ++n;
  }

  return currentResult;
}

double calculateSqrt2Series(const double epsilon) {
  double prod = 1.0;
  double power = 0.25;

  while (1) {
    double term = pow(2.0, power);

    if (fabs(term - 1.0) < epsilon) {
      break;
    }
    prod *= term;
    power /= 2.0;
  }

  return prod;
}

double calculateSqrt2Equation(const double epsilon) {
  double currentX = 1.0;
  double previousX = 0.0;

  while (fabs(currentX - previousX) > epsilon) {
    previousX = currentX;
    currentX = 0.5 * (previousX + 2.0 / previousX);
  }

  return currentX;
}

double calculateSqrt2Limit(const double epsilon) {
  double currentX = -0.5;
  double previousX = 0.0;

  while (fabs(currentX - previousX) > epsilon) {
    previousX = currentX;
    currentX = previousX - (previousX * previousX) / 2.0 + 1.0;
  }

  return currentX;
}

double nlogFactorial(const int x, const double epsilon) {
  double sumLog = 0.0;
  for (int i = 1; i <= x; ++i) {
    sumLog += nlog((double)i, epsilon);
  }

  return sumLog;
}

double calculateGammaSeries(const double epsilon) {
  double pi = calculatePiSeries(epsilon * 100);
  double sum = -(pi * pi) / 6.0;
  double term;

  for (long long k = 2; true; ++k) {
    double kDouble = (double)k;
    double rootKFloor = floor(sqrt(kDouble));
    term = 1.0 / (rootKFloor * rootKFloor) - 1.0 / kDouble;

    if (k > 2 && fabs(term) < epsilon) {
      break;
    }
    sum += term;
  }

  return sum;
}

double calculateGammaLimit(const double epsilon) {
  double currentGamma = 0.0;
  double previousGamma = -1.0;
  for (int m = 1; true; ++m) {
    previousGamma = currentGamma;
    double currentSum = 0.0;
    double mlogFactorial = nlogFactorial(m, epsilon);
    for (int k = 1; k <= m; ++k) {
      double logKfact = nlogFactorial(k, epsilon);
      double logMMinusKFact = nlogFactorial(m - k, epsilon);
      double logCMk = mlogFactorial - logKfact - logMMinusKFact;

      double Cmk = exp(logCMk);

      double sign = (k % 2 == 0) ? 1.0 : -1.0;

      currentSum += Cmk * sign * logKfact;
    }

    currentGamma = currentSum;

    if (m > 1 && fabs(currentGamma - previousGamma) < epsilon) {
      break;
    }
  }

  return currentGamma;
}

bool *sieveOfEratosthenes(int limit) {
  bool *isPrime = (bool *)malloc((limit + 1) * sizeof(bool));

  if (isPrime == NULL) {
    printf("Ошибка выделения памяти для решета Эратосфена\n");
    return NULL;
  }

  for (int i = 0; i <= limit; ++i) {
    isPrime[i] = true;
  }

  isPrime[0] = isPrime[1] = false;

  for (int p = 2; p * p <= limit; ++p) {
    if (isPrime[p]) {
      for (int i = p * p; i <= limit; i += p) {
        isPrime[i] = false;
      }
    }
  }

  return isPrime;
}

double calculateMertensLimit(const double epsilon) {
  double currentLimit = 0.0;
  double previousLimit = -1.0;
  int t = 2;

  while (fabs(currentLimit - previousLimit) > epsilon) {
    previousLimit = currentLimit;
    bool *primes = sieveOfEratosthenes(t);

    if (primes == NULL) {
      printf("Ошибка выделения памяти для решета при вычислении предела\n");
      return NAN;
    }

    double prod = 1.0;

    for (int p = 2; p <= t; ++p) {
      if (primes[p]) {
        prod *= (1.0 - 1.0 / p);
      }
    }

    free(primes);
    currentLimit = nlog((double)t, epsilon) * prod;
    t = (int)(t * 1.5);

    if (t < 3) {
      t = 3;
    }
  }

  return currentLimit;
}

double calculateGammaEquation(const double epsilon) {
  double limit = calculateMertensLimit(epsilon);

  return -nlog(limit, epsilon);
}
