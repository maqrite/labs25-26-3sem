#include "actions.h"
#include <string.h>

int main(int argc, char *argv[]) {

  Input input = {
      .constName = NULL,
      .methodName = NULL,
      .epsilon = 0.0,
      .constProvided = false,
      .methodProvided = false,
      .epsilonProvided = false,
  };

  if (argc < 2) {
    printExceptions(INVALID_NUMBER_OF_ARGS);
    return INVALID_NUMBER_OF_ARGS;
  }

  for (int i = 1; i < argc; ++i) {

    if (strcmp(argv[i], "--const") == 0) {

      if (i + 1 < argc) {
        input.constName = argv[i + 1];
        input.constProvided = true;
        ++i;
      } else {
        printExceptions(FLAG_ERROR);

        return FLAG_ERROR;
      }

    } else if (strcmp(argv[i], "--method") == 0) {
      if (i + 1 < argc) {
        input.methodName = argv[i + 1];
        input.methodProvided = true;
        ++i;
      } else {
        printExceptions(FLAG_ERROR);

        return FLAG_ERROR;
      }
    }

    else if (strcmp(argv[i], "--eps") == 0) {
      if (i + 1 < argc) {
        StatusCode status = stringToDouble(argv[i + 1], &input.epsilon);
        if (status != OK) {
          printExceptions(FLAG_ERROR);

          return FLAG_ERROR;
        }
        input.epsilonProvided = true;
        ++i;
      } else {
        printExceptions(FLAG_ERROR);
        return FLAG_ERROR;
      }
    } else {
      printExceptions(FLAG_ERROR);
      return FLAG_ERROR;
    }
  }

  if (!input.constProvided || !input.methodProvided || !input.epsilonProvided) {
    printExceptions(FLAG_ERROR);
    return FLAG_ERROR;
  }

  if (input.epsilon <= 0) {
    printf("Эпсилон должен быть положительным\n");
    return INVALID_ARGUMENT;
  }

  double result = 0.0;
  bool calculationDone = false;

  if (strcmp(input.constName, "pi") == 0) {
    if (strcmp(input.methodName, "s") == 0) {
      result = calculatePiSeries(input.epsilon);
      calculationDone = true;
    } else if (strcmp(input.methodName, "l") == 0) {
      result = calculatePiLimit(input.epsilon);
      calculationDone = true;
    } else if (strcmp(input.methodName, "e") == 0) {
      result = calculatePiEquation(input.epsilon);
      calculationDone = true;
    } else {
      printExceptions(CALCULATION_ERROR);
      return CALCULATION_ERROR;
    }
  }

  else if (strcmp(input.constName, "exp") == 0) {
    if (strcmp(input.methodName, "s") == 0) {
      result = calculateExpSeries(input.epsilon);
      calculationDone = true;
    } else if (strcmp(input.methodName, "l") == 0) {
      result = calculateExpLimit(input.epsilon);
      calculationDone = true;
    } else if (strcmp(input.methodName, "e") == 0) {
      result = calculateExpEquation(input.epsilon);
      calculationDone = true;
    } else {
      printExceptions(CALCULATION_ERROR);
      return CALCULATION_ERROR;
    }
  }

  else if (strcmp(input.constName, "ln2") == 0) {
    if (strcmp(input.methodName, "s") == 0) {
      result = calculateLn2Series(input.epsilon);
      calculationDone = true;
    } else if (strcmp(input.methodName, "l") == 0) {
      result = calculateLn2Limit(input.epsilon);
      calculationDone = true;
    } else if (strcmp(input.methodName, "e") == 0) {
      result = calculateLn2Equation(input.epsilon);
      calculationDone = true;
    } else {
      printExceptions(CALCULATION_ERROR);
      return CALCULATION_ERROR;
    }
  }

  else if (strcmp(input.constName, "sqrt2") == 0) {
    if (strcmp(input.methodName, "s") == 0) {
      result = calculateSqrt2Series(input.epsilon);
      calculationDone = true;
    } else if (strcmp(input.methodName, "l") == 0) {
      result = calculateSqrt2Limit(input.epsilon);
      calculationDone = true;
    } else if (strcmp(input.methodName, "e") == 0) {
      result = calculateSqrt2Equation(input.epsilon);
      calculationDone = true;
    } else {
      printExceptions(CALCULATION_ERROR);
      return CALCULATION_ERROR;
    }
  }

  else if (strcmp(input.constName, "gamma") == 0) {
    if (strcmp(input.methodName, "s") == 0) {
      result = calculateGammaSeries(input.epsilon);
      calculationDone = true;
    } else if (strcmp(input.methodName, "l") == 0) {
      result = calculateGammaLimit(input.epsilon);
      calculationDone = true;
    } else if (strcmp(input.methodName, "e") == 0) {
      result = calculateGammaEquation(input.epsilon);
      calculationDone = true;
    } else {
      printExceptions(CALCULATION_ERROR);
      return CALCULATION_ERROR;
    }
  }

  if (calculationDone) {
    printf("Результат: %.*f\n", 15, result);
  } else {
    printf("Неизвестная комбинация константы '%s' и метода '%s'\n",
           input.constName, input.methodName);
    return INVALID_ARGUMENT;
  }

  return OK;
}
