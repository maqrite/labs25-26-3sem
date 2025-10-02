#include "actions.h"

void PrintErrors(StatusCode status) {
  switch (status) {

  case INVALID_NUMBER_OF_ARGS:
    printf("Недопустимое количество аргументов\n");
    break;

  case INVALID_INPUT:
    printf("передано некорректное число\n");
    break;

  case INVALID_BASE:
    printf("Основание системы счисления должно быть в диапазоне [2, 36]\n");
    break;

  case INVALID_NUMBER_FORMAT:
    printf("Число содержит недопустимые символы для данного основания\n");
    break;

  case MEMORY_ALLOCATION_ERROR:
    printf("Ошибка выделения памяти\n");
    break;

  case OVERFLOW:
    printf("Переполнение при вычислениях\n");
    break;

  case NO_VALID_NUMBERS_ENTERED:
    printf("Не было передано ни одного корректного числа\n");
    break;

  case NULL_ARGUMENT:
    printf("передан нулевой аргумент\n");
    break;

  default:
    break;
  }
}

StatusCode readAndValidateBase(int *base) {

  if (scanf("%d", base) != 1) {
    while (getchar() != '\n')
      ;
    return INVALID_INPUT;
  }

  if (*base < 2 || *base > 36) {
    return INVALID_BASE;
  }

  while (getchar() != '\n')
    ;

  return OK;
}

StatusCode charToDigit(char c, int *digit) {
  if (digit == NULL) {
    return NULL_ARGUMENT;
  }

  if (c >= '0' && c <= '9') {
    *digit = c - '0';
    return OK;
  }

  char lowerC = tolower(c);

  if (lowerC >= 'a' && lowerC <= 'z') {
    *digit = lowerC - 'a' + 10;
    return OK;
  }

  return INVALID_NUMBER_FORMAT;
}

StatusCode toLongLong(const char *s, int base, long long *result) {
  if (s == NULL || *s == '\0') {
    return INVALID_NUMBER_FORMAT;
  }

  *result = 0;
  int sign = 1;
  int i = 0;

  if (s[i] == '-') {
    sign = -1;
    i++;
  } else if (s[i] == '+') {
    i++;
  }

  if (s[i] == '\0') {
    return INVALID_NUMBER_FORMAT;
  }

  for (; s[i] != '\0'; i++) {
    int digit;

    StatusCode status = charToDigit(s[i], &digit);

    if (status != OK) {
      return status;
    }

    if (digit >= base) {
      return INVALID_NUMBER_FORMAT;
    }

    if (*result > (LLONG_MAX - digit) / base) {
      return OVERFLOW;
    }

    *result = *result * base + digit;
  }

  *result *= sign;

  return OK;
}

StatusCode reverseString(char *str) {
  if (str == NULL) {
    return NULL_ARGUMENT;
  }

  int left = 0;
  int right = strlen(str) - 1;

  while (left < right) {
    char temp = str[left];
    str[left] = str[right];
    str[right] = temp;
    left++;
    right--;
  }

  return OK;
}

StatusCode fromLongLong(long long number, int base, char **resultStr) {

  const int bufferSize = 66;
  char *buffer = (char *)malloc(bufferSize);

  if (buffer == NULL) {
    return MEMORY_ALLOCATION_ERROR;
  }

  int i = 0;
  bool isNegative = number < 0;

  if (number == 0) {
    buffer[i] = '0';
    i++;
    buffer[i] = '\0';
    *resultStr = buffer;
    return OK;
  }

  unsigned long long tempNum;
  if (isNegative) {
    tempNum = (unsigned long long)(-number);
  } else {
    tempNum = (unsigned long long)number;
  }

  while (tempNum > 0) {
    int remainder = tempNum % base;

    if (remainder < 10) {
      buffer[i] = remainder + '0';
    } else {
      buffer[i] = (remainder - 10) + 'A';
    }
    i++;
    tempNum /= base;
  }

  if (isNegative) {
    buffer[i] = '-';
    i++;
  }

  buffer[i] = '\0';

  StatusCode status = reverseString(buffer);

  if (status != OK) {
    free(buffer);
    *resultStr = NULL;
    return status;
  }

  *resultStr = buffer;
  return OK;
}
