#include "stack.h"
#include "actions.h"
#include <stdlib.h>

void initializeStack(Stack *s) {
  if (s != NULL) {
    s->top = NULL;
  }
}

bool isEmptyStack(const Stack *s) { return s == NULL || s->top == NULL; }

StatusCode push(Stack *s, StackData data) {
  if (s == NULL) {
    return INVALID_INPUT;
  }

  StackNode *newNode = (StackNode *)malloc(sizeof(StackNode));
  if (newNode == NULL) {
    return MEMORY_ALLOC_ERROR;
  }

  newNode->data = data;
  newNode->next = s->top;
  s->top = newNode;

  return OK;
}

StatusCode pop(Stack *s, StackData *data) {
  if (isEmptyStack(s)) {
    return INVALID_INPUT;
  }

  StackNode *temp = s->top;
  if (data != NULL) {
    *data = temp->data;
  }

  s->top = s->top->next;
  free(temp);

  return OK;
}

StatusCode peek(const Stack *s, StackData *data) {
  if (isEmptyStack(s)) {
    return INVALID_INPUT;
  }

  if (data != NULL) {
    *data = s->top->data;
  }

  return OK;
}

void destroyStack(Stack *s) {
  StackData _;
  while (!isEmptyStack(s)) {
    pop(s, &_);
  }
}
