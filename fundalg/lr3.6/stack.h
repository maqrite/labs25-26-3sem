#ifndef STACK_H
#define STACK_H

#include "actions.h"
#include <stdbool.h>
#include <stdio.h>

typedef struct Node {
  int data;
  struct Node *next;
} node;

node *createNode(char data);
int insertBeforeHead(node **head, char data);
int deleteHead(node **head);
bool isEmpty(node **stack);

void push(node **stack, char data);
int pop(node **stack);
int peek(node **stack);
void printStack(node **stack);

#endif
