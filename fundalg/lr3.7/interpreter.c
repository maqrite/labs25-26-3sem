#include "interpreter.h"
#include "actions.h"
#include "stack.h"
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define ll long long

int getPrecedence(char op) {
  if (op == '+' || op == '-') {
    return 1;
  }

  if (op == '*' || op == '/') {
    return 2;
  }

  if (op == '^') {
    return 3;
  }

  return 0;
}

bool isOperator(char op) {
  return op == '+' || op == '-' || op == '*' || op == '/' || op == '^';
}

StatusCode evaluateOpertion(long long operand1, long long operand2, char op,
                            long long *result) {
  switch (op) {
  case '+':
    *result = operand1 + operand2;
    break;

  case '-':
    *result = operand1 - operand2;
    break;

  case '*':
    *result = operand1 * operand2;
    break;

  case '/':
    if (operand2 == 0) {
      return DIVISION_BY_ZERO;
    }
    *result = operand1 / operand2;
    break;

  case '^':
    if (operand2 < 0) {
      if (operand1 == 1) {
        *result = 1;
      } else if (operand1 == -1) {
        *result = (operand2 % 2 == 0) ? 1 : -1;
      } else {
        *result = 0;
      }
    } else {
      ll res = 1;
      ll base = operand1;
      ll exp = operand2;
      while (exp > 0) {
        if (exp % 2 == 1) {
          res *= base;
        }
        base *= base;
        exp /= 2;
      }
      *result = res;
    }
    break;

  default:
    return UNEXPECTED_TOKEN;
  }

  return OK;
}

StatusCode logState(InterpreterState *state, const char *command,
                    const char *operationType) {
  if (state == NULL || state->logFile == NULL) {
    return FILE_OPEN_ERROR;
  }

  fprintf(state->logFile, "[%d] %-25s | ", state->commandCount, command);

  bool firstVar = true;
  for (int i = 0; i < VAR_COUNT; i++) {
    if (state->isInit[i]) {
      if (!firstVar) {
        fprintf(state->logFile, ", ");
      }
      fprintf(state->logFile, "%c=%lld", 'A' + i, state->variables[i]);
      firstVar = false;
    }
  }

  fprintf(state->logFile, " | %s\n", operationType);
  fflush(state->logFile);
  return OK;
}
