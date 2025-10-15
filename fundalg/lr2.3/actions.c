#include "actions.h"

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

        break;
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
          char *dumpStr = NULL;
          status = dumpMemory(ptr, dataSize, &dumpStr);
          if (status != OK) {
            va_end(args);
            return -1;
          }

          strcpy(pStr, dumpStr);
          int len = strlen(dumpStr);
          pStr += len;
          totalWritten += len;

          free(dumpStr);
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
        if (*(format + 1) == 'r') {
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

          int writtenNow = fprintf(stream, "%lld", decRes);
          if (writtenNow > 0) {
            totalWritten += writtenNow;
          }
        }

        break;
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
          char *dumpStr = NULL;
          status = dumpMemory(ptr, dataSize, &dumpStr);
          if (status != OK) {
            va_end(args);
            return -1;
          }

          fputs(dumpStr, stream);
          totalWritten += strlen(dumpStr);

          free(dumpStr);
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

void testAllFlags(void) {
  char buffer[1024];
  printf("========= НАЧАЛО ТЕСТИРОВАНИЯ ФУНКЦИЙ =========\n\n");

  printf("--- Тест %%Ro ---\n");
  overfprintf(stdout, "Число 1999 -> %Ro\n", 1999);
  oversprintf(buffer, "Число 42 -> %Ro | Число 3999 -> %Ro", 42, 3999);
  printf("%s\n\n", buffer);

  printf("--- Тест %%Zr ---\n");
  overfprintf(stdout, "Число 17 -> %Zr\n",
              17); // 13+3+1 = F_7+F_4+F_2 -> 1010011
  oversprintf(buffer, "Число 100 -> %Zr | Число 0 -> %Zr", 100, 0);
  printf("%s\n\n", buffer);

  printf("--- Тест %%Cv и %%CV ---\n");
  overfprintf(stdout, "Число 255 (base 16, low): %Cv\n", 255, 16);
  overfprintf(stdout, "Число 255 (base 16, up): %CV\n", 255, 16);
  overfprintf(stdout, "Число -42 (base 2): %Cv\n", -42, 2);
  oversprintf(buffer, "Число 12345 (base 36, up): %CV", 12345, 36);
  printf("%s\n\n", buffer);

  printf("--- Тест %%to и %%TO ---\n");
  overfprintf(stdout, "Строка 'ff' (base 16) -> %to\n", "ff", 16);
  oversprintf(buffer,
              "Строка 'FF' (base 16) -> %TO | Строка '-101010' (base 2) -> %to",
              "FF", 16, "-101010", 2);
  printf("%s\n\n", buffer);

  printf("--- Тест дампов памяти ---\n");
  int signed_int = -1;
  unsigned int unsigned_int = 255;
  double dbl = 3.14;
  float flt = 1.0f / 3.0f;
  overfprintf(stdout, "int (-1): %mi\n", signed_int);
  overfprintf(stdout, "uint (255): %mu\n", unsigned_int);
  overfprintf(stdout, "double (3.14): %md\n", dbl);
  overfprintf(stdout, "float (1/3): %mf\n\n", flt);

  printf("--- Тест некорректных и граничных случаев ---\n");

  overfprintf(stdout, "Неизвестный флаг %%Qx -> %Qx\n");

  overfprintf(stdout, "Неполный флаг %%R -> %R\n");

  int res = overfprintf(stdout, "Строка 'gg' (base 16) -> %to\n", "gg", 16);
  if (res == -1) {
    printf("Функция %%to вернула ошибку, как и ожидалось.\n");
  }

  res = overfprintf(stdout, "Число 4000 -> %Ro\n", 4000);
  if (res == -1) {
    printf("Функция %%Ro вернула ошибку, как и ожидалось.\n");
  }

  overfprintf(stdout, "Число 123 (base 99) -> %Cv\n", 123, 99);

  printf("\n========= ТЕСТИРОВАНИЕ ЗАВЕРШЕНО =========\n");
}
