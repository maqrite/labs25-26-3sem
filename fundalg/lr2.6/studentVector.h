#ifndef STUDENT_VECTOR_H
#define STUDENT_VECTOR_H

#include "student.h"

typedef struct {
  Student **students;
  size_t count;
  size_t capacity;
} StudentVector;

StatusCode initVector(StudentVector *vec, size_t initCapacity);
StatusCode addStudentToVector(StudentVector *vec, Student *student);
void freeVector(StudentVector *vec);

#endif
