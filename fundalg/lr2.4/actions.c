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
  if (c >= '0' && c <= '9') {
    return c - '0';
  }

  if (uppercase) {
    if (c >= 'A' && c <= 'Z') {
      return c - 'A' + 10;
    }
  } else {
    if (c >= 'a' && c <= 'z') {
      return c - 'a' + 10;
    }
  }

  return -1;
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

    int n = 0;

    while (*pStr && isspace(*pStr)) {
      pStr++;
    }

    if (*pStr == '\0') {
      break;
    }

    sscanf(pStr, "%255s%n", token, &n);
    if (n == 0) {
      break;
    }

    pStr += n;

    switch (*format) {
    case 'R':
      if (*(format + 1) == 'o') {
        format++;
        int *ptr = va_arg(args, int *);
        int val;
        status = convertFromRoman(token, &val);
        if (status == OK) {
          *ptr = val;
          assignments++;
        } else {
          va_end(args);
          return assignments;
        }
      }
      break;

    case 'Z':
      if (*(format + 1) == 'r') {
        format++;
        unsigned int *ptr = va_arg(args, unsigned int *);
        unsigned int val;
        status = convertFromZeck(token, &val);
        if (status == OK) {
          *ptr = val;
          assignments++;
        } else {
          va_end(args);
          return assignments;
        }
      }
      break;

    case 'C': {
      bool isUpper = (*(format + 1) == 'V');
      if (isUpper || (*(format + 1) == 'v')) {
        format++;
        int *ptr = va_arg(args, int *);
        int base = va_arg(args, int);
        long long val;
        status = convertFromBase(token, base, isUpper, &val);
        if (status == OK) {
          *ptr = (int)val;
          assignments++;
        } else {
          va_end(args);
          return assignments;
        }
      }
      break;
    }
    }
    format++;
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

    if (fscanf(stream, "%255s", token) != 1) {
      break;
    }

    switch (*format) {
    case 'R':
      if (*(format + 1) == 'o') {
        format++;
        int *ptr = va_arg(args, int *);
        int val;
        status = convertFromRoman(token, &val);
        if (status == OK) {
          *ptr = val;
          assignments++;
        } else {
          va_end(args);
          return assignments;
        }
      }
      break;

    case 'Z':
      if (*(format + 1) == 'r') {
        format++;
        unsigned int *ptr = va_arg(args, unsigned int *);
        unsigned int val;
        status = convertFromZeck(token, &val);
        if (status == OK) {
          *ptr = val;
          assignments++;
        } else {
          va_end(args);
          return assignments;
        }
      }
      break;

    case 'C': {
      bool isUpper = (*(format + 1) == 'V');
      if (isUpper || (*(format + 1) == 'v')) {
        format++;
        int *ptr = va_arg(args, int *);
        int base = va_arg(args, int);
        long long val;
        status = convertFromBase(token, base, isUpper, &val);
        if (status == OK) {
          *ptr = (int)val;
          assignments++;
        } else {
          va_end(args);
          return assignments;
        }
      }
      break;
    }
    }

    format++;
  }

  va_end(args);
  return assignments;
}

void testAllFlags(void) {
  printf("\n========= НАЧАЛО ТЕСТИРОВАНИЯ SCANF =========\n\n");

  int i_val1, i_val2, i_val3;
  unsigned int u_val1;
  int res;

  printf("--- Тест 1: oversscanf (комплексный) ---\n");

  const char *str1 = "MCMXCIX 1010011 ff 1A";
  int base16 = 16;

  res = oversscanf(str1, "%Ro %Zr %Cv %CV", &i_val1, &u_val1, &i_val2, base16,
                   &i_val3, base16);
  printf("Строка: '%s'\n", str1);
  printf("Формат: '%%Ro %%Zr %%Cv %%CV' (base16, base16)\n");
  printf("Ожидаемый результат: 1999, 17, 255, 26\n");
  printf("Получено:            %d, %u, %d, %d\n", i_val1, u_val1, i_val2,
         i_val3);
  printf("Кол-во присваиваний: %d (ожидалось 4)\n\n", res);

  printf("--- Тест 2: oversscanf (литералы и разные СС) ---\n");

  const char *str2 = "Roman: XLII Zeck: 11 Bin: 10110 Oct: 777";
  int base2 = 2;
  int base8 = 8;

  res = oversscanf(str2, "Roman: %Ro Zeck: %Zr Bin: %Cv Oct: %Cv", &i_val1,
                   &u_val1, &i_val2, base2, &i_val3, base8);

  printf("Строка: '%s'\n", str2);
  printf(
      "Формат: 'Roman: %%Ro Zeck: %%Zr Bin: %%Cv Oct: %%Cv' (base2, base8)\n");
  printf("Ожидаемый результат: 42, 1, 22, 511\n");
  printf("Получено:            %d, %u, %d, %d\n", i_val1, u_val1, i_val2,
         i_val3);
  printf("Кол-во присваиваний: %d (ожидалось 4)\n\n", res);

  printf("--- Тест 3: oversscanf (ошибка парсинга) ---\n");
  const char *str3 = "Roman: VI Zeck: ZZZ";
  u_val1 = 0;

  res = oversscanf(str3, "Roman: %Ro Zeck: %Zr", &i_val1, &u_val1);

  printf("Строка: '%s'\n", str3);
  printf("Формат: 'Roman: %%Ro Zeck: %%Zr'\n");
  printf("Ожидаемый результат: i_val1=6, u_val1=0 (не изм.), res=1\n");
  printf("Получено:            i_val1=%d, u_val1=%u\n", i_val1, u_val1);
  printf("Кол-во присваиваний: %d (ожидалось 1)\n\n", res);

  printf("--- Тест 4: overfscanf (stdin) ---\n");
  printf("Пожалуйста, введите три значения, разделенных пробелом:\n");
  printf("1. Римское число (напр. VI)\n");
  printf("2. Число Цекендорфа (напр. 1011)\n");
  printf("3. Шестнадцатеричное число (UPPERCASE, напр. FF)\n");
  printf("Ввод: ");

  res = overfscanf(stdin, "%Ro %Zr %CV", &i_val1, &u_val1, &i_val2, base16);

  printf("\n--- Результат overfscanf ---\n");
  printf("Прочитано: %d элементов\n", res);
  printf("%%Ro -> %d\n", i_val1);
  printf("%%Zr -> %u\n", u_val1);
  printf("%%CV (base 16) -> %d\n", i_val2);

  printf("\n========= ТЕСТИРОВАНИЕ SCANF ЗАВЕРШЕНО =========\n");
}
