#include "linkedList.h"
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void delete_node(Node *node) {
  if (node == NULL) {
    return;
  }
  free(node->data);
  free(node);
}

LIST_TYPE *copy_liver_internal(const LIST_TYPE *src) {
  if (src == NULL) {
    return NULL;
  }
  LIST_TYPE *newLiver = (LIST_TYPE *)malloc(sizeof(LIST_TYPE));
  if (newLiver == NULL) {
    printf("ошибка выделения памяти\n");
    return NULL;
  }
  memcpy(newLiver, src, sizeof(LIST_TYPE));
  return newLiver;
}
