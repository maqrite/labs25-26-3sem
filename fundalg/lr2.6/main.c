#include "actions.h"
#include "fileIo.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printErrors(INVALID_ARGC);
    return INVALID_ARGC;
  }

  const char *inputFile = argv[1];
  const char *traceFile = argv[2];

  FILE *fTrace = fopen(traceFile, "w");
  if (!fTrace) {
    printErrors(FILE_OPEN_ERROR);
    return FILE_OPEN_ERROR;
  }

  StudentVector vec;
  StatusCode status = initVector(&vec, 10);
  if (status != OK) {
    printErrors(status);
    fclose(fTrace);
    return status;
  }

  status = loadVectorFromFile(&vec, inputFile);

  if (status != OK) {
    printErrors(status);
    freeVector(&vec);
    fclose(fTrace);
    return status;
  }

  printf("Загружено %zu студентов\n", vec.count);

  status = runIntDialog(&vec, fTrace);

  printf("Очистка\n");
  freeVector(&vec);
  fclose(fTrace);

  printf("OK");

  return status;
}
