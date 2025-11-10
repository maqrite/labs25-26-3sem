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
