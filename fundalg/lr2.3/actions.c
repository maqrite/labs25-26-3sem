#include "actions.h"
#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
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
  char *symbols[] = {"M",  "CM", "D",  "CD", "C",  "XC", "L",
                     "XL", "X",  "IX", "V",  "IV", "I"};

  *resultStr = (char *)malloc(16 * sizeof(char));

  if (*resultStr == NULL) {
    return MEMORY_ALLOCATION_ERROR;
  }

  (*resultStr)[0] = '\0';

  for (int i = 0; i < 13; i++) {
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
  int maxFibIndex = 0;

  for (int i = 2; i < 50; i++) {
    if (fib[i - 1] > UINT_MAX - fib[i - 2]) {
      maxFibIndex = i - 1;
      break;
    }

    fib[i] = fib[i - 1] + fib[i - 2];

    if (fib[i] > n) {
      maxFibIndex = i - 1;
      break;
    }
  }

  *resultStr = (char *)malloc((maxFibIndex + 1) * sizeof(char));
  if (!*resultStr) {
    return MEMORY_ALLOCATION_ERROR;
  }

  for (int k = 0; k < maxFibIndex - 1; k++) {
    (*resultStr)[k] = '0';
  }

  unsigned int tempN = n;

  for (int k = maxFibIndex; k >= 2; k--) {
    if (tempN >= fib[k]) {
      tempN -= fib[k];
      (*resultStr)[k - 2] = '1';
    }
  }

  (*resultStr)[maxFibIndex - 1] = '1';
  (*resultStr)[maxFibIndex] = '\0';

  return OK;
}

void reverseString(char *str) {
  int left = 0;
  int right = strlen(str) - 1;

  while (left < right) {
    char temp = str[left];
    str[left] = str[right];
    str[right] = temp;
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

  unsigned long long n;
  if (num == LLONG_MIN) {
    n = (unsigned long long)LLONG_MAX + 1;
    isNegative = true;
  } else {
    n = isNegative ? -num : num;
  }

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

  bool isNegative = false;
  int startIndex = 0;
  int len = strlen(numStr);

  if (len > 0 && numStr[0] == '-') {
    isNegative = true;
    startIndex = 1;
  }

  unsigned long long tempRes = 0;
  unsigned long long cutoff =
      (unsigned long long)LLONG_MAX + (isNegative ? 1 : 0);
  unsigned long long cutlim = cutoff % base;

  cutoff /= base;

  for (int i = startIndex; i < len; i++) {
    int val = getCharValue(numStr[i]);

    if (val < 0 || val >= base) {
      return INVALID_PARAMETER;
    }

    if (tempRes > cutoff ||
        (tempRes == cutoff && (unsigned long long)val > cutlim)) {
      return INVALID_PARAMETER;
    }

    tempRes = tempRes * base + val;
  }

  *result = isNegative ? -(long long)tempRes : (long long)tempRes;

  return OK;
}

StatusCode dumpMemory(const void *data, size_t size, char **resultStr) {
  size_t requiredLen = size * 9;
  *resultStr = (char *)malloc(requiredLen);
  if (!*resultStr) {
    return MEMORY_ALLOCATION_ERROR;
  }

  const unsigned char *bytes = (const unsigned char *)data;
  char *pRes = *resultStr;

  for (size_t i = 0; i < size; i++) {
    unsigned char currentByte = bytes[i];

    for (int j = 7; j >= 0; j--) {
      *pRes = ((currentByte >> j) & 1) ? '1' : '0';
      pRes++;
    }

    if (i < size - 1) {
      *pRes = ' ';
      pRes++;
    }
  }
  *pRes = '\0';

  return OK;
}

StatusCode convertDoubleToString(double num, char **resultStr) {
  char *intStr = NULL;
  char *fracStr = NULL;
  StatusCode status;
  bool isNegative = num < 0;
  if (isNegative) {
    num = -num;
  }

  long long intPart = (long long)num;
  status = convertToBase(intPart, 10, false, &intStr);
  if (status != OK) {
    return status;
  }

  double fracPart = num - (double)intPart;

  long long fracNum = (long long)((fracPart * 1000000.0) + 0.5);

  // дальше Бога нет

  if (fracNum >= 1000000) {
    fracNum = 0;
    intPart++;
    free(intStr);
    status = convertToBase(intPart, 10, false, &intStr);
    if (status != OK) {
      return status;
    }
  }

  status = convertToBase(fracNum, 10, false, &fracStr);
  if (status != OK) {
    free(intStr);
    return status;
  }

  int fracLen = strlen(fracStr);
  int zerosToPad = 6 - fracLen;

  if (zerosToPad < 0) {
    zerosToPad = 0;
  }

  size_t totalLen = (isNegative ? 1 : 0) + strlen(intStr) + 1 + 6 + 1;
  *resultStr = (char *)malloc(totalLen * sizeof(char));
  if (*resultStr == NULL) {
    free(intStr);
    free(fracStr);
    return MEMORY_ALLOCATION_ERROR;
  }

  (*resultStr)[0] = '\0';

  if (isNegative) {
    strcat(*resultStr, "-");
  }

  strcat(*resultStr, intStr);
  strcat(*resultStr, ".");

  for (int i = 0; i < zerosToPad; i++) {
    strcat(*resultStr, "0");
  }

  strncat(*resultStr, fracStr, 6 - zerosToPad);

  free(intStr);
  free(fracStr);
  return OK;
}

int oversprintf(char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);

  char *pStr = str;
  int writtenChars = 0;
  int totalWritten = 0;
  StatusCode status;
  char *tempStr = NULL;

  while (*format) {

    if (*format == '%') {
      format++;

      switch (*format) {
      case 'R':
        if (*(format + 1) == 'o') {
          format++;
          int num = va_arg(args, int);

          status = convertToRoman(num, &tempStr);
          if (status != OK) {
            va_end(args);
            return -1;
          }

          strcpy(pStr, tempStr);
          writtenChars = strlen(tempStr);
          pStr += writtenChars;
          totalWritten += writtenChars;
          free(tempStr);
          tempStr = NULL;
          break;
        }

      case 'Z':
        if (*(format + 1) == 'r') {
          format++;
          unsigned int num = va_arg(args, unsigned int);

          status = zeckendorfRepr(num, &tempStr);
          if (status != OK) {
            va_end(args);
            return -1;
          }

          strcpy(pStr, tempStr);
          writtenChars = strlen(tempStr);
          pStr += writtenChars;
          totalWritten += writtenChars;
          free(tempStr);
          tempStr = NULL;
          break;
        }

      case 'C': {
        bool isUpper = (*(format + 1) == 'V');
        if (isUpper || (*(format + 1) == 'v')) {
          format++;
          int number = va_arg(args, int);
          int base = va_arg(args, int);

          status = convertToBase(number, base, isUpper, &tempStr);
          if (status != OK) {
            va_end(args);
            return -1;
          }

          strcpy(pStr, tempStr);
          writtenChars = strlen(tempStr);
          pStr += writtenChars;
          totalWritten += writtenChars;
          free(tempStr);
          tempStr = NULL;
          break;
        }
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

          status = convertToBase(decRes, 10, false, &tempStr);
          if (status != OK) {
            va_end(args);
            return -1;
          }

          strcpy(pStr, tempStr);
          writtenChars = strlen(tempStr);
          pStr += writtenChars;
          totalWritten += writtenChars;
          free(tempStr);
          tempStr = NULL;
          break;
        }
      }

      case 'm': {
        void *ptr = NULL;
        size_t dataSize = 0;

        int iVal;
        unsigned int uVal;
        double dVal;
        float fVal;

        switch (*(format + 1)) {

        case 'i': {
          iVal = va_arg(args, int);
          ptr = &iVal;
          dataSize = sizeof(int);
          format++;
          break;
        }

        case 'u': {
          uVal = va_arg(args, unsigned int);
          ptr = &uVal;
          dataSize = sizeof(unsigned int);
          format++;
          break;
        }

        case 'd': {
          dVal = va_arg(args, double);
          ptr = &dVal;
          dataSize = sizeof(double);
          format++;
          break;
        }

        case 'f': {
          fVal = (float)va_arg(args, double);
          ptr = &fVal;
          dataSize = sizeof(float);
          format++;
          break;
        }
        }

        if (ptr) {
          status = dumpMemory(ptr, dataSize, &tempStr);
          if (status != OK) {
            va_end(args);
            return -1;
          }

          strcpy(pStr, tempStr);
          int len = strlen(tempStr);
          pStr += len;
          totalWritten += len;

          free(tempStr);
          tempStr = NULL;
          break;
        }
      }

      default: {
        *pStr++ = '%';
        *pStr++ = *format;
        totalWritten += 2;
        break;
      }

      case '%':
        *pStr++ = '%';
        totalWritten++;
        break;

      case 'd':
      case 'i': {
        long long val = (long long)va_arg(args, int);
        status = convertToBase(val, 10, false, &tempStr);
        if (status != OK) {
          va_end(args);
          return -1;
        }
        writtenChars = strlen(tempStr);
        strcpy(pStr, tempStr);
        pStr += writtenChars;
        totalWritten += writtenChars;
        free(tempStr);
        break;
      }

      case 'u': {
        long long val = (long long)va_arg(args, unsigned int);
        status = convertToBase(val, 10, false, &tempStr);
        if (status != OK) {
          va_end(args);
          return -1;
        }
        writtenChars = strlen(tempStr);
        strcpy(pStr, tempStr);
        pStr += writtenChars;
        totalWritten += writtenChars;
        free(tempStr);
        break;
      }

      case 'x': {
        long long val = (long long)va_arg(args, unsigned int);
        status = convertToBase(val, 16, false, &tempStr);
        if (status != OK) {
          va_end(args);
          return -1;
        }
        writtenChars = strlen(tempStr);
        strcpy(pStr, tempStr);
        pStr += writtenChars;
        totalWritten += writtenChars;
        free(tempStr);
        break;
      }

      case 'X': {
        long long val = (long long)va_arg(args, unsigned int);
        status = convertToBase(val, 16, true, &tempStr);
        if (status != OK) {
          va_end(args);
          return -1;
        }
        writtenChars = strlen(tempStr);
        strcpy(pStr, tempStr);
        pStr += writtenChars;
        totalWritten += writtenChars;
        free(tempStr);
        break;
      }

      case 'o': {
        long long val = (long long)va_arg(args, unsigned int);
        status = convertToBase(val, 8, false, &tempStr);
        if (status != OK) {
          va_end(args);
          return -1;
        }
        writtenChars = strlen(tempStr);
        strcpy(pStr, tempStr);
        pStr += writtenChars;
        totalWritten += writtenChars;
        free(tempStr);
        break;
      }

      case 'f': {
        double val = va_arg(args, double);
        status = convertDoubleToString(val, &tempStr);
        if (status != OK) {
          va_end(args);
          return -1;
        }
        writtenChars = strlen(tempStr);
        strcpy(pStr, tempStr);
        pStr += writtenChars;
        totalWritten += writtenChars;
        free(tempStr);
        tempStr = NULL;
        break;
      }

      case 'c': {
        char val = (char)va_arg(args, int);
        *pStr++ = val;
        totalWritten++;
        break;
      }

      case 's': {
        char *val = va_arg(args, char *);
        if (val == NULL) {
          val = "(null)";
        }
        writtenChars = strlen(val);
        strcpy(pStr, val);
        pStr += writtenChars;
        totalWritten += writtenChars;
        break;
      }

      case 'p': {
        void *val = va_arg(args, void *);
        if (val == NULL) {
          writtenChars = strlen("(nil)");
          strcpy(pStr, "(nil)");
          pStr += writtenChars;
          totalWritten += writtenChars;
          break;
        }

        uintptr_t ptrVal = (uintptr_t)val;

        *pStr++ = '0';
        *pStr++ = 'x';
        totalWritten += 2;

        status = convertToBase((unsigned long long)ptrVal, 16, false, &tempStr);
        if (status != OK) {
          va_end(args);
          return -1;
        }

        writtenChars = strlen(tempStr);
        strcpy(pStr, tempStr);
        pStr += writtenChars;
        totalWritten += writtenChars;
        free(tempStr);
        break;
      }
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

  int totalWritten = 0;
  StatusCode status;
  char *tempStr = NULL;

  while (*format) {

    if (*format == '%') {
      format++;

      switch (*format) {

      case 'R':

        if (*(format + 1) == 'o') {
          format++;
          int num = va_arg(args, int);

          status = convertToRoman(num, &tempStr);
          if (status != OK) {
            va_end(args);
            return -1;
          }

          fputs(tempStr, stream);
          totalWritten += strlen(tempStr);
          free(tempStr);
          tempStr = NULL;
          break;
        }

      case 'Z':
        if (*(format + 1) == 'r') {
          format++;
          unsigned int num = va_arg(args, unsigned int);

          status = zeckendorfRepr(num, &tempStr);
          if (status != OK) {
            va_end(args);
            return -1;
          }

          fputs(tempStr, stream);
          totalWritten += strlen(tempStr);
          free(tempStr);
          tempStr = NULL;
          break;
        }

      case 'C': {
        bool isUpper = (*(format + 1) == 'V');
        if (isUpper || (*(format + 1) == 'v')) {
          format++;
          int number = va_arg(args, int);
          int base = va_arg(args, int);

          status = convertToBase(number, base, isUpper, &tempStr);
          if (status != OK) {
            va_end(args);
            return -1;
          }

          fputs(tempStr, stream);
          totalWritten += strlen(tempStr);
          free(tempStr);
          tempStr = NULL;
          break;
        }
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

          status = convertToBase(decRes, 10, false, &tempStr);
          if (status != OK) {
            va_end(args);
            return -1;
          }
          fputs(tempStr, stream);
          totalWritten += strlen(tempStr);
          free(tempStr);
          tempStr = NULL;
          break;
        }
      }

      case 'm': {
        void *ptr = NULL;
        size_t dataSize = 0;

        int iVal;
        unsigned int uVal;
        double dVal;
        float fVal;

        switch (*(format + 1)) {

        case 'i': {
          iVal = va_arg(args, int);
          ptr = &iVal;
          dataSize = sizeof(int);
          format++;
          break;
        }

        case 'u': {
          uVal = va_arg(args, unsigned int);
          ptr = &uVal;
          dataSize = sizeof(unsigned int);
          format++;
          break;
        }

        case 'd': {
          dVal = va_arg(args, double);
          ptr = &dVal;
          dataSize = sizeof(double);
          format++;
          break;
        }

        case 'f': {
          fVal = (float)va_arg(args, double);
          ptr = &fVal;
          dataSize = sizeof(float);
          format++;
          break;
        }
        }

        if (ptr) {
          status = dumpMemory(ptr, dataSize, &tempStr);
          if (status != OK) {
            va_end(args);
            return -1;
          }

          fputs(tempStr, stream);
          totalWritten += strlen(tempStr);

          free(tempStr);
          tempStr = NULL;
          break;
        }
      }

      default: {
        fputc('%', stream);
        fputc(*format, stream);
        totalWritten += 2;
        break;
      }

      case '%':
        fputc('%', stream);
        totalWritten++;
        break;

      case 'd':
      case 'i': {
        long long val = (long long)va_arg(args, int);
        status = convertToBase(val, 10, false, &tempStr);
        if (status != OK) {
          va_end(args);
          return -1;
        }
        fputs(tempStr, stream);
        totalWritten += strlen(tempStr);
        free(tempStr);
        break;
      }

      case 'u': {
        long long val = (long long)va_arg(args, unsigned int);
        status = convertToBase(val, 10, false, &tempStr);
        if (status != OK) {
          va_end(args);
          return -1;
        }
        fputs(tempStr, stream);
        totalWritten += strlen(tempStr);
        free(tempStr);
        break;
      }

      case 'x': {
        long long val = (long long)va_arg(args, unsigned int);
        status = convertToBase(val, 16, false, &tempStr);
        if (status != OK) {
          va_end(args);
          return -1;
        }
        fputs(tempStr, stream);
        totalWritten += strlen(tempStr);
        free(tempStr);
        break;
      }

      case 'X': {
        long long val = (long long)va_arg(args, unsigned int);
        status = convertToBase(val, 16, true, &tempStr);
        if (status != OK) {
          va_end(args);
          return -1;
        }
        fputs(tempStr, stream);
        totalWritten += strlen(tempStr);
        free(tempStr);
        break;
      }

      case 'o': {
        long long val = (long long)va_arg(args, unsigned int);
        status = convertToBase(val, 8, false, &tempStr);
        if (status != OK) {
          va_end(args);
          return -1;
        }
        fputs(tempStr, stream);
        totalWritten += strlen(tempStr);
        free(tempStr);
        break;
      }

      case 'f': {
        double val = va_arg(args, double);

        status = convertDoubleToString(val, &tempStr);
        if (status != OK) {
          va_end(args);
          return -1;
        }
        fputs(tempStr, stream);
        totalWritten += strlen(tempStr);
        free(tempStr);
        tempStr = NULL;
        break;
      }

      case 'c': {
        fputc((char)va_arg(args, int), stream);
        totalWritten++;
        break;
      }

      case 's': {
        char *val = va_arg(args, char *);
        if (val == NULL) {
          val = "(null)";
        }
        fputs(val, stream);
        totalWritten += strlen(val);
        break;
      }

      case 'p': {
        void *val = va_arg(args, void *);
        if (val == NULL) {
          fputs("(nil)", stream);
          totalWritten += strlen("(nil)");
          break;
        }

        uintptr_t ptrVal = (uintptr_t)val;
        fputs("0x", stream);
        totalWritten += 2;

        status = convertToBase((unsigned long long)ptrVal, 16, false, &tempStr);
        if (status != OK) {
          va_end(args);
          return -1;
        }
        fputs(tempStr, stream);
        totalWritten += strlen(tempStr);
        free(tempStr);
        break;
      }
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

static int g_test_count = 0;
static int g_test_passed = 0;

static void runTest(const char *testName, const char *expected,
                    const char *actual) {
  g_test_count++;
  printf("  [Тест %d] %s\n", g_test_count, testName);
  if (strcmp(expected, actual) == 0) {
    printf("    \x1b[32mPASS\x1b[0m\n");
    g_test_passed++;
  } else {
    printf("    \x1b[31mFAIL\x1b[0m\n");
    printf("    Ожидалось: \"%s\"\n", expected);
    printf("    Получено:  \"%s\"\n", actual);
  }
}

static void runTestInt(const char *testName, int expected, int actual) {
  g_test_count++;
  printf("  [Тест %d] %s\n", g_test_count, testName);
  if (expected == actual) {
    printf("    \x1b[32mPASS\x1b[0m (Код: %d)\n", actual);
    g_test_passed++;
  } else {
    printf("    \x1b[31mFAIL\x1b[0m\n");
    printf("    Ожидалось: %d\n", expected);
    printf("    Получено:  %d\n", actual);
  }
}

void testAllFlags(void) {
  char buffer[1024];

  printf("========= НАЧАЛО ТЕСТИРОВАНИЯ ФУНКЦИЙ =========\n\n");
  g_test_count = 0;
  g_test_passed = 0;

  printf("--- Тесты Кастомных Флагов ---\n");
  oversprintf(buffer, "Римское 1999: %Ro", 1999);
  runTest("%Ro (Римское)", "Римское 1999: MCMXCIX", buffer);

  oversprintf(buffer, "Цекендорф 17: %Zr", 17);
  runTest("%Zr (Цекендорф)", "Цекендорф 17: 1010011", buffer); // 1+3+13=17

  oversprintf(buffer, "Base16 low: %Cv", 255, 16);
  runTest("%Cv (Base16 low)", "Base16 low: ff", buffer);

  oversprintf(buffer, "Base16 up: %CV", 255, 16);
  runTest("%CV (Base16 up)", "Base16 up: FF", buffer);

  oversprintf(buffer, "Base2 neg: %Cv", -42, 2);
  runTest("%Cv (Base2 neg)", "Base2 neg: -101010", buffer);

  oversprintf(buffer, "From 'ff' base 16: %to", "ff", 16);
  runTest("%to (From Base)", "From 'ff' base 16: 255", buffer);

  oversprintf(buffer, "From '-101010' base 2: %TO", "-101010", 2);
  runTest("%TO (From Base neg)", "From '-101010' base 2: -42", buffer);

  printf("\n--- Тесты Стандартных Флагов (Реализованных Самостоятельно) "
         "---\n");
  oversprintf(buffer, "Int: %d", -123);
  runTest("%d (int)", "Int: -123", buffer);

  oversprintf(buffer, "Unsigned: %u", 456);
  runTest("%u (unsigned)", "Unsigned: 456", buffer);

  oversprintf(buffer, "Hex: %x, HEX: %X, Oct: %o", 255, 255, 255);
  runTest("%x, %X, %o (hex/oct)", "Hex: ff, HEX: FF, Oct: 377", buffer);

  oversprintf(buffer, "Char: %c, String: %s", 'A', "Hello");
  runTest("%c, %s (char/string)", "Char: A, String: Hello", buffer);

  oversprintf(buffer, "Null String: %s", (char *)NULL);
  runTest("%s (null string)", "Null String: (null)", buffer);

  oversprintf(buffer, "Pointer: %p", (void *)0x123ABC);
  runTest("%p (pointer)", "Pointer: 0x123abc", buffer);

  oversprintf(buffer, "Null Pointer: %p", (void *)NULL);
  runTest("%p (null pointer)", "Null Pointer: (nil)", buffer);

  oversprintf(buffer, "Double: %f", 3.141592);
  runTest("%f (double)", "Double: 3.141592", buffer);

  oversprintf(buffer, "Neg Double: %f", -123.456);
  runTest("%f (neg double)", "Neg Double: -123.456000", buffer);

  oversprintf(buffer, "Double rounding: %f", 0.9999999);
  runTest("%f (rounding)", "Double rounding: 1.000000", buffer);

  printf("\n--- Тесты Ошибок и Граничных Случаев ---\n");
  int res = oversprintf(buffer, "%Ro", 4000);
  runTestInt("%Ro (Error > 3999)", -1, res);

  res = oversprintf(buffer, "%to", "gg", 16);
  runTestInt("%to (Invalid input)", -1, res);

  oversprintf(buffer, "Неизвестный флаг: %Qx");
  runTest("Unknown flag %Qx", "Неизвестный флаг: %Qx", buffer);

  oversprintf(buffer, "Неполный флаг: %R");
  runTest("Incomplete flag %R", "Неполный флаг: %R", buffer);

  oversprintf(buffer, "Процент: %%");
  runTest("Percent sign %%", "Процент: %", buffer);

  oversprintf(buffer, "INT_MIN: %d", INT_MIN);
  runTest("INT_MIN %d", "INT_MIN: -2147483648", buffer);

  oversprintf(buffer, "From LLONG_MIN str: %to", "-9223372036854775808", 10);
  runTest("%to (LLONG_MIN)", "From LLONG_MIN str: -9223372036854775808",
          buffer);

  printf("\n----------------------------------------\n");
  printf("  \x1b[1mИтог: %d / %d тестов пройдено\x1b[0m\n", g_test_passed,
         g_test_count);
  printf("========================================\n\n");
}
