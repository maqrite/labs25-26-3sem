#include "actions.h"

void PrintExceptions(StatusCode status) {
  switch (status) {
  case INVALID_NUMBER_OF_ARGS:
    fprintf(stderr, "Недопустимое количество аргументов\n");
    break;

  case FLAG_ERROR:
    fprintf(stderr, "Некорректный или неизвестный флаг\n");
    break;

  case MEMORY_ALLOC_ERROR:
    fprintf(stderr, "Не удалось выделить память для имени файла\n");
    break;

  case FILE_OPEN_ERROR:
    fprintf(stderr, "Ошибка открытия файла\n");
    break;

  default:
    break;
  }
}

StatusCode FlagParse(InputFlag *flag, char *argv[], int argc) {
  const char *flagStr = argv[1];
  size_t flagLen = strlen(flagStr);

  if (flagStr[0] != '/' && flagStr[0] != '-') {
    return FLAG_ERROR;
  }

  if (flagLen == 3 && flagStr[1] == 'n') {
    flag->isN = true;
    flag->option = flagStr[2];

    if (argc != 4) {
      return INVALID_NUMBER_OF_ARGS;
    }

  } else if (flagLen == 2) {
    flag->isN = false;
    flag->option = flagStr[1];

    if (argc != 3) {
      return INVALID_NUMBER_OF_ARGS;
    }

  } else {
    return FLAG_ERROR;
  }

  switch (flag->option) {
  case 'd':
  case 'i':
  case 's':
  case 'a':
    break;

  default:
    return FLAG_ERROR;
  }

  return OK;
}

StatusCode forD(const char *input, char **output) {

  size_t nonDigitCounter = 0;
  for (size_t i = 0; input[i] != '\0'; i++) {
    if (!isdigit((unsigned char)input[i])) {
      nonDigitCounter++;
    }
  }

  *output = (char *)malloc(nonDigitCounter + 1);
  if (*output == NULL) {
    return MEMORY_ALLOC_ERROR;
  }

  size_t j = 0;
  for (size_t i = 0; input[i] != '\0'; i++) {
    if (!isdigit((unsigned char)input[i])) {
      (*output)[j] = input[i];
      j++;
    }
  }

  (*output)[j] = '\0';

  return OK;
}

StatusCode forI(const char *input, char **output) {

  size_t latinCharCounter = 0;
  for (size_t i = 0; input[i] != '\0'; i++) {
    if (isalpha((unsigned char)input[i])) {
      latinCharCounter++;
    }
  }

  size_t digits = 0;
  if (latinCharCounter == 0) {
    digits = 1;
  } else {
    size_t temp = latinCharCounter;
    while (temp > 0) {
      temp /= 10;
      digits++;
    }
  }

  *output = (char *)malloc(digits + 1);
  if (*output == NULL) {
    return MEMORY_ALLOC_ERROR;
  }

  snprintf(*output, digits + 1, "%zu", latinCharCounter);

  return OK;
}

StatusCode forS(const char *input, char **output) {
  size_t specialCharCounter = 0;
  for (size_t i = 0; input[i] != '\0'; i++) {
    unsigned char c = input[i];
    if (!isalpha(c) && !isdigit(c) && c != ' ') {
      specialCharCounter++;
    }
  }

  size_t digits = 0;
  if (specialCharCounter == 0) {
    digits = 1;
  } else {
    size_t temp = specialCharCounter;
    while (temp > 0) {
      temp /= 10;
      digits++;
    }
  }

  *output = (char *)malloc(digits + 1);
  if (*output == NULL) {
    return MEMORY_ALLOC_ERROR;
  }

  snprintf(*output, digits + 1, "%zu", specialCharCounter);

  return OK;
}

StatusCode forA(const char *input, char **output) {
  size_t outputLen = 0;
  for (size_t i = 0; input[i] != '\0'; i++) {
    if (isdigit((unsigned char)input[i])) {
      outputLen++;
    } else {
      outputLen += 2;
    }
  }

  *output = (char *)malloc(outputLen + 1);
  if (*output == NULL) {
    return MEMORY_ALLOC_ERROR;
  }

  size_t j = 0;
  for (size_t i = 0; input[i] != '\0'; i++) {
    unsigned char c = input[i];
    if (isdigit(c)) {
      (*output)[j] = c;
      j++;
    } else {
      snprintf(&((*output)[j]), 3, "%02X", c);
      j += 2;
    }
  }

  (*output)[j] = '\0';

  return OK;
}
