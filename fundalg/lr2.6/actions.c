#include "actions.h"
#include "fileIo.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printErrors(StatusCode status) {
  switch (status) {

  case INVALID_INPUT:
    printf("ошибка, неверный ввод\n");
    break;

  case INVALID_ARGC:
    printf("Неверное количество аргументов командной строки\n");
    break;

  case FILE_OPEN_ERROR:
    printf("Ошибка открытия файла\n");
    break;

  case MEMORY_ALLOC_ERROR:
    printf("Ошибка выделения памяти\n");
    break;

  case BAD_FILE_FORMAT:
    printf("Неверный формат строки\n");
    break;

  case INVALID_STUDENT_DATA:
    printf("Невалидные данные студента\n");
    break;

  case STUDENT_NOT_FOUND:
    printf("Студент с таким ID не найден\n");
    break;

  default:
    break;
  }
}

int compareById(const void *a, const void *b) {
  const Student *studentA = *(const Student **)a;
  const Student *studentB = *(const Student **)b;
  if (studentA->id < studentB->id) {
    return -1;
  }

  if (studentA->id > studentB->id) {
    return 1;
  }

  return 0;
}

int compareBySurname(const void *a, const void *b) {
  const Student *studentA = *(const Student **)a;
  const Student *studentB = *(const Student **)b;

  return strcmp(studentA->surname, studentB->surname);
}

int compareByName(const void *a, const void *b) {
  const Student *studentA = *(const Student **)a;
  const Student *studentB = *(const Student **)b;

  return strcmp(studentA->name, studentB->name);
}

int compareByGroup(const void *a, const void *b) {
  const Student *studentA = *(const Student **)a;
  const Student *studentB = *(const Student **)b;

  return strcmp(studentA->group, studentB->group);
}

StatusCode readUnsignedInt(unsigned int *value) {
  char buffer[32];
  if (!fgets(buffer, sizeof(buffer), stdin)) {
    return INVALID_INPUT;
  }

  buffer[strcspn(buffer, "\n")] = 0;

  char *pEnd;
  long val = strtol(buffer, &pEnd, 10);

  if (pEnd == buffer || *pEnd != '\0' || val < 0 || val > UINT_MAX) {
    return INVALID_INPUT;
  }

  *value = (unsigned int)val;

  return OK;
}

StatusCode readNonEmptyString(char *buffer, size_t size) {
  if (!fgets(buffer, size, stdin)) {
    return INVALID_INPUT;
  }

  buffer[strcspn(buffer, "\n")] = 0;

  if (buffer[0] == '\0') {
    return INVALID_INPUT;
  }

  return OK;
}

void printMenu() {
  printf("1. Найти студента по id\n");
  printf("2. Найти студентов по фамилии\n");
  printf("3. Найти студентов по имени\n");
  printf("4. Найти студентов по группе\n");
  printf("5. Сортировать по id\n");
  printf("6. Сортировать по фамилии\n");
  printf("7. Сортировать по имени\n");
  printf("8. Сортировать по группе\n");
  printf("9. записать в лог по id\n");
  printf("10. записать в лог студентов с баллом > среднего\n");
  printf("11. показать всех студентов\n");
  printf("0. Выход\n");
  printf("\n");
}

void findBiId(const StudentVector *vec, unsigned int id) {
  int found = 0;
  for (size_t i = 0; i < vec->count; ++i) {
    if (vec->students[i]->id == id) {
      printStudent(vec->students[i]);
      found = 1;
    }
  }

  if (!found) {
    printf("Студенты с id %u не найдены\n", id);
  }
}

void findByString(const StudentVector *vec, const char *searchTerm,
                  const char *field) {
  int found = 0;

  for (size_t i = 0; i < vec->count; ++i) {
    const char *value = NULL;

    if (strcmp(field, "surname") == 0) {
      value = vec->students[i]->surname;
    } else if (strcmp(field, "name") == 0) {
      value = vec->students[i]->name;
    } else if (strcmp(field, "group") == 0) {
      value = vec->students[i]->group;
    }

    if (value && strcmp(value, searchTerm) == 0) {
      printStudent(vec->students[i]);
      found = 1;
    }
  }

  if (!found) {
    printf("Студенты не найдены\n");
  }
}

StatusCode runIntDialog(StudentVector *vec, FILE *traceFile) {
  StatusCode status = OK;
  int choice = -1;
  char buffer[256];
  unsigned int id;

  while (choice != 0) {
    printMenu();
    unsigned int tempChoice;

    if (readUnsignedInt(&tempChoice) != OK) {
      printf("Неверный выбор\n");
      choice = -1;
      continue;
    }

    choice = (int)tempChoice;

    switch (choice) {
    case 1:
      printf("Введите id: ");
      if (readUnsignedInt(&id) == OK) {
        findBiId(vec, id);
      } else {
        printErrors(INVALID_INPUT);
      }
      break;

    case 2:
      printf("Введите фамилию: ");
      if (readNonEmptyString(buffer, sizeof(buffer)) == OK) {
        findByString(vec, buffer, "surname");
      } else {
        printErrors(INVALID_INPUT);
      }
      break;

    case 3:
      printf("Введите имя: ");
      if (readNonEmptyString(buffer, sizeof(buffer)) == OK) {
        findByString(vec, buffer, "name");
      } else {
        printErrors(INVALID_INPUT);
      }
      break;

    case 4:
      printf("Введите группу: ");
      if (readNonEmptyString(buffer, sizeof(buffer)) == OK) {
        findByString(vec, buffer, "group");
      } else {
        printErrors(INVALID_INPUT);
      }
      break;

    case 5:
      qsort(vec->students, vec->count, sizeof(Student *), compareById);
      printf("Студенты отсортированы по id\n");
      break;

    case 6:
      qsort(vec->students, vec->count, sizeof(Student *), compareBySurname);
      printf("Студенты отсортированы по Фамилии\n");
      break;

    case 7:
      qsort(vec->students, vec->count, sizeof(Student *), compareByName);
      printf("Студенты отсортированны по имени\n");
      break;

    case 8:
      qsort(vec->students, vec->count, sizeof(Student *), compareByGroup);
      printf("Студеннты отсортированны по группе\n");
      break;

    case 9:
      printf("Введите id для логгирования: ");
      if (readUnsignedInt(&id) == OK) {
        status = logStudentById(vec, id, traceFile);
        if (status == OK) {
          printf("Данные студента %u записаны в лог\n", id);
        } else {
          printErrors(status);
        }
      } else {
        printErrors(INVALID_INPUT);
      }
      break;

    case 10:
      status = logStudentsAboveAverage(vec, traceFile);
      if (status == OK) {
        printf("Данные студентов с баллом выше среднего записаны в лог\n");
      } else {
        printErrors(status);
      }
      break;

    case 11:
      for (size_t i = 0; i < vec->count; ++i) {
        printStudent(vec->students[i]);
      }
      break;

    case 0:
      printf("Выход\n");
      break;

    default:
      printf("Неверная опция\n");
      break;
    }
  }

  return OK;
}
