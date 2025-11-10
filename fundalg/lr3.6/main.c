#include "actions.h"
#include <stdio.h>
#include <string.h>

#define MAX_BUFFER 1024

int main() {
  char buffer[MAX_BUFFER];

  if (fgets(buffer, MAX_BUFFER, stdin) == NULL) {
    return 1;
  }

  buffer[strcspn(buffer, "\n")] = 0;

  StatusCode status = check_brackets(buffer);

  if (status == OK) {
    printf("OK\n");
  } else {
    printf("Error\n");
  }

  return 0;
}
