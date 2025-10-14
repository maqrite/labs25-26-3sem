#include "actions.h"
#include <string.h> //исключительно для тестов)))

#if defined(__APPLE__) && defined(__MACH__)
#define MAX_ERRNO 106
const char *const ERROR_LIST[MAX_ERRNO + 2] = {
    "Undefined error: 0",
    "Operation not permitted",
    "No such file or directory",
    "No such process",
    "Interrupted system call",
    "Input/output error",
    "Device not configured",
    "Argument list too long",
    "Exec format error",
    "Bad file descriptor",
    "No child processes",
    "Resource deadlock avoided",
    "Cannot allocate memory",
    "Permission denied",
    "Bad address",
    "Block device required",
    "Device / Resource busy",
    "File exists",
    "Cross-device link",
    "Operation not supported by device",
    "Not a directory",
    "Is a directory",
    "Invalid argument",
    "Too many open files in system",
    "Too many open files",
    "Inappropriate ioctl for device",
    "Text file busy",
    "File too large",
    "No space left on device",
    "Illegal seek",
    "Read-only file system",
    "Too many links",
    "Broken pipe",
    "Numerical argument out of domain",
    "Result too large",
    "Resource temporarily unavailable",
    "Operation now in progress",
    "Operation already in progress",
    "Socket operation on non-socket",
    "Destination address required",
    "Message too long",
    "Protocol wrong type for socket",
    "Protocol not available",
    "Protocol not supported",
    "Socket type not supported",
    "Operation not supported",
    "Protocol family not supported",
    "Address family not supported by protocol family",
    "Address already in use",
    "Can't assign requested address",
    "Network is down",
    "Network is unreachable",
    "Network dropped connection on reset",
    "Software caused connection abort",
    "Connection reset by peer",
    "No buffer space available",
    "Socket is already connected",
    "Socket is not connected",
    "Can't send after socket shutdown",
    "Too many references: can't splice",
    "Operation timed out",
    "Connection refused",
    "Too many levels of symbolic links",
    "File name too long",
    "Host is down",
    "No route to host",
    "Directory not empty",
    "Too many processes",
    "Too many users",
    "Disc quota exceeded",
    "Stale NFS file handle",
    "Too many levels of remote in path",
    "RPC struct is bad",
    "RPC version wrong",
    "RPC prog. not avail",
    "Program version wrong",
    "Bad procedure for program",
    "No locks available",
    "Function not implemented",
    "Inappropriate file type or format",
    "Authentication error",
    "Need authenticator",
    "Device power is off",
    "Device error",
    "Value too large to be stored in data type",
    "Bad executable (or shared library)",
    "Bad CPU type in executable",
    "Shared library version mismatch",
    "Malformed Mach-o file",
    "Operation canceled",
    "Identifier removed",
    "No message of desired type",
    "Illegal byte sequence",
    "Attribute not found",
    "Bad message",
    "EMULTIHOP (Reserved)",
    "No data available",
    "No link (Reserved)",
    "No stream resources",
    "Not a stream",
    "Protocol error",
    "STREAM ioctl timeout",
    "Operation not supported on socket",
    "Policy not found",
    "State not recoverable",
    "Previous owner died",
    "Interface output queue is full",
    "Authentication error"};

#elif defined(__linux__)
#define MAX_ERRNO 133
const char *const ERROR_LIST[MAX_ERRNO + 1] = {
    "Success",
    "Operation not permitted",
    "No such file or directory",
    "No such process",
    "Interrupted system call",
    "Input/output error",
    "No such device or address",
    "Argument list too long",
    "Exec format error",
    "Bad file descriptor",
    "No child processes",
    "Resource temporarily unavailable",
    "Cannot allocate memory",
    "Permission denied",
    "Bad address",
    "Block device required",
    "Device or resource busy",
    "File exists",
    "Invalid cross-device link",
    "No such device",
    "Not a directory",
    "Is a directory",
    "Invalid argument",
    "Too many open files in system",
    "Too many open files",
    "Inappropriate ioctl for device",
    "Text file busy",
    "File too large",
    "No space left on device",
    "Illegal seek",
    "Read-only file system",
    "Too many links",
    "Broken pipe",
    "Numerical argument out of domain",
    "Numerical result out of range",
    "Resource deadlock avoided",
    "File name too long",
    "No record locks available",
    "Function not implemented",
    "Directory not empty",
    "Too many symbolic links encountered",
    "Unknown error 41",
    "No message of desired type",
    "Identifier removed",
    "Channel number out of range",
    "Level 2 not synchronized",
    "Level 3 halted",
    "Level 3 reset",
    "Link number out of range",
    "Protocol driver not attached",
    "No CSI structure available",
    "Level 2 halted",
    "Invalid exchange",
    "Invalid request descriptor",
    "Exchange full",
    "No anode",
    "Invalid request code",
    "Invalid slot",
    "Unknown error 58",
    "Bad font file format",
    "Device not a stream",
    "No data available",
    "Timer expired",
    "Out of streams resources",
    "Machine is not on the network",
    "Package not installed",
    "Object is remote",
    "Link has been severed",
    "Advertise error",
    "Srmount error",
    "Communication error on send",
    "Protocol error",
    "Multihop attempted",
    "RFS specific error",
    "Bad message",
    "Value too large for defined data type",
    "Name not unique on network",
    "File descriptor in bad state",
    "Remote address changed",
    "Can not access a needed shared library",
    "Accessing a corrupted shared library",
    ".lib section in a.out corrupted",
    "Attempting to link in too many shared libraries",
    "Cannot exec a shared library directly",
    "Illegal byte sequence",
    "Interrupted system call should be restarted",
    "Streams pipe error",
    "Too many users",
    "Socket operation on non-socket",
    "Destination address required",
    "Message too long",
    "Protocol wrong type for socket",
    "Protocol not available",
    "Protocol not supported",
    "Socket type not supported",
    "Operation not supported",
    "Protocol family not supported",
    "Address family not supported by protocol",
    "Address already in use",
    "Cannot assign requested address",
    "Network is down",
    "Network is unreachable",
    "Network dropped connection on reset",
    "Software caused connection abort",
    "Connection reset by peer",
    "No buffer space available",
    "Transport endpoint is already connected",
    "Transport endpoint is not connected",
    "Cannot send after transport endpoint shutdown",
    "Too many references: cannot splice",
    "Connection timed out",
    "Connection refused",
    "Host is down",
    "No route to host",
    "Operation already in progress",
    "Operation now in progress",
    "Stale file handle",
    "Structure needs cleaning",
    "Not a XENIX named type file",
    "No XENIX semaphores available",
    "Is a named type file",
    "Remote I/O error",
    "Quota exceeded",
    "No medium found",
    "Wrong medium type",
    "Operation canceled",
    "Required key not available",
    "Key has expired",
    "Key has been revoked",
    "Key was rejected by service",
    "Owner died",
    "State not recoverable",
    "Operation not possible due to RF-kill",
    "Memory page has hardware error"};
#else
#define MAX_ERRNO 0
const char *const ERROR_LIST[MAX_EEMAX_ERRNO + 1] = {"usopported OS"};
#endif

void printErrors(StatusCode status) {
  switch (status) {
  case INVALID_INPUT:
    printf("ошибка ввода\n");
    break;

  case NOT_FOUND:
    printf("искомый элемент не найден\n");
    break;

  default:
    break;
  }
}

StatusCode myMemchr(const void *str, int c, size_t n, void **result) {

  if (str == NULL || result == NULL) {
    return INVALID_INPUT;
  }

  const unsigned char *p = (const unsigned char *)str;
  unsigned char ch = (unsigned char)c;

  *result = NULL;

  for (size_t i = 0; i < n; i++) {
    if (p[i] == ch) {
      *result = (void *)(p + i);
      break;
    }
  }

  if (*result != NULL) {
    return OK;
  } else {
    return NOT_FOUND;
  }
}

StatusCode myMemcmp(const void *str1, const void *str2, size_t n, int *result) {
  if (str1 == NULL || str2 == NULL || result == NULL) {
    return INVALID_INPUT;
  }

  const unsigned char *p1 = (const unsigned char *)str1;
  const unsigned char *p2 = (const unsigned char *)str2;

  for (size_t i = 0; i < n; i++) {
    if (p1[i] != p2[i]) {
      *result = p1[i] - p2[i];
      return OK;
    }
  }

  *result = 0;

  return OK;
}

StatusCode myMemcpy(void *dest, const void *src, size_t n) {
  if (dest == NULL || src == NULL) {
    return INVALID_INPUT;
  }

  char *pDest = (char *)dest;
  const char *pSrc = (const char *)src;

  for (size_t i = 0; i < n; i++) {
    pDest[i] = pSrc[i];
  }

  return OK;
}

StatusCode myMemset(void *str, int c, size_t n) {
  if (str == NULL) {
    return INVALID_INPUT;
  }

  unsigned char *pStr = (unsigned char *)str;
  unsigned char value = (unsigned char)c;

  for (size_t i = 0; i < n; i++) {
    pStr[i] = value;
  }

  return OK;
}

StatusCode myStrncat(char *dest, const char *src, size_t n) {
  if (dest == NULL || src == NULL) {
    return INVALID_INPUT;
  }

  char *pDest = dest;

  while (*pDest != '\0') {
    pDest++;
  }

  size_t i = 0;

  while (i < n && src[i] != '\0') {
    pDest[i] = src[i];
    i++;
  }

  pDest[i] = '\0';

  return OK;
}

StatusCode myStrchr(const char *str, int c, char **result) {
  if (str == NULL || result == NULL) {
    return INVALID_INPUT;
  }

  *result = NULL;
  char targetChar = (char)c;

  const char *pStr = str;

  while (*pStr != '\0') {
    if (*pStr == targetChar) {
      *result = (char *)pStr;
      break;
    }
    pStr++;
  }

  if (targetChar == '\0' && *pStr == '\0') {
    *result = (char *)pStr;
  }

  return (*result != NULL) ? OK : NOT_FOUND;
}

StatusCode myStrncmp(const char *str1, const char *str2, size_t n,
                     int *result) {
  if (str1 == NULL || str2 == NULL || result == NULL) {
    return INVALID_INPUT;
  }

  if (n == 0) {
    *result = 0;
    return OK;
  }

  size_t i = 0;

  while (i < n - 1 && str1[i] != '\0' && str1[i] == str2[i]) {
    i++;
  }

  *result = (unsigned char)str1[i] - (unsigned char)str2[i];

  return OK;
}

StatusCode myStrncpy(char *dest, const char *src, size_t n) {
  if (dest == NULL || src == NULL) {
    return INVALID_INPUT;
  }

  size_t i;

  for (i = 0; i < n && src[i] != '\0'; i++) {
    dest[i] = src[i];
  }

  while (i < n) {
    dest[i] = '\0';
    i++;
  }

  return OK;
}

StatusCode myStrcspn(const char *str1, const char *str2, size_t *result) {
  if (str1 == NULL || str2 == NULL || result == NULL) {
    return INVALID_INPUT;
  }

  size_t length = 0;
  const char *p1 = str1;

  while (*p1 != '\0') {
    const char *p2 = str2;
    int charFoundInStr2 = 0;

    while (*p2 != '\0') {
      if (*p1 == *p2) {
        charFoundInStr2 = 1;
        break;
      }
      p2++;
    }

    if (charFoundInStr2) {
      break;
    }

    length++;
    p1++;
  }

  *result = length;

  return OK;
}

StatusCode myStrerror(int errnum, char **result) {
  if (result == NULL) {
    return INVALID_INPUT;
  }

  static char unknownErrorMsg[50];

  if (errnum >= 0 && errnum <= MAX_ERRNO) {
    *result = (char *)ERROR_LIST[errnum];
  } else {
    snprintf(unknownErrorMsg, sizeof(unknownErrorMsg), "неизвестная ошибка: %d",
             errnum);
    *result = unknownErrorMsg;
  }

  return OK;
}

StatusCode myStrlen(const char *str, size_t *result) {
  if (str == NULL || result == NULL) {
    return INVALID_INPUT;
  }

  size_t length = 0;

  while (str[length] != '\0') {
    length++;
  }

  *result = length;

  return OK;
}

StatusCode myStrpbrk(const char *str1, const char *str2, char **result) {
  if (str1 == NULL || str2 == NULL || result == NULL) {
    return INVALID_INPUT;
  }

  for (const char *p1 = str1; *p1 != '\0'; p1++) {

    for (const char *p2 = str2; *p2 != '\0'; p2++) {

      if (*p1 == *p2) {
        *result = (char *)p1;
        return OK;
      }
    }
  }

  *result = NULL;

  return NOT_FOUND;
}

StatusCode myStrrchr(const char *str, int c, char **result) {
  if (str == NULL || result == NULL) {
    return INVALID_INPUT;
  }

  *result = NULL;
  char targetChar = (char)c;

  const char *pStr = str;

  while (*pStr != '\0') {
    if (*pStr == targetChar) {
      *result = (char *)pStr;
    }

    pStr++;
  }

  if (targetChar == '\0') {
    *result = (char *)pStr;
  }

  return (*result != NULL) ? OK : NOT_FOUND;
}

StatusCode myStrstr(const char *haystack, const char *needle, char **result) {
  if (haystack == NULL || needle == NULL || result == NULL) {
    return INVALID_INPUT;
  }

  if (*needle == '\0') {
    *result = (char *)haystack;
    return OK;
  }

  for (const char *h = haystack; *h != '\0'; h++) {
    const char *hRunner = h;
    const char *nRunner = needle;

    while (*hRunner != '\0' && *nRunner != '\0' && *hRunner == *nRunner) {
      hRunner++;
      nRunner++;
    }

    if (*nRunner == '\0') {
      *result = (char *)h;
      return OK;
    }
  }

  *result = NULL;
  return NOT_FOUND;
}

static int isDelim(char c, const char *delim) {
  while (*delim != '\0') {
    if (c == *delim) {
      return 1;
    }
    delim++;
  }
  return 0;
}

StatusCode myStrtok(char *str, const char *delim, char **result) {
  if (delim == NULL || result == NULL) {
    return INVALID_INPUT;
  }

  static char *savePtr;

  char *tokenStart = (str != NULL) ? str : savePtr;

  while (*tokenStart != '\0' && isDelim(*tokenStart, delim)) {
    tokenStart++;
  }

  if (*tokenStart == '\0') {
    *result = NULL;
    return NOT_FOUND;
  }

  char *tokenEnd = tokenStart;

  while (*tokenEnd != '\0' && !isDelim(*tokenEnd, delim)) {
    tokenEnd++;
  }

  if (*tokenEnd != '\0') {
    *tokenEnd = '\0';
    savePtr = tokenEnd + 1;
  } else {
    savePtr = tokenEnd;
  }

  *result = tokenStart;

  return OK;
}

void runAllTests(void) {
  StatusCode status;

  printf("--- 1. Тестирование myMemchr ---\n");
  {
    const char *str = "Hello World";
    void *res = NULL;
    status = myMemchr(str, 'W', 11, &res);
    printf("Поиск 'W': %s\n",
           (status == OK && strcmp(res, "World") == 0) ? "УСПЕХ" : "ПРОВАЛ");
    status = myMemchr(str, 'z', 11, &res);
    printf("Поиск 'z': %s\n", (status == NOT_FOUND) ? "УСПЕХ" : "ПРОВАЛ");
  }
  printf("\n");

  printf("--- 2. Тестирование myMemcmp ---\n");
  {
    int res = 0;
    status = myMemcmp("abc", "abd", 3, &res);
    printf("Сравнение 'abc' и 'abd': %s\n",
           (status == OK && res < 0) ? "УСПЕХ" : "ПРОВАЛ");
    status = myMemcmp("abc", "abc", 3, &res);
    printf("Сравнение 'abc' и 'abc': %s\n",
           (status == OK && res == 0) ? "УСПЕХ" : "ПРОВАЛ");
  }
  printf("\n");

  printf("--- 3. Тестирование myMemcpy ---\n");
  {
    char dest[10] = "";
    status = myMemcpy(dest, "test", 5); // Копируем 4 символа + '\0'
    printf("Копирование 'test': %s\n",
           (status == OK && strcmp(dest, "test") == 0) ? "УСПЕХ" : "ПРОВАЛ");
  }
  printf("\n");

  printf("--- 4. Тестирование myMemset ---\n");
  {
    char str[] = "aaaaa";
    myMemset(str, 'b', 3);
    printf("Заполнение 'b': %s\n",
           (strcmp(str, "bbbaa") == 0) ? "УСПЕХ" : "ПРОВАЛ");
  }
  printf("\n");

  printf("--- 5. Тестирование myStrncat ---\n");
  {
    char dest[20] = "Hello ";
    myStrncat(dest, "World!", 3);
    printf("Конкатенация 3 символов: %s\n",
           (strcmp(dest, "Hello Wor") == 0) ? "УСПЕХ" : "ПРОВАЛ");
    strcpy(dest, "Hello ");
    myStrncat(dest, "World!", 10);
    printf("Полная конкатенация: %s\n",
           (strcmp(dest, "Hello World!") == 0) ? "УСПЕХ" : "ПРОВАЛ");
  }
  printf("\n");

  printf("--- 6. Тестирование myStrchr ---\n");
  {
    char *res = NULL;
    const char *str = "test";
    myStrchr(str, 's', &res);
    printf("Поиск 's': %s\n", (strcmp(res, "st") == 0) ? "УСПЕХ" : "ПРОВАЛ");
  }
  printf("\n");

  printf("--- 7. Тестирование myStrncmp ---\n");
  {
    int res = 0;
    myStrncmp("test", "tesT", 4, &res);
    printf("Сравнение 'test' и 'tesT': %s\n", (res > 0) ? "УСПЕХ" : "ПРОВАЛ");
    myStrncmp("test", "tesT", 3, &res);
    printf("Сравнение первых 3 символов: %s\n",
           (res == 0) ? "УСПЕХ" : "ПРОВАЛ");
  }
  printf("\n");

  printf("--- 8. Тестирование myStrncpy ---\n");
  {
    char dest[10] = "xxxxxxxxx";
    myStrncpy(dest, "abc", 5);
    printf("Копирование короткой строки: %s\n",
           (dest[0] == 'a' && dest[3] == '\0' && dest[4] == '\0') ? "УСПЕХ"
                                                                  : "ПРОВАЛ");
    myStrncpy(dest, "abcdefgh", 5);
    dest[5] = '\0';
    printf("Копирование длинной строки: %s\n",
           (strcmp(dest, "abcde") == 0) ? "УСПЕХ" : "ПРОВАЛ");
  }
  printf("\n");

  printf("--- 9. Тестирование myStrcspn ---\n");
  {
    size_t len = 0;
    myStrcspn("find the char", "xyz", &len);
    printf("Нет совпадений: %s\n", (len == 13) ? "УСПЕХ" : "ПРОВАЛ");
    myStrcspn("find the char", " tc", &len);
    printf("Есть совпадения: %s\n", (len == 4) ? "УСПЕХ" : "ПРОВАЛ");
  }
  printf("\n");
  printf("--- 10. Тестирование myStrerror ---\n");
  {
    char *err_msg = NULL;
    myStrerror(2, &err_msg);
    printf("Ошибка #2: %s\n",
           (err_msg != NULL && strstr(err_msg, "file or directory") != NULL)
               ? "УСПЕХ"
               : "ПРОВАЛ");
    myStrerror(999, &err_msg);
    printf("Ошибка #999: %s\n",
           (strstr(err_msg, "неизвестная ошибка: 999") != NULL) ? "УСПЕХ"
                                                                : "ПРОВАЛ");
  }
  printf("\n");

  printf("--- 11. Тестирование myStrlen ---\n");
  {
    size_t len = 0;
    myStrlen("hello", &len);
    printf("Длина 'hello': %s\n", (len == 5) ? "УСПЕХ" : "ПРОВАЛ");
    myStrlen("", &len);
    printf("Длина пустой строки: %s\n", (len == 0) ? "УСПЕХ" : "ПРОВАЛ");
  }
  printf("\n");

  printf("--- 12. Тестирование myStrpbrk ---\n");
  {
    char *res = NULL;
    myStrpbrk("hello world", "xr w", &res);
    printf("Поиск любого из 'xr w': %s\n",
           (res != NULL && strcmp(res, " world") == 0) ? "УСПЕХ" : "ПРОВАЛ");
  }
  printf("\n");

  printf("--- 13. Тестирование myStrrchr ---\n");
  {
    char *res = NULL;
    myStrrchr("hello world", 'l', &res);
    printf("Поиск последней 'l': %s\n",
           (strcmp(res, "ld") == 0) ? "УСПЕХ" : "ПРОВАЛ");
  }
  printf("\n");

  printf("--- 14. Тестирование myStrstr ---\n");
  {
    char *res = NULL;
    myStrstr("this is a test", "is a", &res);
    printf("Поиск подстроки 'is a': %s\n",
           (strcmp(res, "is a test") == 0) ? "УСПЕХ" : "ПРОВАЛ");
    status = myStrstr("this is a test", "notfound", &res);
    printf("Поиск несуществующей подстроки: %s\n",
           (status == NOT_FOUND) ? "УСПЕХ" : "ПРОВАЛ");
  }
  printf("\n");

  printf("--- 15. Тестирование myStrtok ---\n");
  {
    char str[] = "tok1,tok2.tok3";
    char *res = NULL;
    int count = 0;
    myStrtok(str, ",.", &res);
    if (res != NULL && strcmp(res, "tok1") == 0)
      count++;
    myStrtok(NULL, ",.", &res);
    if (res != NULL && strcmp(res, "tok2") == 0)
      count++;
    myStrtok(NULL, ",.", &res);
    if (res != NULL && strcmp(res, "tok3") == 0)
      count++;
    status = myStrtok(NULL, ",.", &res);
    printf("Разбиение на токены: %s\n",
           (count == 3 && status == NOT_FOUND) ? "УСПЕХ" : "ПРОВАЛ");
  }
  printf("\n======= ТЕСТЫ ЗАВЕРШЕНЫ =======\n");
}
