#include "actions.h"

int main(int argc, char *argv[]) {

  if (argc < 2) {
    PrintExceptions(INVALID_NUMBER_OF_ARGS);
    return INVALID_NUMBER_OF_ARGS;
  }

  char *flag = argv[1];

  if (strcmp(flag, "-q") == 0 || strcmp(flag, "/q") == 0) {

    if (argc != 6) {
      PrintExceptions(INVALID_NUMBER_OF_ARGS_FOR_FLAG);
      return INVALID_NUMBER_OF_ARGS_FOR_FLAG;
    }

    double epsilon, a, b, c;
    StatusCode status;

    status = StringToDouble(argv[2], &epsilon);
    if (status != OK) {
      PrintExceptions(status);
      return status;
    }

    status = StringToDouble(argv[3], &a);
    if (status != OK) {
      PrintExceptions(status);
      return status;
    }

    status = StringToDouble(argv[4], &b);
    if (status != OK) {
      PrintExceptions(status);
      return status;
    }

    status = StringToDouble(argv[5], &c);
    if (status != OK) {
      PrintExceptions(status);
      return status;
    }

    if (epsilon <= 0) {
      printf("Эпсилон должен быть положительным\n");
      return INVALID_ARGUMENT;
    }

    PrintQuadSolves(epsilon, a, b, c);
  }

  else if (strcmp(flag, "-m") == 0 || strcmp(flag, "/m") == 0) {

    if (argc != 4) {
      PrintExceptions(INVALID_NUMBER_OF_ARGS_FOR_FLAG);
      return INVALID_NUMBER_OF_ARGS_FOR_FLAG;
    }

    int number1, number2;
    StatusCode status;

    status = StringToInt(argv[2], &number1);
    if (status != OK) {
      PrintExceptions(status);
      return status;
    }

    status = StringToInt(argv[3], &number2);
    if (status != OK) {
      PrintExceptions(status);
      return status;
    }

    if (number1 == 0 || number2 == 0) {
      PrintExceptions(INVALID_ARGUMENT);
      return INVALID_ARGUMENT;
    }

    if (CheckMultiplicity(number1, number2)) {
      printf("Первое число кратно второму\n");
    } else {
      printf("Первое число не кратно второму\n");
    }
  }

  else if (strcmp(flag, "-t") == 0 || strcmp(flag, "/t") == 0) {

    if (argc != 6) {
      PrintExceptions(INVALID_NUMBER_OF_ARGS_FOR_FLAG);
      return INVALID_NUMBER_OF_ARGS_FOR_FLAG;
    }

    double epsilon, a, b, c;
    StatusCode status;

    status = StringToDouble(argv[2], &epsilon);
    if (status != OK) {
      PrintExceptions(status);
      return status;
    }

    if (epsilon <= 0) {
      printf("Эпсилон должен быть положительным\n");
      return INVALID_ARGUMENT;
    }

    status = StringToDouble(argv[3], &a);
    if (status != OK) {
      PrintExceptions(status);
      return status;
    }

    status = StringToDouble(argv[4], &b);
    if (status != OK) {
      PrintExceptions(status);
      return status;
    }

    status = StringToDouble(argv[5], &c);
    if (status != OK) {
      PrintExceptions(status);
      return status;
    }

    if (CheckRightTriangle(epsilon, a, b, c)) {
      printf("Три числа могут являться длинами сторон прямоугольного "
             "треугольника\n");
    } else {
      printf("Три числа не могут являться длинами сторон прямоугольного "
             "треугольника\n");
    }
  }

  else {
    PrintExceptions(UNKNOWN_FLAG);
    return UNKNOWN_FLAG;
  }

  return OK;
}
