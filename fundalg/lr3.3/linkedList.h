#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "actions.h"
#include <cstddef>
#include <stddef.h>
#include <time.h>

#define MAX_NAME_LEN 50
#define MAX_PATRONYMIC_LEN 50
#define MAX_FILE_PATH 256

typedef struct {
  int day;
  int month;
  int year;
} Date;

typedef struct {
  unsigned int id;
  char surname[MAX_NAME_LEN];
  char name[MAX_NAME_LEN];
  char patronymic[MAX_PATRONYMIC_LEN];
  Date dob;
  char gender;
  double avgIncome;
} Liver;

typedef Liver LIST_TYPE;

typedef struct Node {
  LIST_TYPE *data;
  struct Node *prev;
  struct Node *next;
} Node;

typedef struct {
  Node *head;
  Node *tail;
  size_t size;
} LinkedList;

#endif
