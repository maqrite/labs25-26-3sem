#include "actions.h"
#include "interpreter.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 256
#define LOG_FILE_NAME "trace.log"

int main(void) {
  InterpreterState state;
  StatusCode status = initializeInterpreter(&state, LOG_FILE_NAME);

  if (status != OK) {
    printErrors(status);
    return status;
  }

  printf(
      "Введите команды (каждая с новой строки). Введите 'quit' для выхода.\n");

  char inputLine[MAX_LINE_LENGTH];

  while (1) {
    printf("> ");
    if (fgets(inputLine, MAX_LINE_LENGTH, stdin) == NULL) {
      break;
    }

    size_t len = strlen(inputLine);
    if (len > 0 && inputLine[len - 1] == '\n') {
      inputLine[len - 1] = '\0';
    }

    if (strcmp(inputLine, "quit") == 0) {
      break;
    }

    status = processCommand(&state, inputLine);

    if (status != OK) {
      printErrors(status);
    }
  }

  destroyInterpreter(&state);

  return 0;
}
