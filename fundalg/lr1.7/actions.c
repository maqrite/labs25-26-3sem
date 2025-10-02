#include "actions.h"
#include <limits.h>

void PrintErrors(StatusCode status) {
  switch (status) {
  case INVALID_NUMBER_OF_ARGS:
    printf("Недопустимое количество аргументов\n");
    break;

  case INPUT_FILE_OPEN_ERROR:
    printf("Ошибка при открытии файла\n");
    break;

  case OUTPUT_FILE_OPEN_ERROR:
    printf("Ошибка при открытии файла\n");
    break;

  case INVALID_CHARACTER_IN_NUMBER:
    printf("в строке найден недопустимый символ\n");
    break;

  case NUMBER_OVERFLOW:
    printf("число слишком велико\n");
    break;

  default:
    break;
  }
}

StatusCode getDigitValue(char c, int *out_value) {
  c = tolower(c);
  if (c >= '0' && c <= '9') {
    *out_value = c - '0';
    return OK;
  }

  if (c >= 'a' && c <= 'z') {
    *out_value = c - 'a' + 10;
    return OK;
  }

  return INVALID_CHARACTER_IN_NUMBER;
}

StatusCode processNumber(const char *numberStr, int *outBase,
                         unsigned long long *outValue) {
  int maxDigit = 0;

  for (int i = 0; numberStr[i] != '\0'; ++i) {
    int digit;
    StatusCode status = getDigitValue(numberStr[i], &digit);

    if (status != OK) {
      return status;
    }

    if (digit > maxDigit) {
      maxDigit = digit;
    }
  }

  int base = maxDigit + 1;

  if (base < 2) {
    base = 2;
  }

  unsigned long long result = 0;

  for (int i = 0; numberStr[i] != '\0'; ++i) {
    int digit;
    StatusCode status = getDigitValue(numberStr[i], &digit);

    if (status != OK) {
      return status;
    }

    if (result > (ULLONG_MAX - digit) / base) {
      return NUMBER_OVERFLOW;
    }

    result = result * base + digit;
  }

  *outBase = base;
  *outValue = result;

  return OK;
}

StatusCode processFiles(const char *inputPath, const char *outputPath) {

  FILE *inputFile = fopen(inputPath, "r");
  if (inputFile == NULL) {
    return INPUT_FILE_OPEN_ERROR;
  }

  FILE *outputFile = fopen(outputPath, "w");
  if (outputFile == NULL) {
    fclose(inputFile);
    return OUTPUT_FILE_OPEN_ERROR;
  }

  char numberStr[257];

  while (fscanf(inputFile, "%256s", numberStr) == 1) {
    int base;
    unsigned long long value;

    StatusCode status = processNumber(numberStr, &base, &value);

    if (status == OK) {
      const char *outputStr = numberStr;
      while (*outputStr == '0' && *(outputStr + 1) != '\0') {
        outputStr++;
      }
      fprintf(outputFile, "%s %d %llu\n", outputStr, base, value);
    } else {
      fprintf(stderr, "Неудалось обработать строку /%s/\n", numberStr);
    }
  }

  fclose(inputFile);
  fclose(outputFile);

  return OK;
}
