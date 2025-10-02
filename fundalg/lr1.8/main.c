#include "actions.h"

int main(int argc, char *argv[]) {

  (void)argv;

  if (argc > 1) {
    PrintErrors(INVALID_NUMBER_OF_ARGS);
    return INVALID_NUMBER_OF_ARGS;
  }

  int base;
  printf("Введите основание системы счисления в диапазоне [2, 36]:\t");
  StatusCode status = readAndValidateBase(&base);

  if (status != OK) {
    PrintErrors(status);
    return status;
  }

  char inputBuffer[256];
  char maxAbsStr[256];
  long long maxAbsValue = -1;
  bool firstNumberEntered = false;

  printf("Введите числа в системе счисления %d. Для завершения введите stop\n",
         base);

  while (fgets(inputBuffer, 256, stdin)) {
    inputBuffer[strcspn(inputBuffer, "\n")] = 0;

    if (strcmp(inputBuffer, "stop") == 0) {
      break;
    }

    long long currentNumber;

    status = toLongLong(inputBuffer, base, &currentNumber);

    if (status != OK) {
      printf("Некорректный ввод /%s/", inputBuffer);
      PrintErrors(status);
      continue;
    }

    long long currentAbsValue = llabs(currentNumber);

    if (!firstNumberEntered || currentAbsValue > maxAbsValue) {
      maxAbsValue = currentAbsValue;
      strcpy(maxAbsStr, inputBuffer);
      firstNumberEntered = true;
    }
  }

  if (!firstNumberEntered) {
    PrintErrors(NO_VALID_NUMBERS_ENTERED);
    return OK;
  }

  printf("Максимальное число по модулю: %s\n", maxAbsStr);

  long long maxNumberToConvert;
  StatusCode status1 = toLongLong(maxAbsStr, base, &maxNumberToConvert);

  if (status1 != OK) {
    PrintErrors(status1);
    return status1;
  }

  int targetBases[] = {9, 18, 27, 36};
  int numTargetBases = sizeof(targetBases) / sizeof(targetBases[0]);

  for (int i = 0; i < numTargetBases; ++i) {
    char *resultString = NULL;
    int targetBase = targetBases[i];

    status = fromLongLong(maxNumberToConvert, targetBase, &resultString);

    if (status == OK) {
      printf("B %d c/c: %s\n", targetBase, resultString);
      free(resultString);
    } else {
      printf("Не удалось конвертировать в с/с %d\n", targetBase);
      PrintErrors(status);
    }
  }

  return OK;
}
