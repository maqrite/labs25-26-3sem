#include "stack.h"
#include "actions.h"
#include <stdlib.h>

node *createNode(char data) {
  node *newNode = (node *)malloc(sizeof(node));

  if (newNode == NULL) {
    return NULL;
  }

  newNode->data = data;
  newNode->next = NULL;

  return newNode;
}

int insertBeforeHead(node **head, char data) {
  node *newNode = createNode(data);

  if (!newNode) {
    return -1;
  }

  if (*head == NULL) {
    *head = newNode;
    return 0;
  }

  newNode->next = *head;
  *head = newNode;

  return 0;
}

int deleteHead(node **head) {
  node *temp = *head;
  *head = (*head)->next;
  free(temp);
  return 0;
}

bool isEmpty(node **stack) { return (*stack == NULL); }

void push(node **stack, char data) {
  if (insertBeforeHead(stack, data) == -1) {
    printErrors(MEMORY_ALLOC_ERROR);
  }
}

int pop(node **stack) {
  if (isEmpty(stack)) {
    printf("стэк пуст\n");
    return -1;
  }

  deleteHead(stack);
  return 0;
}

int peek(node **stack) {
  if (!isEmpty(stack)) {
    return (*stack)->data;
  } else {
    return -1;
  }
}

void printStack(node **stack) {
  node *temp = *stack;

  while (temp != NULL) {
    printf("%c-> ", temp->data);
    temp = temp->next;
  }

  printf("\n");
}
