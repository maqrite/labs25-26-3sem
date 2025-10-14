#ifndef ACTIONS_H
#define ACTIONS_H

#include <stddef.h>
#include <stdio.h>

typedef enum {
  OK = 0,
  INVALID_INPUT = 1,
  NOT_FOUND = 2,
} StatusCode;

void printErrors(StatusCode status);
void runAllTests(void);

StatusCode myMemchr(const void *str, int c, size_t n, void **result);
StatusCode myMemcmp(const void *str1, const void *str2, size_t n, int *result);
StatusCode myMemcpy(void *dest, const void *src, size_t n);
StatusCode myMemset(void *str, int c, size_t n);
StatusCode myStrncat(char *dest, const char *src, size_t n);
StatusCode myStrchr(const char *str, int c, char **result);
StatusCode myStrncmp(const char *str1, const char *str2, size_t n, int *result);
StatusCode myStrncpy(char *dest, const char *src, size_t n);
StatusCode myStrcspn(const char *str1, const char *str2, size_t *result);
StatusCode myStrerror(int errnum, char **result);
StatusCode myStrlen(const char *str, size_t *result);
StatusCode myStrpbrk(const char *str1, const char *str2, char **result);
StatusCode myStrrchr(const char *str, int c, char **result);
StatusCode myStrstr(const char *haystack, const char *needle, char **result);
StatusCode myStrtok(char *str, const char *delim, char **result);

#endif
