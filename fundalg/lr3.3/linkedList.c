#include "linkedList.h"
#include <cstddef>
#include <ctype.h>
#include <math.h>
#include <stddef.h>
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

LinkedList create_list(void) {
  LinkedList list = {.head = NULL, .tail = NULL, .size = 0};
  return list;
}

void erase_list(LinkedList *list) {
  if (list == NULL) {
    return;
  }
  Node *current = list->head;
  Node *next;

  while (current != NULL) {
    next = current->next;
    delete_node(current);
    current = next;
  }
  list->head = NULL;
  list->tail = NULL;
  list->size = 0;
}

void delete_list(LinkedList *list) {
  if (list == NULL) {
    return;
  }
  erase_list(list);
}

void push_list_internal(LinkedList *list, const LIST_TYPE *value, int isFront) {
  if (list == NULL || value == NULL) {
    return;
  }

  LIST_TYPE *dataCopy = copy_liver_internal(value);
  if (dataCopy == NULL) {
    return;
  }

  Node *newNode = (Node *)malloc(sizeof(Node));
  if (newNode == NULL) {
    printf("ошибка выделения памяти\n");
    free(dataCopy);
    return;
  }

  newNode->data = dataCopy;
  newNode->prev = NULL;
  newNode->next = NULL;

  if (list->size == 0) {
    list->head = newNode;
    list->tail = newNode;
  } else if (isFront) {
    newNode->next = list->head;
    list->head->prev = newNode;
    list->head = newNode;
  } else {
    newNode->prev = list->tail;
    list->tail->next = newNode;
    list->tail = newNode;
  }

  list->size++;
}

void push_back_list(LinkedList *list, const LIST_TYPE *value) {
  push_list_internal(list, value, 0);
}

void push_front_list(LinkedList *list, const LIST_TYPE *value) {
  push_list_internal(list, value, 1);
}

LIST_TYPE *pop_list_internal(LinkedList *list, int isFront) {
  if (list == NULL || list->size == 0) {
    return NULL;
  }

  Node *toRemove = isFront ? list->head : list->tail;
  LIST_TYPE *valueOut = toRemove->data;

  if (list->size == 1) {
    list->head = NULL;
    list->tail = NULL;
  } else if (isFront) {
    list->head = toRemove->next;
    if (list->head != NULL) {
      list->head->prev = NULL;
    }
  } else {
    list->tail = toRemove->prev;
    if (list->tail != NULL) {
      list->tail->next = NULL;
    }
  }

  free(toRemove);
  list->size--;

  return valueOut;
}

LIST_TYPE *pop_back_list(LinkedList *list) {
  return pop_list_internal(list, 0);
}

LIST_TYPE *pop_front_list(LinkedList *list) {
  return pop_list_internal(list, 1);
}

Node *get_node_at_list(const LinkedList *list, size_t index) {
  if (list == NULL || index >= list->size) {
    return NULL;
  }

  Node *current;
  if (index < list->size / 2) {
    current = list->head;
    for (size_t i = 0; i < index; i++) {
      current = current->next;
    }
  } else {
    current = list->tail;
    for (size_t i = list->size - 1; i > index; i--) {
      current = current->prev;
    }
  }

  return current;
}

void insert_at_list(LinkedList *list, size_t index, const LIST_TYPE *value) {
  if (list == NULL || value == NULL) {
    return;
  }

  if (index > list->size) {
    printf("выход за границы\n");
    return;
  }

  if (index == 0) {
    push_front_list(list, value);
    return;
  }

  if (index == list->size) {
    push_back_list(list, value);
  }

  Node *current = get_node_at_list(list, index);
  if (current == NULL) {
    return;
  }

  LIST_TYPE *dataCopy = copy_liver_internal(value);
  if (dataCopy == NULL) {
    return;
  }

  Node *newNode = (Node *)malloc(sizeof(Node));
  if (newNode == NULL) {
    printf("ошибка выделения памяти\n");
    free(dataCopy);
    return;
  }

  newNode->data = dataCopy;
  newNode->next = current;
  newNode->prev = current->prev;
  current->prev->next = newNode;
  current->prev = newNode;

  list->size++;
}
