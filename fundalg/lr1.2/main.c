#include "actions.h"

int main() {
  const int base = 10;
  char buffer[50];
  int t;

  if (fgets(buffer, sizeof(buffer), stdin)) {
    char *pEnd;
    long int value = strtol(buffer, &pEnd, base);

    if (pEnd == buffer || (*pEnd != '\0' && *pEnd != '\n') || value < 0) {
      printExceptions(INCORRECT_NUMBER_OF_STRINGS);
      return INCORRECT_NUMBER_OF_STRINGS;
    }

    t = (int)value;
  } else {
    printExceptions(STRING_READ_ERROR);
    return STRING_READ_ERROR;
  }

  for (int i = 0; i < t; ++i) {
    if (fgets(buffer, sizeof(buffer), stdin)) {

      char *pEnd;
      long valueTwo = strtol(buffer, &pEnd, base);

      if (pEnd == buffer || (*pEnd != '\0' && *pEnd != '\n') || valueTwo < 0) {
        printExceptions(INCORRECT_NUMBER_IN_STRING);
        continue;
      }

      int n = (int)valueTwo;
      long long int answer;
      StatusCode status = findPrimeBasedOnSequenceNumber(n, &answer);

      if (status == OK) {
        printf("%lld\n", answer);
      } else {
        printExceptions(status);
        continue;
      }
    }
  }
  return OK;
}
