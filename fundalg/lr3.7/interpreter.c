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
