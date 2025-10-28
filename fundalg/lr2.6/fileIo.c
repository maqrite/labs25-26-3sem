#include "fileIo.h"
#include "validation.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const double EPSILON = 1e-6;

StatusCode parseLine(char *line, StudentVector *vec) {
  const char *delim = ",";
  char *token;

  unsigned int id;
  char *surname;
  char *name;
  char *group;
  unsigned char grades[NUM_GRADES];

  token = strtok(line, delim);
  if (!token) {
    return BAD_FILE_FORMAT;
  }

  char *pEnd;

  id = (unsigned int)strtoul(token, &pEnd, 10);
  if (*pEnd != '\0') {
    return BAD_FILE_FORMAT;
  }

  surname = strtok(NULL, delim);
  if (!isAlphaString(surname)) {
    return INVALID_STUDENT_DATA;
  }

  name = strtok(NULL, delim);
  if (!isAlphaString(name)) {
    return INVALID_STUDENT_DATA;
  }

  group = strtok(NULL, delim);
  if (!isNonEmptyString(group)) {
    return INVALID_STUDENT_DATA;
  }

  for (int i = 0; i < NUM_GRADES; ++i) {
    token = strtok(NULL, delim);
    if (!token) {
      return BAD_FILE_FORMAT;
    }

    long grade = strtol(token, &pEnd, 10);
    if (*pEnd != '\0' || grade < 0 || grade > 255) {
      return BAD_FILE_FORMAT;
    }

    grades[i] = (unsigned char)grade;
  }

  if (strtok(NULL, delim) != NULL) {
    return BAD_FILE_FORMAT;
  }

  Student *newStudent = NULL;
  StatusCode status =
      createStudent(&newStudent, id, name, surname, group, grades);
  if (status != OK) {
    return status;
  }

  status = addStudentToVector(vec, newStudent);
  if (status != OK) {
    freeStudent(newStudent);
    return status;
  }

  return OK;
}

StatusCode loadVectorFromFile(StudentVector *vec, const char *filename) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    return FILE_OPEN_ERROR;
  }

  char lineBuffer[1024];
  StatusCode status = OK;
  int lineNum = 0;

  while (fgets(lineBuffer, sizeof(lineBuffer), file)) {
    lineNum++;
    lineBuffer[strcspn(lineBuffer, "\n")] = 0;

    if (lineBuffer[0] == '\0') {
      continue;
    }

    status = parseLine(lineBuffer, vec);
    if (status != OK) {
      fprintf(stderr, "ошибка парсинга в файле на строке %d\n", lineNum);
      break;
    }
  }

  fclose(file);
  return status;
}

StatusCode logStudentById(const StudentVector *vec, unsigned int id,
                          FILE *traceFile) {
  Student *found = NULL;

  for (size_t i = 0; i < vec->count; ++i) {
    if (vec->students[i]->id == id) {
      found = vec->students[i];
      break;
    }
  }

  if (found) {
    fprintf(traceFile, "Найден по ID: %u\n", id);
    fprintf(traceFile, "ФИО: %s %s\n", found->surname, found->name);
    fprintf(traceFile, "Группа: %s\n", found->group);
    fprintf(traceFile, "Средний балл: %.2f\n", calculateAverage(found));
    fflush(traceFile);
    return OK;
  } else {
    return STUDENT_NOT_FOUND;
  }
}

StatusCode logStudentsAboveAverage(const StudentVector *vec, FILE *traceFile) {
  if (vec->count == 0) {
    fprintf(traceFile, "Нет студентов для расчета среднего\n");
    return OK;
  }

  double totalAverage = 0.0;
  for (size_t i = 0; i < vec->count; ++i) {
    totalAverage += calculateAverage(vec->students[i]);
  }

  totalAverage /= vec->count;

  fprintf(traceFile, "Студенты с баллом > %.2f (общий средний):\n",
          totalAverage);
  int found = 0;

  for (size_t i = 0; i < vec->count; ++i) {
    double avg = calculateAverage(vec->students[i]);

    if ((avg - totalAverage) > EPSILON) {
      fprintf(traceFile, "фамилия: %s, Имя: %s, Балл: %.2f\n",
              vec->students[i]->surname, vec->students[i]->name, avg);
      found = 1;
    }
  }

  if (!found) {
    fprintf(traceFile, "Студенты с баллом выше среднего не найдены\n");
  }

  fflush(traceFile);

  return OK;
}
