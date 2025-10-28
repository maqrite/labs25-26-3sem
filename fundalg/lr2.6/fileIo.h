#ifndef FILE_IO_H
#define FILE_IO_H

#include "studentVector.h"

StatusCode loadVectorFromFile(StudentVector *vec, const char *filename);
StatusCode logStudentById(const StudentVector *vec, unsigned int id,
                          FILE *traceFile);
StatusCode logStudentsAboveAverage(const StudentVector *vec, FILE *traceFile);

#endif
