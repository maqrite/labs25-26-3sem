#include "studentVector.h"
#include <stdlib.h>

StatusCode initVector(StudentVector *vec, size_t initCapacity) {
  if (initCapacity == 0) {
    initCapacity = 10;
  }
  vec->students = malloc(initCapacity * sizeof(Student *));
  if (!vec->students) {
    return MEMORY_ALLOC_ERROR;
  }
  vec->count = 0;
  vec->capacity = initCapacity;

  return OK;
}

StatusCode resizeVector(StudentVector *vec) {
  size_t newCapacity = vec->capacity * 2;
  Student **newStudents =
      realloc(vec->students, newCapacity * sizeof(Student *));
  if (!newStudents) {
    return MEMORY_ALLOC_ERROR;
  }

  vec->students = newStudents;
  vec->capacity = newCapacity;

  return OK;
}

StatusCode addStudentToVector(StudentVector *vec, Student *student) {
  if (vec->count == vec->capacity) {
    StatusCode status = resizeVector(vec);
    if (status != OK) {
      return status;
    }
  }

  vec->students[vec->count] = student;
  vec->count++;

  return OK;
}

void freeVector(StudentVector *vec) {
  if (vec) {
    for (size_t i = 0; i < vec->count; ++i) {
      freeStudent(vec->students[i]);
    }

    free(vec->students);
    vec->students = NULL;
    vec->count = 0;
    vec->capacity = 0;
  }
}
