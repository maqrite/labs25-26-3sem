#ifndef ACTIONS_H
#define ACTIONS_H

#include "common.h"
#include "studentVector.h"
#include <stdio.h>

void printErrors(StatusCode status);

StatusCode runIntDialog(StudentVector *vec, FILE *traceFile);

int compareById(const void *a, const void *b);
int compareBySurname(const void *a, const void *b);
int compareByName(const void *a, const void *b);
int compareByGroup(const void *a, const void *b);

#endif
