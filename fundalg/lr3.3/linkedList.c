#include "linkedList.h"
#include <ctype.h>
#include <iso646.h>
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

LIST_TYPE *delete_at_list(LinkedList *list, size_t index) {
  if (list == NULL || list->size == 0) {
    return NULL;
  }

  if (index >= list->size) {
    printf("выход за границы\n");
    return NULL;
  }

  if (index == 0) {
    return pop_front_list(list);
  }

  if (index == list->size - 1) {
    return pop_back_list(list);
  }

  Node *toRemove = get_node_at_list(list, index);
  if (toRemove == NULL) {
    return NULL;
  }

  toRemove->prev->next = toRemove->next;
  toRemove->next->prev = toRemove->prev;

  LIST_TYPE *removedData = toRemove->data;
  free(toRemove);
  list->size--;
  return removedData;
}

LIST_TYPE *get_at_list(const LinkedList *list, size_t index) {
  if (list == NULL || index >= list->size) {
    printf("выход за границы\n");
    return NULL;
  }

  Node *found = get_node_at_list(list, index);
  if (found == NULL) {
    return NULL;
  }

  return copy_liver_internal(found->data);
}

int is_equal_liver(const LIST_TYPE *l1, const LIST_TYPE *l2) {
  if (l1 == NULL || l2 == NULL) {
    return 0;
  }

  if (l1->id != l2->id) {
    return 0;
  }

  if (strcmp(l1->surname, l2->surname) != 0) {
    return 0;
  }

  if (strcmp(l1->name, l2->name) != 0) {
    return 0;
  }

  if (strcmp(l1->patronymic, l2->patronymic) != 0) {
    return 0;
  }

  if (l1->dob.day != l2->dob.day || l1->dob.month != l2->dob.month ||
      l1->dob.year != l2->dob.year) {
    return 0;
  }

  if (l1->gender != l2->gender) {
    return 0;
  }

  if (fabs(l1->avgIncome - l2->avgIncome) > 1e-9) {
    return 0;
  }

  return 1;
}

int is_equal_list(const LinkedList *l1, const LinkedList *l2) {
  if (l1 == NULL || l2 == NULL) {
    return 0;
  }

  if (l1->size != l2->size) {
    return 0;
  }

  Node *current1 = l1->head;
  Node *current2 = l2->head;

  while (current1 != NULL) {
    if (!is_equal_liver(current1->data, current2->data)) {
      return 0;
    }

    current1 = current1->next;
    current2 = current2->next;
  }

  return 1;
}

void push_stack(LinkedList *stack, const LIST_TYPE *value) {
  push_back_list(stack, value);
}

LIST_TYPE *pop_stack(LinkedList *stack) { return pop_back_list(stack); }

LIST_TYPE *peek_stack(const LinkedList *stack) {
  if (stack == NULL || stack->size == 0) {
    return NULL;
  }

  return copy_liver_internal(stack->tail->data);
}

void enqueue(LinkedList *queue, const LIST_TYPE *value) {
  push_back_list(queue, value);
}

LIST_TYPE *dequeue(LinkedList *queue) { return pop_front_list(queue); }

LIST_TYPE *peek_queue(const LinkedList *queue) {
  if (queue == NULL || queue->size == 0) {
    return 0;
  }

  return copy_liver_internal(queue->head->data);
}

int calculate_age(Date dob) {
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);

  int currentYear = tm.tm_year + 1900;
  int currentMonth = tm.tm_mon + 1;
  int currentDay = tm.tm_mday;

  int age = currentYear - dob.year;

  if (dob.month > currentMonth ||
      (dob.month == currentMonth && dob.day > currentDay)) {
    age--;
  }

  return age;
}

int compare_liver_by_age(const LIST_TYPE *l1, const LIST_TYPE *l2) {
  return calculate_age(l1->dob) - calculate_age(l2->dob);
}

int insert_sorted(LinkedList *list, LIST_TYPE *newLiver) {
  if (list == NULL || newLiver == NULL) {
    free(newLiver);
    return 0;
  }

  Node *newNode = (Node *)malloc(sizeof(Node));
  if (newNode == NULL) {
    printf("ошибка выделения памяти\n");
    free(newLiver);
    return 0;
  }

  newNode->data = newLiver;
  newNode->prev = NULL;
  newNode->next = NULL;

  if (list->size == 0) {
    list->head = newNode;
    list->tail = newNode;
  } else {
    Node *current = list->head;
    while (current != NULL &&
           compare_liver_by_age(newLiver, current->data) > 0) {
      current = current->next;
    }

    if (current == NULL) {
      newNode->prev = list->tail;
      list->tail->next = newNode;
      list->tail = newNode;
    } else if (current == list->head) {
      newNode->next = list->head;
      list->head->prev = newNode;
      list->head = newNode;
    } else {
      newNode->next = current;
      newNode->prev = current->prev;
      current->prev->next = newNode;
      current->prev = newNode;
    }
  }

  list->size++;

  return 1;
}

int read_file_to_list(const char *filename, LinkedList *list) {
  if (filename == NULL || list == NULL) {
    return 0;
  }

  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    printf("ошибка открытия файла %s \n", filename);
    return 0;
  }

  erase_list(list);

  LIST_TYPE tempLiver;
  int day, month, year;
  char patronymicBuf[MAX_PATRONYMIC_LEN];
  int readCount;

  while ((readCount = fscanf(file, "%u %s %s %s %d %d %d %c %lf", &tempLiver.id,
                             tempLiver.surname, tempLiver.name, patronymicBuf,
                             &day, &month, &year, &tempLiver.gender,
                             &tempLiver.avgIncome)) == 9) {

    if (tempLiver.avgIncome < 0.0 ||
        (tempLiver.gender != 'M' && tempLiver.gender != 'W')) {
      printf("Ошибка валидации данных в файле, пропускаем запись (ID: %u)\n",
             tempLiver.id);
      continue;
    }

    strncpy(tempLiver.patronymic, patronymicBuf, MAX_PATRONYMIC_LEN - 1);
    tempLiver.patronymic[MAX_PATRONYMIC_LEN - 1] = '\0';
    tempLiver.dob.day = day;
    tempLiver.dob.month = month;
    tempLiver.dob.year = year;

    LIST_TYPE *newLiver = copy_liver_internal(&tempLiver);
    if (newLiver == NULL) {
      fclose(file);
      erase_list(list);
      return 0;
    }
  }

  if (!feof(file)) {
    printf("ошибка чтения файла\n");
    fclose(file);
    erase_list(list);
    return 0;
  }

  fclose(file);
  return 1;
}

Node *find_liver(const LinkedList *list, unsigned int id) {
  if (list == NULL || list->size == 0) {
    return NULL;
  }

  Node *current = list->head;
  while (current != NULL) {
    if (current->data->id == id) {
      return current;
    }

    current = current->next;
  }

  return NULL;
}

void modify_liver(Node *node, const LIST_TYPE *newData) {
  if (node == NULL || newData == NULL) {
    return;
  }

  unsigned int originalId = node->data->id;
  memcpy(node->data, newData, sizeof(LIST_TYPE));
  node->data->id = originalId;
}

int write_list_to_file(const char *filename, const LinkedList *list) {
  if (filename == NULL || list == NULL) {
    return 0;
  }

  FILE *file = fopen(filename, "w");
  if (file == NULL) {
    printf("ошибка открытия файла %s \n", filename);
    return 0;
  }

  Node *current = list->head;
  while (current != NULL) {
    LIST_TYPE *l = current->data;
    fprintf(file, "%u %s %s %s %d %d %d %c %.2lf\n", l->id, l->surname, l->name,
            l->patronymic, l->dob.day, l->dob.month, l->dob.year, l->gender,
            l->avgIncome);
    current = current->next;
  }

  fclose(file);

  return 1;
}

void print_liver(const LIST_TYPE *liver) {
  if (liver == NULL) {
    return;
  }

  printf(" ID: %u\n", liver->id);
  printf(" ФИО: %s %s %s\n", liver->surname, liver->name, liver->patronymic);
  printf(" Дата рождения: %02d.%02d.%d (возраст: %d)\n", liver->dob.day,
         liver->dob.month, liver->dob.year, calculate_age(liver->dob));
  printf(" Пол: %c\n", liver->gender);
  printf(" Средний доход: %.2lf\n", liver->avgIncome);
}

void print_list(const LinkedList *list) {
  if (list == NULL || list->size == 0) {
    printf("список пуст\n");
    return;
  }

  printf("---\n");

  Node *current = list->head;
  size_t index = 0;

  while (current != NULL) {
    printf("[%zu].\n", index);
    print_liver(current->data);
    current = current->next;
    index++;
  }

  printf("---\n");
}

void free_modification(Modification *mod) {
  if (mod == NULL) {
    return;
  }

  free(mod->old_data);
  free(mod->new_data);
}

void push_modification(LinkedList *undoStack, Modification mod) {
  Modification *modPtr = (Modification *)malloc(sizeof(Modification));
  if (modPtr == NULL) {
    printf("ошибка выделения памяти\n");
    free_modification(&mod);
    return;
  }

  memcpy(modPtr, &mod, sizeof(Modification));

  Node *newNode = (Node *)malloc(sizeof(Node));
  if (newNode == NULL) {
    printf("ошибка выделения памяти\n");
    free(modPtr);
    free_modification(&mod);
    return;
  }

  newNode->data = (LIST_TYPE *)modPtr;
  newNode->prev = NULL;
  newNode->next = NULL;

  if (undoStack->size == 0) {
    undoStack->head = newNode;
    undoStack->tail = newNode;
  } else {
    newNode->prev = undoStack->tail;
    undoStack->tail->next = newNode;
    undoStack->tail = newNode;
  }

  undoStack->size++;
}

void undo_modifications(LinkedList *list, LinkedList *undoStack) {
  if (list == NULL || undoStack == NULL) {
    return;
  }

  if (undoStack->size = 0) {
    printf("нет изменений для отмены\n");
    return;
  }

  size_t numUndo = undoStack->size / 2;
  printf("Отмена последних %zu изменений", numUndo);

  for (size_t i = 0; i < numUndo; i++) {
    LIST_TYPE *modDataPtr = pop_list_internal(undoStack, 0);
    if (modDataPtr == NULL) {
      break;
    }

    Modification *mod = (Modification *)modDataPtr;

    switch (mod->type) {
    case MOD_ADD: {
      LIST_TYPE *removedLiver = delete_at_list(list, mod->index);
      if (removedLiver == NULL) {
        printf("не удалось удалить добавленный элемент по индексу %zu\n",
               mod->index);
      } else {
        free(removedLiver);
      }
      break;
    }

    case MOD_DELETE: {
      insert_at_list(list, mod->index, mod->old_data);
      break;
    }

    case MOD_EDIT: {
      Node *nodeToEdit = get_node_at_list(list, mod->index);
      if (nodeToEdit != NULL) {
        memcpy(nodeToEdit->data, mod->old_data, sizeof(LIST_TYPE));
      } else {
        printf("не найден элемент для edit по индексу %zu.\n", mod->index);
      }
      break;
    }
    }

    free_modification(mod);
    free(mod);
  }

  printf("отмена завершена\n");
}
