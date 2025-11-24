#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "actions.h"
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

LinkedList create_list(void);
void erase_list(LinkedList *list);
void delete_list(LinkedList *list);
void push_back_list(LinkedList *list, const LIST_TYPE *value);
void push_front_list(LinkedList *list, const LIST_TYPE *value);
LIST_TYPE *pop_back_list(LinkedList *list);
LIST_TYPE *pop_front_list(LinkedList *list);
void insert_at_list(LinkedList *list, size_t index, const LIST_TYPE *value);
LIST_TYPE *delete_at_list(LinkedList *list, size_t index);
LIST_TYPE *get_at_list(const LinkedList *list, size_t index);
int is_equal_list(const LinkedList *l1, const LinkedList *l2);

// stack
void push_stack(LinkedList *stack, const LIST_TYPE *value);
LIST_TYPE *pop_stack(LinkedList *stack);
LIST_TYPE *peek_stack(const LinkedList *stack);

// queue
void enqueue(LinkedList *queue, const LIST_TYPE *value);
LIST_TYPE *dequeue(LinkedList *queue);
LIST_TYPE *peek_queue(const LinkedList *queue);

// functions
int read_file_to_list(const char *filename, LinkedList *list);
int insert_sorted(LinkedList *list, LIST_TYPE *newLiver);
Node *find_liver(const LinkedList *list, unsigned int id);
void modify_liver(Node *node, const LIST_TYPE *newData);
int write_list_to_file(const char *filename, const LinkedList *list);
void print_liver(const LIST_TYPE *liver);
void print_list(const LinkedList *list);

// undo mod

typedef struct {
  enum { MOD_ADD, MOD_DELETE, MOD_EDIT } type;
  size_t index;
  LIST_TYPE *old_data;
  LIST_TYPE *new_data;
} Modification;

void undo_modifications(LinkedList *list, LinkedList *undoStack);
void push_modification(LinkedList *undoStack, Modification mod);

// my help func
void delete_node(Node *node);
LIST_TYPE *copy_liver_internal(const LIST_TYPE *src);
void push_list_internal(LinkedList *list, const LIST_TYPE *value, int isFront);

#endif
