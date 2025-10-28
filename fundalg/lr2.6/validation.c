#include "validation.h"

int isAlphaString(const char *str) {
  if (!str || str[0] == '\0') {
    return 0;
  }

  for (size_t i = 0; str[i] != '\0'; i++) {
    if (!isalpha((unsigned char)str[i])) {
      return 0;
    }
  }

  return 1;
}

int isNonEmptyString(const char *str) { return (str && str[0] != '\0'); }
