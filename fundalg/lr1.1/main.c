#include "actions.h"

// X -flag
int main(int argc, char *argv[]) {

  // argc -> кол-во аргументов  argv[] -> массив c cамими аргументами
  // argc >= 1 всегда. тк argv[0] - название исполняемого файла

  if (argc != 3) {
    PrintErrors(INVALID_NUMBER_OF_ARGS);
    return INVALID_NUMBER_OF_ARGS;
  }

  char firstElement = argv[2][0];

  if (!FlagFirstElementCheck(firstElement)) {
    PrintErrors(UNKNOWN_FLAG);
    return UNKNOWN_FLAG;
  }

  const int base = 10;
  char *pEnd; // strtol.  ->742723. -> \0

  long int number = StringToNumber(argv[1], &pEnd, base);

  if (pEnd == argv[1] || *pEnd != '\0' || number <= 0) {
    PrintErrors(INCORRECT_NUMBER);
    return INCORRECT_NUMBER;
  }

  if ((strcmp(argv[2], "-e") == 0 || strcmp(argv[2], "/e") == 0) &&
      number > 10) {
    PrintErrors(INCORRECT_NUMBER_FOR_FLAG);
    return INCORRECT_NUMBER_FOR_FLAG;
  }

  if ((strcmp(argv[2], "-f") == 0 || strcmp(argv[2], "/f") == 0) &&
      number > 20) {
    PrintErrors(INCORRECT_NUMBER_FOR_FLAG);
    return INCORRECT_NUMBER_FOR_FLAG;
  }

  if (strcmp(argv[2], "-a") == 0 || strcmp(argv[2], "/a") == 0) {
    long long sum = CalculateSum(number);
    printf("Сумма равна: %lld\n", sum);
  } else if (strcmp(argv[2], "-p") == 0 || strcmp(argv[2], "/p") == 0) {

    if (IsPrime(number)) {
      printf("%ld is simple\n", number);

    } else {
      printf("%ld not simple\n", number);
    }
  } else if (strcmp(argv[2], "-h") == 0 || strcmp(argv[2], "/h") == 0) {
    PrintMultiples(number);

  } else if (strcmp(argv[2], "-s") == 0 || strcmp(argv[2], "/s") == 0) {
    PrintHexDigits(number);

  } else if (strcmp(argv[2], "-e") == 0 || strcmp(argv[2], "/e") == 0) {
    PrintPowersTable(number);

  } else if (strcmp(argv[2], "-f") == 0 || strcmp(argv[2], "/f") == 0) {
    long long factorial = Factorial(number);
    printf("%ld! = %lld\n", number, factorial);

  } else {
    PrintErrors(UNKNOWN_FLAG);
    return UNKNOWN_FLAG;
  }

  return OK;
}
