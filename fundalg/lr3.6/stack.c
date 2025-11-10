#include "stack.h"
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
  if (insertBeforeHead(stack, data)) {
    printf("стэк переполнен\n");
  }
}
