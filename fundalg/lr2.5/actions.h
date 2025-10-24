#ifndef ACTIONS_H
#define ACTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_WIDTH 80
#define MAX_PATH_LEN 1024
#define MAX_INPUT_LINE 8192

typedef enum {
  OK = 0,
  INVALID_INPUT = 1,
  FILE_OPEN_ERROR = 2,
  FILE_READ_ERROR = 3,
  FILE_WRITE_ERROR = 4,
  MEMORY_ALLOC_ERROR = 5,
  END_OF_FILE = 100,
} StatusCode;

void printErrors(StatusCode status);

void freeWords(char **words, int wordCount);

StatusCode writeLongWord(FILE *file, const char *word);

StatusCode writeLine(FILE *file, char **words, int wordCount, int charCount,
                     int justify);

StatusCode processLine(FILE *outFile, char *line);

StatusCode processFiles(const char *inputPath, const char *outputPath);

StatusCode readLineSafe(char *buffer, size_t size);

#endif
