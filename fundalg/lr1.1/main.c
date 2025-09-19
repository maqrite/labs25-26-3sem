#include "actions.h"

int main(int argc, char *argv[]) {

  if (argc != 3) {
    PrintExceptions(INVALID_NUMBER_OF_ARGS);
    return INVALID_NUMBER_OF_ARGS;
  }

  char FirstElement = argv[2][0];

  if (!FlagFirstElementCheck(FirstElement)) {
    PrintExceptions(UNKNOWN_FLAG);
    return UNKNOWN_FLAG;
  }

  const int base = 10;
  char *pEnd;

  long int number = StringToNumber(argv[1], &pEnd, base);

  if (pEnd == argv[1] || *pEnd != '\0' || number <= 0) {
    PrintExceptions(INCORRECT_NUMBER);
    return INCORRECT_NUMBER;
  }

  if ((strcmp(argv[2], "-e") == 0 || strcmp(argv[2], "/e") == 0) &&
      number > 10) {
    PrintExceptions(INCORRECT_NUMBER_FOR_FLAG);
    return INCORRECT_NUMBER_FOR_FLAG;
  }
  if ((strcmp(argv[2], "-f") == 0 || strcmp(argv[2], "/f") == 0) &&
      number > 20) {
    PrintExceptions(INCORRECT_NUMBER_FOR_FLAG);
    return INCORRECT_NUMBER_FOR_FLAG;
  }

  if (strcmp(argv[2], "-a") == 0 || strcmp(argv[2], "/a") == 0) {
    long long sum = CalculateSum(number);
    printf("Сумма равна: %lld\n", sum);
  } else if (strcmp(argv[2], "-p") == 0 || strcmp(argv[2], "/p") == 0) {
    if (IsPrime(number)) {
      printf("Число %ld является простым\n", number);
    } else {
      printf("Число %ld является составным\n", number);
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
    PrintExceptions(UNKNOWN_FLAG);
    return UNKNOWN_FLAG;
  }
  return OK;
}
