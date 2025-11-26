#include "interpreter.h"
#include "actions.h"
#include "stack.h"
#include <ctype.h>
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

StatusCode infixToRPN(const char *expression, Stack *outputStack,
                      Stack *operatorStack) {
  const char *p = expression;
  StackData token;

  while (*p != '\0') {
    if (isspace((unsigned char)*p)) {
      p++;
      continue;
    }

    if (isdigit((unsigned char)*p)) {
      char *endptr;
      token.value = strtoll(p, &endptr, 10);
      if (push(outputStack, token) != OK) {
        return MEMORY_ALLOC_ERROR;
      }
      p = endptr;
      continue;
    }

    if (isupper((unsigned char)*p) && (*p >= 'A' && *p <= 'Z')) {
      token.op = *p;
      if (push(outputStack, token) != OK) {
        return MEMORY_ALLOC_ERROR;
      }
      p++;
      continue;
    }

    if (isOperator(*p)) {
      char op = *p;
      StackData topOpData;

      while (
          !isEmptyStack(operatorStack) &&
          peek(operatorStack, &topOpData) == OK && isOperator(topOpData.op) &&
          (getPrecedence(topOpData.op) > getPrecedence(op) ||
           (getPrecedence(topOpData.op) == getPrecedence(op) && op != '^'))) {

        if (pop(operatorStack, &topOpData) != OK) {
          return UNEXPECTED_TOKEN;
        }

        if (push(outputStack, topOpData) != OK) {
          return MEMORY_ALLOC_ERROR;
        }
      }

      token.op = op;
      if (push(operatorStack, token) != OK) {
        return MEMORY_ALLOC_ERROR;
      }
      p++;
      continue;
    }

    if (*p == '(') {
      token.op = *p;
      if (push(operatorStack, token) != OK) {
        return MEMORY_ALLOC_ERROR;
      }
      p++;
      continue;
    }

    if (*p == ')') {
      StackData topOpData;

      while (!isEmptyStack(operatorStack) &&
             peek(operatorStack, &topOpData) == OK && topOpData.op != '(') {
        if (pop(operatorStack, &topOpData) != OK) {
          return UNEXPECTED_TOKEN;
        }

        if (push(outputStack, topOpData) != OK) {
          return MEMORY_ALLOC_ERROR;
        }
      }

      if (isEmptyStack(operatorStack) || pop(operatorStack, &topOpData) != OK ||
          topOpData.op != '(') {
        return UNEXPECTED_TOKEN;
      }

      p++;
      continue;
    }

    return UNEXPECTED_TOKEN;
  }

  StackData topOpData;

  while (!isEmptyStack(operatorStack)) {
    if (pop(operatorStack, &topOpData) != OK) {
      return UNEXPECTED_TOKEN;
    }

    if (topOpData.op == '(' || topOpData.op == ')') {
      return UNEXPECTED_TOKEN;
    }

    if (push(outputStack, topOpData) != OK) {
      return MEMORY_ALLOC_ERROR;
    }
  }

  return OK;
}

StatusCode evaluateRPN(InterpreterState *state, Stack *rpnStack,
                       long long *result) {
  Stack evalStack;
  initializeStack(&evalStack);
  StatusCode status = OK;

  Stack tempStack;
  initializeStack(&tempStack);
  StackData data;

  while (pop(rpnStack, &data) == OK) {
    if (push(&tempStack, data) != OK) {
      status = MEMORY_ALLOC_ERROR;
      destroyStack(&evalStack);
      destroyStack(&tempStack);
      return status;
    }
  }

  while (pop(&tempStack, &data) == OK) {
    if (isOperator(data.op)) {
      ll operand2, operand1;
      StackData opData1, opData2;

      if (pop(&evalStack, &opData2) != OK) {
        status = UNEXPECTED_TOKEN;
        destroyStack(&evalStack);
        destroyStack(&tempStack);
        return status;
      }

      operand2 = opData2.value;

      if (pop(&evalStack, &opData1) != OK) {
        status = UNEXPECTED_TOKEN;
        destroyStack(&evalStack);
        destroyStack(&tempStack);
        return status;
      }

      operand1 = opData1.value;

      ll res;

      status = evaluateOpertion(operand1, operand2, data.op, &res);

      if (status != OK) {
        destroyStack(&evalStack);
        destroyStack(&tempStack);
        return status;
      }

      data.value = res;

      if (push(&evalStack, data) != OK) {
        status = MEMORY_ALLOC_ERROR;
        destroyStack(&evalStack);
        destroyStack(&tempStack);
        return status;
      }
    } else if (isupper((unsigned char)data.op) &&
               (data.op >= 'A' && data.op <= 'Z')) {
      int varIndex = data.op - 'A';

      if (!state->isInit[varIndex]) {
        status = UNEXPECTED_TOKEN;
        destroyStack(&evalStack);
        destroyStack(&tempStack);
        return status;
      }

      data.value = state->variables[varIndex];

      if (push(&evalStack, data) != OK) {
        status = MEMORY_ALLOC_ERROR;
        destroyStack(&evalStack);
        destroyStack(&tempStack);
        return status;
      }
    } else {
      if (push(&evalStack, data) != OK) {
        status = MEMORY_ALLOC_ERROR;
        destroyStack(&evalStack);
        destroyStack(&tempStack);
        return status;
      }
    }
  }

  if (pop(&evalStack, &data) != OK || !isEmptyStack(&evalStack)) {
    status = UNEXPECTED_TOKEN;
    destroyStack(&evalStack);
    destroyStack(&tempStack);
    return status;
  }

  *result = data.value;

  return OK;
}

StatusCode initializeInterpreter(InterpreterState *state,
                                 const char *logFileName) {
  if (state == NULL || logFileName == NULL) {
    return INVALID_INPUT;
  }

  memset(state->variables, 0, sizeof(state->variables));
  memset(state->isInit, 0, sizeof(state->isInit));
  state->commandCount = 0;

  state->logFile = fopen(logFileName, "w");
  if (state->logFile == NULL) {
    return FILE_OPEN_ERROR;
  }

  return OK;
}

void destroyInterpreter(InterpreterState *state) {
  if (state != NULL && state->logFile != NULL) {
    fclose(state->logFile);
    state->logFile = NULL;
  }
}

const char *skipToExpression(const char *start, char *varName) {
  const char *p = start;

  while (*p != '\0' && isspace((unsigned char)*p)) {
    p++;
  }

  if (strncmp(p, "print", 5) == 0) {
    p += 5;

    while (*p != '\0' && isspace((unsigned char)*p)) {
      p++;
    }

    if (*p != '(') {
      return NULL;
    }
    p++;

    while (*p != '\0' && isspace((unsigned char)*p)) {
      p++;
    }

    if (varName != NULL) {
      if (isupper((unsigned char)*p) && (*p >= 'A' && *p <= 'Z')) {
        *varName = *p;
        p++;
      } else {
        return NULL;
      }
    } else {
      return NULL;
    }

    while (*p != '\0' && isspace((unsigned char)*p)) {
      p++;
    }

    if (*p != ')') {
      return NULL;
    }
    p++;

    while (*p != '\0' && isspace((unsigned char)*p)) {
      p++;
    }

    return *p == '\0' ? p : NULL;
  }

  if (isupper((unsigned char)*p) && (*p >= 'A' && *p <= 'Z')) {
    if (varName != NULL) {
      *varName = *p;
    }

    p++;

    while (*p != '\0' && isspace((unsigned char)*p)) {
      p++;
    }

    return p;
  }

  return NULL;
}

StatusCode processCommand(InterpreterState *state, const char *commandLine) {
  if (state == NULL || commandLine == NULL) {
    return INVALID_INPUT;
  }

  state->commandCount++;
  StatusCode status = OK;
  char targetVar = '\0';
  char trimmedCommand[256];
  strncpy(trimmedCommand, commandLine, 255);
  trimmedCommand[255] = '\0';
  char *end = trimmedCommand + strlen(trimmedCommand) - 1;

  while (end >= trimmedCommand && isspace((unsigned char)*end)) {
    *end = '\0';
    end--;
  }

  const char *exprStart = skipToExpression(trimmedCommand, &targetVar);

  if (exprStart == NULL) {
    char varForPrint = '\0';
    skipToExpression(trimmedCommand, &varForPrint);

    if (varForPrint != '\0' && strncmp(trimmedCommand, "print", 5) == 0) {
      int varIndex = varForPrint - 'A';
      if (!state->isInit[varIndex]) {
        printf("переменная %c не инициализирована\n", varForPrint);
        logState(state, commandLine, "Error: variable not init");
        return UNEXPECTED_TOKEN;
      }

      printf("%lld\n", state->variables[varIndex]);
      logState(state, commandLine, "Print");
      return OK;
    }

    logState(state, commandLine, "Error: Unknown or Invalid command");
    return UNKNOWN_COMMAND;
  }

  if (targetVar != '\0') {
    Stack rpnStack, operatorStack;
    initializeStack(&rpnStack);
    initializeStack(&operatorStack);
    ll result;
    int varIndex = targetVar - 'A';

    if ((status = infixToRPN(exprStart, &rpnStack, &operatorStack)) != OK) {
      destroyStack(&rpnStack);
      destroyStack(&operatorStack);
      logState(state, commandLine, "error: parsing failed");
      return status;
    }

    if ((status = evaluateRPN(state, &rpnStack, &result)) != OK) {
      destroyStack(&rpnStack);
      destroyStack(&operatorStack);
      logState(state, commandLine, "Error: evaluation failed");
      return status;
    }

    state->variables[varIndex] = result;
    state->isInit[varIndex] = true;

    logState(state, commandLine, "Assignment/Arithmetic operation");

    destroyStack(&rpnStack);
    destroyStack(&operatorStack);

    return OK;
  }

  logState(state, commandLine, "Error: unknown or invalid command");

  return UNKNOWN_COMMAND;
}
