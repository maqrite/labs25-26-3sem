#include "actions.h"
#include "stack.h"

#include <string.h>

void printErrors(StatusCode status) {
  switch (status) {

  case INVALID_INPUT:
    printf("неверный ввод\n");
    break;

  case MEMORY_ALLOC_ERROR:
    printf("ошибка выделения памяти\n");
    break;

  default:
    break;
  }
}

bool areBracketsPaired(char open, char close) {
  if (open == '(' && close == ')') {
    return true;
  }
  if (open == '[' && close == ']') {
    return true;
  }
  if (open == '{' && close == '}') {
    return true;
  }
  if (open == '<' && close == '>') {
    return true;
  }

  return false;
}

int check_brackets(const char *str) {
  node *stack = NULL;
  int len = strlen(str);
  StatusCode status = OK;

  for (int i = 0; i < len; i++) {
    char c = str[i];

    if (c == '(' || c == '{' || c == '[' || c == '<') {
      push(&stack, c);
    } else if (c == ')' || c == '}' || c == ']' || c == '>') {
      if (isEmpty(&stack)) {
        status = INVALID_INPUT;
        break;
      }

      char top = (char)peek(&stack);

      if (areBracketsPaired(top, c)) {
        pop(&stack);
      } else {
        status = INVALID_INPUT;
        break;
      }
    }
  }

  if (status == OK && !isEmpty(&stack)) {
    status = INVALID_INPUT;
  }

  while (!isEmpty(&stack)) {
    pop(&stack);
  }

  return status;
}
