#include "actions.h"

int main(int argc, char *argv[]) {
  if (argc != 3) {
    PrintErrors(INVALID_NUMBER_OF_ARGS);
    return INVALID_NUMBER_OF_ARGS;
  }

  const char *inputFile = argv[1];
  const char *outputFile = argv[2];

  StatusCode status = processFiles(inputFile, outputFile);

  if (status != OK) {
    PrintErrors(status);
    return status;
  }

  return OK;
}
