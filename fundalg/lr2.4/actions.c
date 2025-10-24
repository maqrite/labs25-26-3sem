#include "actions.h"
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
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

int getRomanValue(char c) {
  switch (c) {
  case 'I':
    return 1;
  case 'V':
    return 5;
  case 'X':
    return 10;
  case 'L':
    return 50;
  case 'C':
    return 100;
  case 'D':
    return 500;
  case 'M':
    return 1000;
  default:
    return -1;
  }
}

StatusCode convertFromRoman(const char *numStr, int *result) {
  if (numStr == 0 || result == 0) {
    return INVALID_PARAMETER;
  }

  *result = 0;
  int len = strlen(numStr);

  for (int i = 0; i < len; i++) {
    int val1 = getRomanValue(numStr[i]);
    if (val1 == -1) {
      return INVALID_INPUT;
    }

    if (i + 1 < len) {
      int val2 = getRomanValue(numStr[i + 1]);
      if (val2 == -1) {
        return INVALID_INPUT;
      }

      if (val1 < val2) {
        *result += (val2 - val1);
        i++;
      } else {
        *result += val1;
      }

    } else {
      *result += val1;
    }
  }
  return OK;
}

StatusCode convertFromZeck(const char *zeckStr, unsigned int *result) {
  if (zeckStr == 0 || result == 0) {
    return INVALID_PARAMETER;
  }

  int len = strlen(zeckStr);

  if (len == 0 || zeckStr[len - 1] != '1') {
    return INVALID_PARAMETER;
  }

  unsigned int fib[50];
  fib[0] = 1;
  fib[1] = 2;
  int maxFibIndex = 1;

  for (int i = 2; i < 50; i++) {
    if (fib[i - 1] > UINT_MAX - fib[i - 2]) {
      maxFibIndex = i - 1;
      break;
    }

    fib[i] = fib[i - 1] + fib[i - 2];
    maxFibIndex = i;
  }

  *result = 0;

  for (int i = 0; i < len - 1; i++) {
    if (i > maxFibIndex) {
      return INVALID_PARAMETER;
    }

    if (zeckStr[i] == '1') {

      if (*result > UINT_MAX - fib[i]) {
        return INVALID_PARAMETER;
      }

      *result += fib[i];
    } else if (zeckStr[i] != '0') {
      return INVALID_INPUT;
    }
  }

  return OK;
}

int getCharValue(char c, bool uppercase) {

  int val = getCharValueIns(c);

  if (val == -1) {
    return -1;
  }

  if (val < 10) {
    return val;
  }

  if (uppercase) {
    if (c >= 'A' && c <= 'Z') {
      return val;
    }
  } else {
    if (c >= 'a' && c <= 'z') {
      return val;
    }
  }

  return -1;
}

int getCharValueIns(char c) {
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

StatusCode parseInt(const char *token, int base, long long *result) {
  if (token == NULL || result == NULL) {
    return INVALID_PARAMETER;
  }

  long long res = 0;
  bool isNegative = false;
  int i = 0;
  int len = strlen(token);
  if (len == 0) {
    return INVALID_INPUT;
  }

  if (token[0] == '-') {
    isNegative = true;
    i = 1;
  }

  if (base == 16 && (len - i) > 2 && token[i] == '0' &&
      (token[i + 1] == 'x' || token[i + 1] == 'X')) {
    i += 2;
  }

  if (i == len) {
    return INVALID_INPUT;
  }

  for (; i < len; i++) {
    int val = getCharValueIns(token[i]);
    if (val < 0 || val >= base) {
      break;
    }

    if (res > (LLONG_MAX - val) / base) {
      return INVALID_PARAMETER;
    }

    res = res * base + val;
  }

  *result = isNegative ? -res : res;

  return OK;
}

StatusCode parseDouble(const char *token, double *result) {
  if (token == NULL || result == NULL) {
    return INVALID_PARAMETER;
  }

  double res = 0.0;
  bool isNegative = false;
  int i = 0;
  int len = strlen(token);
  if (len == 0) {
    return INVALID_INPUT;
  }

  if (token[0] == '-') {
    isNegative = true;
    i = 1;
  }

  while (i < len && token[i] != '.') {
    int val = getCharValueIns(token[i]);
    if (val < 0 || val >= 10) {
      break;
    }

    res = res * 10 + (double)val;
    i++;
  }

  if (i < len && token[i] == '.') {
    i++;
    double power = 0.1;
    while (i < len) {
      int val = getCharValueIns(token[i]);
      if (val < 0 || val >= 10) {
        break;
      }

      res = res + (double)val * power;
      power /= 10.0;
      i++;
    }
  }

  *result = isNegative ? -res : res;

  return OK;
}

StatusCode parsePointer(const char *token, void **result) {
  if (strcmp(token, "(nil)") == 0) {
    *result = NULL;
    return OK;
  }

  long long val;

  StatusCode s = parseInt(token, 16, &val);
  if (s != OK) {
    return s;
  }

  *result = (void *)(uintptr_t)val;
  return OK;
}

StatusCode convertFromBase(const char *numStr, int base, bool uppercase,
                           long long *result) {

  if (numStr == 0 || result == 0) {
    return INVALID_PARAMETER;
  }

  if (base < 2 || base > 36) {
    base = 10;
  }

  long long res = 0;
  long long power = 1;
  bool isNegative = false;
  int startIndex = 0;
  int len = strlen(numStr);

  if (len == 0) {
    return INVALID_INPUT;
  }

  if (numStr[0] == '-') {
    isNegative = true;
    startIndex = 1;
  }

  for (int i = len - 1; i >= startIndex; i--) {
    int val = getCharValue(numStr[i], uppercase);

    if (val < 0 || val >= base) {
      return INVALID_PARAMETER;
    }

    if (val > 0 && power > LLONG_MAX / val) {
      return INVALID_PARAMETER;
    }

    long long term = val * power;

    if (res > LLONG_MAX - term) {
      return INVALID_PARAMETER;
    }

    res += term;

    if (i > startIndex) {
      if (power > LLONG_MAX / base) {
        return INVALID_PARAMETER;
      }

      power *= base;
    }
  }

  *result = isNegative ? -res : res;

  return OK;
}

StatusCode handleToken(const char *token, const char **format, va_list *args,
                       int *assignments) {
  StatusCode status = OK;

  switch (**format) {
  case 'R':
    if (*(*format + 1) == 'o') {
      (*format)++;
      int *ptr = va_arg(*args, int *);
      int val;
      status = convertFromRoman(token, &val);
      if (status == OK) {
        *ptr = val;
        (*assignments)++;
      } else {
        return status;
      }
    }
    break;

  case 'Z':
    if (*(*format + 1) == 'r') {
      (*format)++;
      unsigned int *ptr = va_arg(*args, unsigned int *);
      unsigned int val;
      status = convertFromZeck(token, &val);
      if (status == OK) {
        *ptr = val;
        (*assignments)++;
      } else {
        return status;
      }
    }
    break;

  case 'C': {
    bool isUpper = (*(*format + 1) == 'V');
    if (isUpper || (*(*format + 1) == 'v')) {
      (*format)++;
      int *ptr = va_arg(*args, int *);
      int base = va_arg(*args, int);
      long long val;
      status = convertFromBase(token, base, isUpper, &val);
      if (status == OK) {
        *ptr = (int)val;
        (*assignments)++;
      } else {
        return status;
      }
    }
    break;
  }

  case 'd':
  case 'i': {
    int *ptr = va_arg(*args, int *);
    long long val;
    status = parseInt(token, 10, &val);
    if (status == OK) {
      *ptr = (int)val;
      (*assignments)++;
    } else {
      return status;
    }
    break;
  }

  case 'u': {
    unsigned int *ptr = va_arg(*args, unsigned int *);
    long long val;
    status = parseInt(token, 10, &val);
    if (status == OK && val >= 0) {
      *ptr = (unsigned int)val;
      (*assignments)++;
    } else {
      return (status != OK) ? status : INVALID_INPUT;
    }
    break;
  }

  case 'x':
  case 'X': {
    unsigned int *ptr = va_arg(*args, unsigned int *);
    long long val;
    status = parseInt(token, 16, &val);
    if (status == OK && val >= 0) {
      *ptr = (unsigned int)val;
      (*assignments)++;
    } else {
      return (status != OK) ? status : INVALID_INPUT;
    }
    break;
  }

  case 'o': {
    unsigned int *ptr = va_arg(*args, unsigned int *);
    long long val;
    status = parseInt(token, 8, &val);
    if (status == OK && val >= 0) {
      *ptr = (unsigned int)val;
      (*assignments)++;
    } else {
      return (status != OK) ? status : INVALID_INPUT;
    }
    break;
  }

  case 'f':
  case 'e':
  case 'g': {
    double *ptr = va_arg(*args, double *);
    status = parseDouble(token, ptr);
    if (status == OK) {
      (*assignments)++;
    } else {
      return status;
    }
    break;
  }

  case 's': {
    char *ptr = va_arg(*args, char *);
    strcpy(ptr, token);
    (*assignments)++;
    break;
  }

  case 'p': {
    void **ptr = va_arg(*args, void **);
    status = parsePointer(token, ptr);
    if (status == OK) {
      (*assignments)++;
    } else {
      return status;
    }
    break;
  }
  }

  (*format)++;
  return OK;
}

int oversscanf(const char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);

  int assignments = 0;
  StatusCode status;
  char token[256];
  const char *pStr = str;

  while (*format) {

    if (isspace(*format)) {
      format++;
      while (*pStr && isspace(*pStr)) {
        pStr++;
      }
      continue;
    }

    if (*format != '%') {
      if (*pStr != *format) {
        break;
      }

      format++;
      pStr++;
      continue;
    }

    format++;

    if (*format == '%') {
      if (*pStr != '%') {
        break;
      }

      format++;
      pStr++;
      continue;
    }

    if (*format == 'c') {
      if (*pStr == '\0') {
        break;
      }

      char *ptr = va_arg(args, char *);
      *ptr = *pStr;
      pStr++;
      assignments++;
      format++;
      continue;
    }

    while (*pStr && isspace(*pStr)) {
      pStr++;
    }

    if (*pStr == '\0') {
      break;
    }

    int tokenIndex = 0;

    while (*pStr != '\0' && !isspace(*pStr) && tokenIndex < 255) {
      token[tokenIndex] = *pStr;
      tokenIndex++;
      pStr++;
    }
    token[tokenIndex] = '\0';

    if (tokenIndex == 0) {
      break;
    }

    status = handleToken(token, &format, &args, &assignments);
    if (status != OK) {
      va_end(args);
      return assignments;
    }
  }

  va_end(args);
  return assignments;
}

int overfscanf(FILE *stream, const char *format, ...) {
  va_list args;
  va_start(args, format);

  int assignments = 0;
  StatusCode status;
  char token[256];

  while (*format) {
    if (isspace(*format)) {
      format++;

      int c;

      while ((c = fgetc(stream)) != EOF && isspace(c)) {
      }

      if (c != EOF) {
        ungetc(c, stream);
      }

      continue;
    }

    if (*format != '%') {
      int c = fgetc(stream);

      if (c == EOF || c != *format) {
        break;
      }

      format++;
      continue;
    }

    format++;

    if (*format == '%') {
      int c = fgetc(stream);
      if (c == EOF || c != '%') {
        break;
      }

      format++;
      continue;
    }

    if (*format == 'c') {
      int c = fgetc(stream);
      if (c == EOF) {
        break;
      }
      char *ptr = va_arg(args, char *);
      *ptr = (char)c;
      assignments++;
      format++;
      continue;
    }

    int c;
    while ((c = fgetc(stream)) != EOF && isspace(c)) {
    }

    // связь с Богом была потеряна

    if (c == EOF) {
      break;
    }

    ungetc(c, stream);

    int tokenIndex = 0;
    while (tokenIndex < 255) {
      c = fgetc(stream);

      if (c == EOF || isspace(c)) {
        if (c != EOF) {
          ungetc(c, stream);
        }
        break;
      }

      token[tokenIndex] = (char)c;
      tokenIndex++;
    }

    token[tokenIndex] = '\0';

    if (tokenIndex == 0) {
      break;
    }

    status = handleToken(token, &format, &args, &assignments);
    if (status != OK) {
      va_end(args);
      return assignments;
    }
  }

  va_end(args);
  return assignments;
}

static int g_test_count = 0;
static int g_test_passed = 0;

static void runTestInt(const char *testName, int expected, int actual) {
  g_test_count++;
  if (expected == actual) {
    printf("  \x1b[32m[PASS]\x1b[0m %s (Ожидалось: %d, Получено: %d)\n",
           testName, expected, actual);
    g_test_passed++;
  } else {
    printf("  \x1b[31m[FAIL]\x1b[0m %s (Ожидалось: %d, Получено: %d)\n",
           testName, expected, actual);
  }
}

static void runTestStr(const char *testName, const char *expected,
                       const char *actual) {
  g_test_count++;
  if (strcmp(expected, actual) == 0) {
    printf("  \x1b[32m[PASS]\x1b[0m %s (Ожидалось: \"%s\", Получено: \"%s\")\n",
           testName, expected, actual);
    g_test_passed++;
  } else {
    printf("  \x1b[31m[FAIL]\x1b[0m %s (Ожидалось: \"%s\", Получено: \"%s\")\n",
           testName, expected, actual);
  }
}

static void runTestDouble(const char *testName, double expected, double actual,
                          double epsilon) {
  g_test_count++;
  if (fabs(expected - actual) < epsilon) {
    printf("  \x1b[32m[PASS]\x1b[0m %s (Ожидалось: %f, Получено: %f)\n",
           testName, expected, actual);
    g_test_passed++;
  } else {
    printf("  \x1b[31m[FAIL]\x1b[0m %s (Ожидалось: %f, Получено: %f)\n",
           testName, expected, actual);
  }
}

void testAllFlags(void) {
  char s_buf[256];
  int i_val1, i_val2, i_val3;
  unsigned int u_val1;
  double d_val1;
  char c_val1, c_val2, c_val3;
  void *p_val1;
  int res;
  int base16 = 16;

  printf("\n========= НАЧАЛО ТЕСТИРОВАНИЯ SCANF =========\n\n");
  g_test_count = 0;
  g_test_passed = 0;

  printf("--- Тестирование oversscanf ---\n");

  const char *str1 = "MCMXCIX 1010011 ff 1A";
  res = oversscanf(str1, "%Ro %Zr %Cv %CV", &i_val1, &u_val1, &i_val2, base16,
                   &i_val3, base16);
  runTestInt("oversscanf: Кастомные флаги (счетчик)", 4, res);
  runTestInt("oversscanf: %Ro (1999)", 1999, i_val1);
  runTestInt("oversscanf: %Zr (17)", 17, u_val1);
  runTestInt("oversscanf: %Cv (ff)", 255, i_val2);
  runTestInt("oversscanf: %CV (1A)", 26, i_val3);

  const char *str2 = "test -123 3.1415 456 ff 777 0xABC (nil)";
  res = oversscanf(str2, "%s %d %f %u %x %o %p %p", s_buf, &i_val1, &d_val1,
                   &u_val1, &i_val2, &i_val3, &p_val1, &p_val1);
  runTestInt("oversscanf: Стандартные флаги (счетчик)", 8, res);
  runTestStr("oversscanf: %s", "test", s_buf);
  runTestInt("oversscanf: %d", -123, i_val1);
  runTestDouble("oversscanf: %f", 3.1415, d_val1, 0.00001);
  runTestInt("oversscanf: %u", 456, u_val1);
  runTestInt("oversscanf: %x (ff)", 255, i_val2);
  runTestInt("oversscanf: %o (777)", 511, i_val3);
  runTestInt("oversscanf: %p (nil)", 1, (p_val1 == NULL));

  const char *str3 = "Value: 42 _ Symbol: A";
  res = oversscanf(str3, "Value: %d %c Symbol: %c", &i_val1, &c_val1, &c_val2);
  runTestInt("oversscanf: Литералы и %c (счетчик)", 3, res);
  runTestInt("oversscanf: %d (42)", 42, i_val1);
  runTestInt("oversscanf: %c 1 (_)", '_', c_val1);
  runTestInt("oversscanf: %c 2 (A)", 'A', c_val2);

  const char *str4 = "Roman: VI Zeck: ZZZ";
  u_val1 = 999;
  res = oversscanf(str4, "Roman: %Ro Zeck: %Zr", &i_val1, &u_val1);
  runTestInt("oversscanf: Ошибка парсинга (счетчик)", 1, res);
  runTestInt("oversscanf: %Ro (VI)", 6, i_val1);
  runTestInt("oversscanf: %Zr (не должен измениться)", 999, u_val1);

  printf("\n--- Тестирование overfscanf ---\n");

  const char *f_str1 = "VI 1011 FF 3.14 -42";
  FILE *f1 = fmemopen((void *)f_str1, strlen(f_str1), "r");
  if (f1 == NULL) {
    printf("  \x1b[31m[FAIL]\x1b[0m fmemopen не удалось, overfscanf не "
           "протестирован\n");
    g_test_count++;
  } else {
    res = overfscanf(f1, "%Ro %Zr %CV %f %d", &i_val1, &u_val1, &i_val2, base16,
                     &d_val1, &i_val3);
    fclose(f1);
    runTestInt("overfscanf: Все флаги (счетчик)", 5, res);
    runTestInt("overfscanf: %Ro (VI)", 6, i_val1);
    runTestInt("overfscanf: %Zr (1011)", 4, u_val1); // 1+3=4
    runTestInt("overfscanf: %CV (FF)", 255, i_val2);
    runTestDouble("overfscanf: %f", 3.14, d_val1, 0.001);
    runTestInt("overfscanf: %d (-42)", -42, i_val3);
  }

  const char *f_str2 = "A B"; //
  FILE *f2 = fmemopen((void *)f_str2, strlen(f_str2), "r");
  if (f2 == NULL) {
    printf(
        "  \x1b[31m[FAIL]\x1b[0m fmemopen не удалось, %%c не протестирован\n");
    g_test_count++;
  } else {
    res = overfscanf(f2, "%c%c%c", &c_val1, &c_val2, &c_val3);
    fclose(f2);
    runTestInt("overfscanf: %c (счетчик)", 3, res);
    runTestInt("overfscanf: %c 1 (A)", 'A', c_val1);
    runTestInt("overfscanf: %c 2 (' ')", ' ', c_val2);
    runTestInt("overfscanf: %c 3 (B)", 'B', c_val3);
  }

  printf("\n----------------------------------------\n");
  if (g_test_passed == g_test_count) {
    printf("  \x1b[1m\x1b[32mВСЕ ТЕСТЫ ПРОЙДЕНЫ (%d / %d)\x1b[0m\n",
           g_test_passed, g_test_count);
  } else {
    printf("  \x1b[1m\x1b[31mПРОВАЛЕНО %d из %d тестов\x1b[0m\n",
           g_test_count - g_test_passed, g_test_count);
  }
  printf("========================================\n\n");
}
