#ifndef STUDENT_H
#define STUDENT_H

#include "common.h"
#include <stdio.h>
#include <stdlib.h>

#define NUM_GRADES 5

typedef struct {
  unsigned int id;
  char *name;
  char *surname;
  char *group;
  unsigned char *grades;
} Student;

StatusCode createStudent(Student **studentPtr, unsigned int id,
                         const char *name, const char *surname,
                         const char *group, const unsigned char *grades);

void freeStudent(Student *student);
void printStudent(const Student *student);
double calculateAverage(const Student *student);

#endif
