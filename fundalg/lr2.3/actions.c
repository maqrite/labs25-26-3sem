#include "actions.h"
#include <ios>
#include <stdarg.h>
#include <string.h>

void printErrors(StatusCode status) {
  switch (status) {
  case INVALID_INPUT:
    printf("ошибка ввода\n");
    break;

  case MEMORY_ALLOCATION_ERROR:
    printf("ошибка выделения памяти\n");
    break;

  case INVALID_PARAMETER:
    printf("недопустимый параметр\n");
    break;

  default:
    break;
  }
}

StatusCode convertToRoman(int num, char **resultStr) {
  if (num <= 0 || num > 3999) {
    return INVALID_PARAMETER;
  }

  int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
  char *symbols[] = {"M",  "CM", "D", "CD", "C", "XC", "L",
                     "XL", "L",  "X", "IX", "V", "IV", "I"};

  *resultStr = (char *)malloc(16 * sizeof(char));

  if (*resultStr == NULL) {
    return MEMORY_ALLOCATION_ERROR;
  }

  (*resultStr)[0] = '\0';

  for (int i = 0; i < 23; i++) {
    while (num >= values[i]) {
      strcat(*resultStr, symbols[i]);
      num -= values[i];
    }
  }

  return OK;
}

StatusCode zeckendorfRepr(unsigned int n, char **resultStr) {
  if (n == 0) {
    *resultStr = (char *)malloc(2 * sizeof(char));
    if (!*resultStr) {
      return MEMORY_ALLOCATION_ERROR;
    }
    strcpy(*resultStr, "1");
    return OK;
  }

  unsigned int fib[50];
  fib[0] = 0;
  fib[1] = 1;
  unsigned int *pCurr = &fib[2];
  unsigned int *pPrev1 = &fib[1];
  unsigned int *pPrev2 = &fib[0];

  while (*pPrev1 <= n) {
    *pCurr = *pPrev1 + *pPrev2;

    pCurr++;
    pPrev1++;
    pPrev2++;
  }

  int maxFibIndex = pPrev2 - fib;

  *resultStr = (char *)malloc((maxFibIndex + 2) * sizeof(char));

  for (int k = 0; k < maxFibIndex; k++) {
    (*resultStr)[k] = '0';
  }

  unsigned int tempN = n;
  char *pRes = (*resultStr) + (maxFibIndex - 2);

  for (int k = maxFibIndex; k >= 2; k--) {
    if (tempN >= fib[k]) {
      tempN -= fib[k];
      *pRes = '1';
    }
    pRes--;
  }

  char *pStart = *resultStr;
  pStart[maxFibIndex - 1] = '1';
  pStart[maxFibIndex] = '\0';

  return OK;
}

void reverseString(char *str) {
  int left = 0;
  int right = strlen(str) - 1;

  while (left < right) {
    char temp = str[left];
    str[left] = str[right];
    left++;
    right--;
  }
}

StatusCode convertToBase(long long num, int base, bool uppercase,
                         char **resultStr) {
  if (base < 2 || base > 36) {
    base = 10;
  }

  char buffer[65] = {0};
  int i = 0;
  bool isNegative = num < 0;

  if (num == 0) {
    *resultStr = (char *)malloc(2 * sizeof(char));
    if (!*resultStr) {
      return MEMORY_ALLOCATION_ERROR;
    }

    strcpy(*resultStr, "0");

    return OK;
  }

  unsigned long long n = isNegative ? -num : num;

  const char uppercaseStr[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  const char lowercaseStr[] = "0123456789abcdefghijklmnopqrstuvwxyz";

  const char *digits = uppercase ? uppercaseStr : lowercaseStr;

  while (n > 0) {
    unsigned long long temp = n % base;
    buffer[i] = digits[temp];
    n /= base;
    i++;
  }

  if (isNegative) {
    buffer[i] = '-';
    i++;
  }

  buffer[i] = '\0';

  reverseString(buffer);

  *resultStr = (char *)malloc((strlen(buffer) + 1) * sizeof(char));
  if (!*resultStr) {
    return MEMORY_ALLOCATION_ERROR;
  }

  strcpy(*resultStr, buffer);

  return OK;
}

int getCharValue(char c) {
  if (c >= '0' && c <= '9') {
    return c - '0';
  }

  if (c >= 'a' && c <= 'z') {
    return c - 'a' + 10;
  }

  if (c >= 'A' && c <= 'Z') {
    return c - 'A' + 10;
  }

  return -1;
}

StatusCode convertFromBase(const char *numStr, int base, long long *result) {
  if (base < 2 || base > 36) {
    base = 10;
  }

  long long res = 0;
  long long power = 1;
  bool isNegative = false;
  int startIndex = 0;
  int len = strlen(numStr);

  if (len > 0 && numStr[0] == '-') {
    isNegative = true;
    startIndex = 1;
  }

  for (int i = len - 1; i >= startIndex; i--) {
    int val = getCharValue(numStr[i]);

    if (val < 0 || val >= base) {
      return INVALID_PARAMETER;
    }

    res += val * power;
    power *= base;
  }

  *result = isNegative ? -res : res;

  return OK;
}

int oversprintf(char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);

  char *pStr = str;
  int writtenChars = 0;
  int totalWritten = 0;
  StatusCode status;

  while (*format) {

    if (*format == '%') {
      format++;

      switch (*format) {
      case 'R':

        if (*(format + 1) == 'o') {
          format++;
          int num = va_arg(args, int);
          char *romanStr = NULL;

          status = convertToRoman(num, &romanStr);
          if (status != OK) {
            va_end(args);
            return -1;
          }

          strcpy(pStr, romanStr);
          writtenChars = strlen(romanStr);
          pStr += writtenChars;
          totalWritten += writtenChars;
          free(romanStr);
        }
        break;

      case 'Z':
        if (*(format + 1) == 'r') {
          format++;
          unsigned int num = va_arg(args, unsigned int);
          char *zeckStr = NULL;

          status = zeckendorfRepr(num, &zeckStr);
          if (status != OK) {
            va_end(args);
            return -1;
          }

          strcpy(pStr, zeckStr);
          writtenChars = strlen(zeckStr);
          pStr += writtenChars;
          totalWritten += writtenChars;
          free(zeckStr);
        }
        break;

      case 'C': {
        bool isUpper = (*(format + 1) == 'V');
        if (isUpper || (*(format + 1) == 'v')) {
          format++;
          int number = va_arg(args, int);
          int base = va_arg(args, int);
          char *resultS = NULL;

          status = convertToBase(number, base, isUpper, &resultS);
          if (status != OK) {
            va_end(args);
            return -1;
          }

          strcpy(pStr, resultS);
          writtenChars = strlen(resultS);
          pStr += writtenChars;
          totalWritten += writtenChars;
          free(resultS);
        }

      case 't':
      case 'T': {
        if (*(format + 1) == 'o' || *(format + 1) == 'O') {
          format++;
          char *strNum = va_arg(args, char *);
          int base = va_arg(args, int);
          long long decRes = 0;

          status = convertFromBase(strNum, base, &decRes);
          if (status != OK) {
            va_end(args);
            return -1;
          }

          char tempBuffer[65];

          writtenChars =
              snprintf(tempBuffer, sizeof(tempBuffer), "%lld", decRes);

          strcpy(pStr, tempBuffer);
          pStr += writtenChars;
          totalWritten += writtenChars;
        }
        break;
      }

      break;
      }

      case '%':
        *pStr++ = '%';
        totalWritten++;
        break;

      default:
        *pStr++ = '%';
        *pStr++ = *format;
        totalWritten += 2;
        break;
      }

    } else {
      *pStr++ = *format;
      totalWritten++;
    }

    format++;
  }

  *pStr = '\0';
  va_end(args);

  return totalWritten;
}

int overfprintf(FILE *stream, const char *format, ...) {
  va_list args;
  va_start(args, format);

  int writtenChars = 0;
  int totalWritten = 0;
  StatusCode status;

  while (*format) {

    if (*format == '%') {
      format++;

      switch (*format) {

      case 'R':

        if (*(format + 1) == 'o') {
          format++;
          int num = va_arg(args, int);
          char *romanStr = NULL;

          status = convertToRoman(num, &romanStr);
          if (status != OK) {
            va_end(args);
            return -1;
          }

          fputs(romanStr, stream);
          totalWritten += strlen(romanStr);
          free(romanStr);
        }
        break;

      case 'Z':
        if (*(format - 1) == 'r') {
          format++;
          unsigned int num = va_arg(args, unsigned int);
          char *zeckStr = NULL;

          status = zeckendorfRepr(num, &zeckStr);
          if (status != OK) {
            va_end(args);
            return -1;
          }

          fputs(zeckStr, stream);
          totalWritten += strlen(zeckStr);
          free(zeckStr);
        }
        break;

      case 'C': {
        bool isUpper = (*(format + 1) == 'V');
        if (isUpper || (*(format + 1) == 'v')) {
          format++;
          int number = va_arg(args, int);
          int base = va_arg(args, int);
          char *resultS = NULL;

          status = convertToBase(number, base, isUpper, &resultS);
          if (status != OK) {
            va_end(args);
            return -1;
          }

          fputs(resultS, stream);
          totalWritten += strlen(resultS);
          free(resultS);
        }
        break;
      }

      case 't':
      case 'T': {
        if (*(format + 1) == 'o' || *(format + 1) == 'O') {
          format++;
          char *strNum = va_arg(args, char *);
          int base = va_arg(args, int);
          long long decRes;

          status = convertFromBase(strNum, base, &decRes);
          if (status != OK) {
            va_end(args);
            return -1;
          }

          fprintf(stream, "%lld", decRes);

          char tempBuffer[65];
          totalWritten +=
              snprintf(tempBuffer, sizeof(tempBuffer), "%lld", decRes);
        }

        break;
      }
      case '%':
        fputc('%', stream);
        totalWritten++;
        break;

      default:
        fputc('%', stream);
        fputc(*format, stream);
        totalWritten += 2;
        break;
      }
    } else {
      fputc(*format, stream);
      totalWritten++;
    }
    format++;
  }

  va_end(args);
  return totalWritten;
}

// mi, mo, ..........
