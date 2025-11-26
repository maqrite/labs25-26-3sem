#ifndef STACK_H
#define STACK_H

#include "actions.h"
#include <stdbool.h>

#define ll long long

typedef union {
  ll value;
  char op;
} StackData;

typedef struct StackNode {
  StackData data;
  struct StackNode *next;
} StackNode;

typedef struct {
  StackNode *top;
} Stack;

void initializeStack(Stack *s);
bool isEmptyStack(const Stack *s);
StatusCode push(Stack *s, StackData data);
StatusCode pop(Stack *s, StackData *data);
StatusCode peek(const Stack *s, StackData *data);
void destroyStack(Stack *s);

#endif
