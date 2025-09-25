#include "actions.h"

int main(int argc, char *argv[]) {

  if (argc <= 2 || argc > 4) {
    PrintExceptions(INVALID_NUMBER_OF_ARGS);
    return INVALID_NUMBER_OF_ARGS;
  }

  InputFlag flag;
  StatusCode status = FlagParse(&flag, argv, argc);

  if (status != OK) {
    PrintExceptions(status);
    return status;
  }

  char *inputFilename = argv[2];
  char *outputFilename = NULL;

  if (flag.isN) {
    outputFilename = argv[3];
  } else {

    size_t len = strlen("out_") + strlen(inputFilename) + 1;
    outputFilename = (char *)malloc(len);

    if (outputFilename == NULL) {
      PrintExceptions(MEMORY_ALLOC_ERROR);
      return MEMORY_ALLOC_ERROR;
    }

    strcpy(outputFilename, "out_");
    strcat(outputFilename, inputFilename);
  }

  FILE *inFile = fopen(inputFilename, "r");
  if (inFile == NULL) {
    PrintExceptions(FILE_OPEN_ERROR);

    if (!flag.isN) {
      free(outputFilename);
    }

    return FILE_OPEN_ERROR;
  }

  FILE *outFile = fopen(outputFilename, "w");
  if (outFile == NULL) {
    PrintExceptions(FILE_OPEN_ERROR);
    fclose(inFile);
    if (!flag.isN) {
      free(outputFilename);
    }
    return FILE_OPEN_ERROR;
  }

  char buffer[1024];
  while (fgets(buffer, sizeof(buffer), inFile) != NULL) {
    buffer[strcspn(buffer, "\n")] = 0;

    char *resultString = NULL;
    StatusCode actionStatus;

    switch (flag.option) {
    case 'd':
      actionStatus = forD(buffer, &resultString);
      break;

    case 'i':
      actionStatus = forI(buffer, &resultString);
      break;

    case 's':
      actionStatus = forS(buffer, &resultString);
      break;

    case 'a':
      actionStatus = forA(buffer, &resultString);
      break;
    }

    if (actionStatus != OK) {
      PrintExceptions(actionStatus);
      fclose(inFile);
      fclose(outFile);
      if (!flag.isN) {
        free(outputFilename);
      }
      return actionStatus;
    }

    fprintf(outFile, "%s\n", resultString);
    free(resultString);
  }

  fclose(inFile);
  fclose(outFile);

  if (!flag.isN) {
    free(outputFilename);
  }

  return 0;
}
