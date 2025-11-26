#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "actions.h"
#include <stdbool.h>

#define VAR_COUNT 26

typedef struct {
  long long variables[VAR_COUNT];
  bool isInit[VAR_COUNT];
  FILE *logFile;
  int commandCount;
} InterpreterState;

StatusCode initializeInterpreter(InterpreterState *state,
                                 const char *logFileName);
StatusCode precessCommand(InterpreterState *state, const char *commandLine);
void destroyInterpreter(InterpreterState *state);

#endif
