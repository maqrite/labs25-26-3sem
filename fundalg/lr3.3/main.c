#include "linkedList.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define COMMAND_QUIT 0
#define COMMAND_PRINT 1
#define COMMAND_READ_FILE 2
#define COMMAND_WRITE_FILE 3
#define COMMAND_ADD_LIVER 4
#define COMMAND_DELETE_LIVER 5
#define COMMAND_FIND_LIVER 6
#define COMMAND_MODIFY_LIVER 7
#define COMMAND_UNDO 8

void displayMenu(void);
int getCommand(void);
int getLiverFromUser(LIST_TYPE *liver, int isNew);
int getFilenameFromUser(char *buffer, size_t bufferSize);
void handleAddLiver(LinkedList *list, LinkedList *undoStack);
void handleDeleteLiver(LinkedList *list, LinkedList *undoStack);
void handleFindLiver(LinkedList *list);
void handleModifyLiver(LinkedList *list, LinkedList *undoStack);
int validateDate(int d, int m, int y);
int validateName(const char *str);

void freeModification(Modification *mod);

int main(void) {
  LinkedList mainList = create_list();
  LinkedList undoStack = create_list();
  int command;

  do {
    displayMenu();
    command = getCommand();
    printf("\n");

    switch (command) {
    case COMMAND_QUIT: {
      break;
    }
    case COMMAND_PRINT: {
      print_list(&mainList);
      break;
    }
    case COMMAND_READ_FILE: {
      char filename[MAX_FILE_PATH];
      if (getFilenameFromUser(filename, MAX_FILE_PATH)) {
        delete_list(&mainList);
        if (read_file_to_list(filename, &mainList)) {
          printf("Данные успешно считаны и отсортированы.\n");
          erase_list(&undoStack);
          printf("Стек Undo сброшен.\n");
        } else {
          printf("Ошибка при чтении файла.\n");
        }
      }
      break;
    }
    case COMMAND_WRITE_FILE: {
      char filename[MAX_FILE_PATH];
      if (getFilenameFromUser(filename, MAX_FILE_PATH)) {
        if (write_list_to_file(filename, &mainList)) {
          printf("Данные успешно записаны в файл '%s'.\n", filename);
        } else {
          printf("Ошибка при записи в файл.\n");
        }
      }
      break;
    }
    case COMMAND_ADD_LIVER: {
      handleAddLiver(&mainList, &undoStack);
      break;
    }
    case COMMAND_DELETE_LIVER: {
      handleDeleteLiver(&mainList, &undoStack);
      break;
    }
    case COMMAND_FIND_LIVER: {
      handleFindLiver(&mainList);
      break;
    }
    case COMMAND_MODIFY_LIVER: {
      handleModifyLiver(&mainList, &undoStack);
      break;
    }
    case COMMAND_UNDO: {
      undo_modifications(&mainList, &undoStack);
      break;
    }
    default: {
      printf("Неизвестная команда. Пожалуйста, выберите номер из меню.\n");
      break;
    }
    }
  } while (command != COMMAND_QUIT);

  delete_list(&mainList);

  LIST_TYPE *modData;
  while ((modData = pop_stack(&undoStack)) != NULL) {
    Modification *mod = (Modification *)modData;
    freeModification(mod);
    free(mod);
  }
  delete_list(&undoStack);

  return 0;
}

void freeModification(Modification *mod) {
  if (mod == NULL)
    return;
  free(mod->old_data);
  free(mod->new_data);
}

void displayMenu(void) {
  printf("\n--- МЕНЮ ---\n");
  printf("%d. Выход\n", COMMAND_QUIT);
  printf("%d. Вывести список\n", COMMAND_PRINT);
  printf("%d. Считать данные из файла\n", COMMAND_READ_FILE);
  printf("%d. Выгрузить данные в файл\n", COMMAND_WRITE_FILE);
  printf("%d. Добавить жителя\n", COMMAND_ADD_LIVER);
  printf("%d. Удалить жителя по ID\n", COMMAND_DELETE_LIVER);
  printf("%d. Найти жителя по ID\n", COMMAND_FIND_LIVER);
  printf("%d. Изменить жителя по ID\n", COMMAND_MODIFY_LIVER);
  printf("%d. Отменить последние N/2 модификаций (Undo)\n", COMMAND_UNDO);
  printf("Введите номер команды: ");
}

int getCommand(void) {
  int command;
  if (scanf("%d", &command) != 1) {
    while (getchar() != '\n')
      ;
    return -1;
  }
  while (getchar() != '\n')
    ;
  return command;
}

int getFilenameFromUser(char *buffer, size_t bufferSize) {
  printf("Введите путь к файлу: ");
  if (fgets(buffer, bufferSize, stdin) == NULL) {
    return 0;
  }
  size_t len = strlen(buffer);
  if (len > 0 && buffer[len - 1] == '\n') {
    buffer[len - 1] = '\0';
  } else if (len == bufferSize - 1) {
    while (getchar() != '\n')
      ;
  }
  if (strlen(buffer) == 0) {
    return 0;
  }
  return 1;
}

int validateDate(int d, int m, int y) {
  if (y < 1900 || y > 2025)
    return 0;
  if (m < 1 || m > 12)
    return 0;
  if (d < 1 || d > 31)
    return 0;

  if (m == 2) {
    int isLeap = (y % 4 == 0 && (y % 100 != 0 || y % 400 == 0));
    if (d > (28 + isLeap))
      return 0;
  } else if (m == 4 || m == 6 || m == 9 || m == 11) {
    if (d > 30)
      return 0;
  }
  return 1;
}

int validateName(const char *str) {
  if (str == NULL || *str == '\0')
    return 0;
  for (size_t i = 0; str[i] != '\0'; i++) {
    if (!isalpha(str[i])) {
      return 0;
    }
  }
  return 1;
}

int getLiverFromUser(LIST_TYPE *liver, int isNew) {
  int day, month, year;
  char genderChar;
  double income;
  unsigned int id = 0;

  if (isNew) {
    printf("Введите ID жителя (неотрицательное): ");
    if (scanf("%u", &id) != 1) {
      while (getchar() != '\n')
        ;
      return 0;
    }
  }
  liver->id = id;

  while (getchar() != '\n')
    ;
  char tempSurname[MAX_NAME_LEN];
  printf("Введите фамилию (латиница, непустая): ");
  if (fgets(tempSurname, MAX_NAME_LEN, stdin) == NULL ||
      !validateName(strtok(tempSurname, "\n")))
    return 0;
  strncpy(liver->surname, tempSurname, MAX_NAME_LEN);

  char tempName[MAX_NAME_LEN];
  printf("Введите имя (латиница, непустая): ");
  if (fgets(tempName, MAX_NAME_LEN, stdin) == NULL ||
      !validateName(strtok(tempName, "\n")))
    return 0;
  strncpy(liver->name, tempName, MAX_NAME_LEN);

  char tempPatronymic[MAX_PATRONYMIC_LEN];
  printf("Введите отчество (латиница, можно пропустить): ");
  if (fgets(tempPatronymic, MAX_PATRONYMIC_LEN, stdin) == NULL)
    return 0;
  strtok(tempPatronymic, "\n");
  if (*tempPatronymic != '\0' && !validateName(tempPatronymic))
    return 0;
  strncpy(liver->patronymic, tempPatronymic, MAX_PATRONYMIC_LEN);

  printf("Введите дату рождения (день месяц год, например 01 01 2000): ");
  if (scanf("%d %d %d", &day, &month, &year) != 3 ||
      !validateDate(day, month, year)) {
    while (getchar() != '\n')
      ;
    return 0;
  }
  liver->dob.day = day;
  liver->dob.month = month;
  liver->dob.year = year;

  printf("Введите пол ('M' или 'W'): ");
  if (scanf(" %c", &genderChar) != 1 ||
      (genderChar != 'M' && genderChar != 'W')) {
    while (getchar() != '\n')
      ;
    return 0;
  }
  liver->gender = genderChar;

  printf("Введите средний доход за месяц (неотрицательное вещественное): ");
  if (scanf("%lf", &income) != 1 || income < 0.0) {
    while (getchar() != '\n')
      ;
    return 0;
  }
  liver->avgIncome = income;

  while (getchar() != '\n')
    ;
  return 1;
}

void handleAddLiver(LinkedList *list, LinkedList *undoStack) {
  LIST_TYPE tempLiver;
  printf("Добавление жителя\n");
  if (!getLiverFromUser(&tempLiver, 1)) {
    printf("Ошибка ввода данных жителя.\n");
    return;
  }

  if (find_liver(list, tempLiver.id) != NULL) {
    printf("Ошибка: Житель с ID %u уже существует.\n", tempLiver.id);
    return;
  }

  LIST_TYPE *newLiverToInsert = copy_liver_internal(&tempLiver);
  if (newLiverToInsert == NULL) {
    return;
  }

  if (!insert_sorted(list, newLiverToInsert)) {
    printf("Ошибка при добавлении жителя\n");
    return;
  }

  size_t index = 0;
  Node *current = list->head;
  while (current != NULL && current->data != newLiverToInsert) {
    current = current->next;
    index++;
  }

  Modification mod = {
      .type = MOD_ADD, .index = index, .old_data = NULL, .new_data = NULL};
  push_modification(undoStack, mod);
  printf("Житель успешно добавлен (индекс: %zu).\n", index);
}

void handleDeleteLiver(LinkedList *list, LinkedList *undoStack) {
  unsigned int id;
  printf("Введите ID жителя для удаления: ");
  if (scanf("%u", &id) != 1) {
    while (getchar() != '\n')
      ;
    printf("Ошибка ввода ID.\n");
    return;
  }
  while (getchar() != '\n')
    ;

  Node *nodeToRemove = find_liver(list, id);
  if (nodeToRemove == NULL) {
    printf("Житель с ID %u не найден.\n", id);
    return;
  }

  size_t index = 0;
  Node *current = list->head;
  while (current != NULL && current != nodeToRemove) {
    current = current->next;
    index++;
  }

  LIST_TYPE *oldDataCopy = copy_liver_internal(nodeToRemove->data);
  if (oldDataCopy == NULL) {
    printf("Ошибка выделения памяти для Undo.\n");
    return;
  }

  LIST_TYPE *removedData = delete_at_list(list, index);
  if (removedData == NULL) {
    free(oldDataCopy);
    return;
  }
  free(removedData);

  Modification mod = {.type = MOD_DELETE,
                      .index = index,
                      .old_data = oldDataCopy,
                      .new_data = NULL};
  push_modification(undoStack, mod);
  printf("Житель с ID %u успешно удален.\n", id);
}

void handleFindLiver(LinkedList *list) {
  unsigned int id;
  printf("Введите ID жителя для поиска: ");
  if (scanf("%u", &id) != 1) {
    while (getchar() != '\n')
      ;
    printf("Ошибка ввода ID.\n");
    return;
  }
  while (getchar() != '\n')
    ;

  Node *foundNode = find_liver(list, id);
  if (foundNode != NULL) {
    printf("Житель найден:\n");
    print_liver(foundNode->data);
  } else {
    printf("Житель с ID %u не найден.\n", id);
  }
}

void handleModifyLiver(LinkedList *list, LinkedList *undoStack) {
  unsigned int id;
  printf("Введите ID жителя для изменения: ");
  if (scanf("%u", &id) != 1) {
    while (getchar() != '\n')
      ;
    printf("Ошибка ввода ID.\n");
    return;
  }
  while (getchar() != '\n')
    ;

  Node *nodeToModify = find_liver(list, id);
  if (nodeToModify == NULL) {
    printf("Житель с ID %u не найден.\n", id);
    return;
  }

  printf("Найденный житель:\n");
  print_liver(nodeToModify->data);

  LIST_TYPE *oldDataCopy = copy_liver_internal(nodeToModify->data);
  if (oldDataCopy == NULL) {
    printf("Ошибка выделения памяти для Undo.\n");
    return;
  }

  LIST_TYPE newData;
  newData.id = id;
  printf("\nВведите НОВЫЕ данные жителя:\n");
  if (!getLiverFromUser(&newData, 0)) {
    printf("Ошибка ввода новых данных.\n");
    free(oldDataCopy);
    return;
  }
  newData.id = id;

  modify_liver(nodeToModify, &newData);

  size_t index = 0;
  Node *current = list->head;
  while (current != NULL && current != nodeToModify) {
    current = current->next;
    index++;
  }

  LIST_TYPE *newDataCopy = copy_liver_internal(&newData);
  if (newDataCopy == NULL) {
    printf("Ошибка выделения памяти для Undo (копия новых данных).\n");
    free(oldDataCopy);
    return;
  }

  Modification mod = {.type = MOD_EDIT,
                      .index = index,
                      .old_data = oldDataCopy,
                      .new_data = newDataCopy};
  push_modification(undoStack, mod);
  printf("Житель с ID %u успешно изменен.\n", id);
}
