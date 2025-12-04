#include "actions.h"

long long CalculateSum(const long int x) {
  long long sum = (long long)x * (x + 1) / 2;

  return sum;
}

bool IsPrime(const long int x) {
  long int i = 0;

  if (x == 1) {
    return false;
  }

  if (x <= 3) {
    return true;
  }

  if (x % 2 == 0 || x % 3 == 0) {
    return false;
  }

  for (i = 5; i * i <= x; i = i + 6) {
    if (x % i == 0 || x % (i + 2) == 0) {
      return false;
    }
  }

  return true;
}

void PrintMultiples(const long int x) {
  long int i = 0;
  const int limit = 100;
  bool Flag = false;

  for (i = 1; i <= limit; ++i) {
    if (i % x == 0) {
      Flag = true;
      printf("%ld\t", i);
    }
  }

  if (Flag == true) {
    printf("\n");
  } else {
    printf("There are no multiples of natural numbers within 100\n");
  }

  return;
}

void PrintHexDigits(const long int x) {
  char hexChars[] = "0123456789ABCDEF";

  if (x == 0) {
    printf("0\n");
    return;
  }

  if (x / 16 > 0) {
    PrintHexDigits(x / 16);
  }

  printf("%c ", hexChars[x % 16]);
}

void PrintPowersTable(const long int x) {
  printf("%-5s", "Base");
  long long result = 0;

  for (int exp = 1; exp <= x; ++exp) {
    printf("%-10d", exp);
  }
  printf("\n");

  for (int base = 1; base <= 10; ++base) {
    printf("%-5d", base);
    for (int exp = 1; exp <= x; ++exp) {
      result = 1;
      for (int i = 0; i < exp; ++i) {
        result *= base;
      }
      printf("%-10lld", result);
    }
    printf("\n");
  }

  return;
}

long long Factorial(const long int x) {
  long long factorial = 1;

  if (x == 0) {
    return 1;
  }

  for (int i = 1; i <= x; ++i) {
    factorial *= i;
  }

  return factorial;
}

bool FlagFirstElementCheck(const char element) {
  if ((element == '-') || (element == '/')) {
    return true;
  }

  return false;
}

long int StringToNumber(const char *string, char **endptr, int base) {
  long int number = strtol(string, endptr, base);

  return number;
}

void PrintErrors(const StatusCode status) {
  switch (status) {

  case INVALID_NUMBER_OF_ARGS:
    printf("Invalid number of arguments\n");
    break;

  case UNKNOWN_FLAG:
    printf("Unknown flag\n");
    break;

  case INCORRECT_NUMBER:
    printf("Incorrect number\n");
    break;

  case INCORRECT_NUMBER_FOR_FLAG:
    printf("Invalid number for the selected flag\n");
    break;

  default:
    break;
  }
}
