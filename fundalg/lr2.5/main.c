#include "actions.h"

int main(void) {
  char inputPath[MAX_PATH_LEN];
  char outputPath[MAX_PATH_LEN];
  StatusCode status;

  printf("Введите путь к входному файлу: ");
  status = readLineSafe(inputPath, MAX_PATH_LEN);

  if (status != OK) {
    printErrors(status);
    return status;
  }

  printf("Введите путь к выходному файлу: ");
  status = readLineSafe(outputPath, MAX_PATH_LEN);
  if (status != OK) {
    printErrors(status);
    return status;
  }

  if (strcmp(inputPath, outputPath) == 0) {
    status = INVALID_INPUT;
    printErrors(status);
    fprintf(stderr, "Файлы не должны совпадать\n");
    return status;
  }

  status = processFiles(inputPath, outputPath);
  if (status == OK) {
    printf("успешно\n");
  } else {
    printErrors(status);
  }

  return status;
}
