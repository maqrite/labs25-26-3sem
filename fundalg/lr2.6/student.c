#include "student.h"
#include "actions.h"
#include <stdlib.h>
#include <string.h>

StatusCode dublicateString(char **dest, const char *src) {
  size_t len = strlen(src) + 1;
  *dest = malloc(len);
  if (!*dest) {
    return MEMORY_ALLOC_ERROR;
  }
  memcpy(*dest, src, len);
  return OK;
}

StatusCode createStudent(Student **studentPtr, unsigned int id,
                         const char *name, const char *surname,
                         const char *group, const unsigned char *grades) {

  Student *s = malloc(sizeof(Student));
  if (!s) {
    return MEMORY_ALLOC_ERROR;
  }
  s->id = id;
  s->name = NULL;
  s->surname = NULL;
  s->group = NULL;
  s->grades = NULL;

  StatusCode status = OK;

  if (status == OK) {
    status = dublicateString(&s->surname, surname);
  }
  if (status == OK) {
    status = dublicateString(&s->name, name);
  }
  if (status == OK) {
    status = dublicateString(&s->group, group);
  }

  if (status == OK) {
    s->grades = malloc(NUM_GRADES * sizeof(unsigned char));
    if (!s->grades) {
      status = MEMORY_ALLOC_ERROR;
    } else {
      memcpy(s->grades, grades, NUM_GRADES * sizeof(unsigned char));
    }
  }

  if (status != OK) {
    freeStudent(s);
    *studentPtr = NULL;
    return MEMORY_ALLOC_ERROR;
  }

  *studentPtr = s;
  return OK;
}

void freeStudent(Student *student) {
  if (student) {
    free(student->name);
    free(student->surname);
    free(student->group);
    free(student->grades);
    free(student);
  }
}

void printStudent(const Student *student) {
  if (!student) {
    return;
  }

  printf(
      "ID: %-5u | ФИО: %-15s %-15s | Группа: %-10s | Оценки: %u %u %u %u %u\n",
      student->id, student->surname, student->name, student->group,
      student->grades[0], student->grades[1], student->grades[2],
      student->grades[3], student->grades[4]);
}

double calculateAverage(const Student *student) {
  if (!student) {
    return 0.0;
  }
  unsigned int sum = 0;
  for (int i = 0; i < NUM_GRADES; ++i) {
    sum += student->grades[i];
  }

  return (double)sum / NUM_GRADES;
}
