#include "actions.h"

void PrintErrors(StatusCode status) {
  switch (status) {
  case INVALID_NUMBER_OF_ARGS:
    printf("Недопустимое количество аргументов\n");
    break;

  case FLAG_ERROR:
    printf("Некорректный или неизвестный флаг\n");
    break;

  case EPSILON_PARSE_ERROR:
    printf("Ошибка в парсинге эпсилон\n");
    break;

  case OPTION_ERROR:
    printf("ошибка при выборе опции или при ее парсинге\n");
    break;

  default:
    break;
  }
}

StatusCode InputParse(UserInput *input, char *argv[], int argc) {
  input->epsilon = 0.0;
  input->option = 0;
  bool epsilonFound = false;

  for (int i = 1; i < argc; i++) {

    if (strcmp(argv[i], "-e") == 0) {

      if (i + 1 >= argc) {
        return EPSILON_PARSE_ERROR;
      }

      char *pEnd;
      input->epsilon = strtod(argv[i + 1], &pEnd);

      if (*pEnd != '\0' || input->epsilon <= 0) {
        return EPSILON_PARSE_ERROR;
      }

      epsilonFound = true;
      i++;

    } else if (strcmp(argv[i], "-a") == 0 || strcmp(argv[i], "-b") == 0 ||
               strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "-d") == 0) {

      if (input->option != 0) {
        return OPTION_ERROR;
      }

      input->option = argv[i][1];
    } else {

      return FLAG_ERROR;
    }
  }

  if (!epsilonFound) {
    return EPSILON_PARSE_ERROR;
  }

  return OK;
}

double funcA(double x) {
  if (x == 0) {
    return 1.0;
  }
  return log(1.0 + x) / x;
}

double funcB(double x) { return exp(-x * x / 2.0); }

double funcC(double x) { return -log(1.0 - x); }

double funcD(double x) {
  if (x == 0.0) {
    return 1.0;
  }
  return pow(x, x);
}

StatusCode calculateIntegral(double a, double b, double epsilon,
                             double (*f)(double), double *result) {
  int n = 4;
  double hN = (b - a) / n;
  double sumN = (f(a) + f(b)) / 2.0;

  for (int i = 1; i < n; i++) {
    sumN += f(a + i * hN);
  }

  double iN = sumN * hN;

  while (1) {
    n *= 2;
    if (n > 10000000) {
      return OK;
    }

    double h2N = (b - a) / n;
    double sum2N = (f(a) + f(b)) / 2;
    for (int i = 1; i < n; i++) {
      sum2N += f(a + i * h2N);
    }
    double i2N = sum2N * h2N;

    if (fabs(i2N - iN) < epsilon) {
      *result = i2N;
      return OK;
    }
    iN = i2N;
  }
  return OK;
}

StatusCode forA(UserInput *input, double *answer) {
  return calculateIntegral(0.0, 1.0, input->epsilon, funcA, answer);
}

StatusCode forB(UserInput *input, double *answer) {
  return calculateIntegral(0.0, 1.0, input->epsilon, funcB, answer);
}

StatusCode forC(UserInput *input, double *answer) {
  const double highLim = 1.0 - input->epsilon;
  return calculateIntegral(0.0, highLim, input->epsilon, funcC, answer);
}

StatusCode forD(UserInput *input, double *answer) {
  return calculateIntegral(0.0, 1.0, input->epsilon, funcD, answer);
}
