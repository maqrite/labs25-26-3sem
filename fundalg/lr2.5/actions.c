#include "actions.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#define MAX_WORDS_PER_LINE (MAX_INPUT_LINE / 2 + 1)

void printErrors(StatusCode status) {
  switch (status) {

  case INVALID_INPUT:
    printf("ошибка, неверный ввод\n");
    break;

  case FILE_OPEN_ERROR:
    printf("Ошибка открытия файла\n");
    break;

  case FILE_READ_ERROR:
    printf("Ошибка чтения файла\n");
    break;

  case FILE_WRITE_ERROR:
    printf("Ошибка записи в файл\n");
    break;

  case MEMORY_ALLOC_ERROR:
    printf("Ошибка выделения памяти\n");
    break;

  default:
    break;
  }
}

void freeWords(char **words, int wordCount) {
  for (int i = 0; i < wordCount; ++i) {
    free(words[i]);
    words[i] = NULL;
  }
}

StatusCode writeLongWord(FILE *file, const char *word) {
  size_t len = strlen(word);
  size_t pos = 0;
  while (pos < len) {
    size_t charsToWrite = (len - pos > LINE_WIDTH) ? LINE_WIDTH : (len - pos);

    if (fwrite(word + pos, 1, charsToWrite, file) != charsToWrite) {
      return FILE_WRITE_ERROR;
    }

    if (fprintf(file, "\n") < 0) {
      return FILE_WRITE_ERROR;
    }

    pos += charsToWrite;
  }

  return OK;
}

StatusCode writeLine(FILE *file, char **words, int wordCount, int charCount,
                     int justify) {
  if (wordCount == 0) {
    return OK;
  }

  if (!justify || wordCount == 1) {
    for (int i = 0; i < wordCount; ++i) {
      if (fprintf(file, "%s%s", words[i], (i == wordCount - 1) ? "" : " ") <
          0) {
        return FILE_WRITE_ERROR;
      }
    }
  } else {
    int spacesNeeded = LINE_WIDTH - charCount;
    int gaps = wordCount - 1;

    if (fprintf(file, "%s", words[0]) < 0) {
      return FILE_WRITE_ERROR;
    }

    for (int i = 1; i < wordCount; ++i) {
      int baseSpaces = spacesNeeded / gaps;
      int extraSpaces = (i - 1 < spacesNeeded % gaps) ? 1 : 0;
      int totalSpaces = baseSpaces + extraSpaces;

      for (int j = 0; j < totalSpaces; ++j) {
        if (fputc(' ', file) == EOF) {
          return FILE_WRITE_ERROR;
        }
      }

      if (fprintf(file, "%s", words[i]) < 0) {
        return FILE_WRITE_ERROR;
      }
    }
  }

  if (fprintf(file, "\n") < 0) {
    return FILE_WRITE_ERROR;
  }

  return OK;
}

StatusCode processLine(FILE *outFile, char *line) {
  char *words[MAX_WORDS_PER_LINE] = {NULL};
  int wordCount = 0;
  int charCount = 0;
  int currentLineLen = 0;
  StatusCode status = OK;

  char *lineEnd = strchr(line, '\n');
  if (lineEnd) {
    *lineEnd = '\0';
  }

  if (line[0] == '\0') {
    if (fprintf(outFile, "\n") < 0) {
      return FILE_WRITE_ERROR;
    }

    return OK;
  }

  char *word = strtok(line, " \t\n\v\f\r");
  while (word != NULL && status == OK) {
    size_t wordLen = strlen(word);

    if (wordLen == 0) {
      word = strtok(NULL, " \t\n\v\f\r");
      continue;
    }

    if (wordLen > LINE_WIDTH) {
      status = writeLine(outFile, words, wordCount, charCount, 1);
      freeWords(words, wordCount);
      wordCount = 0;
      charCount = 0;
      currentLineLen = 0;

      if (status == OK) {
        status = writeLongWord(outFile, word);
      }
    } else {
      int requiredLen = currentLineLen + wordLen + (wordCount > 0 ? 1 : 0);

      if (requiredLen <= LINE_WIDTH) {
        words[wordCount] = strdup(word);

        if (!words[wordCount]) {
          status = MEMORY_ALLOC_ERROR;
          break;
        }

        wordCount++;
        charCount += (int)wordLen;
        currentLineLen = requiredLen;
      } else {
        status = writeLine(outFile, words, wordCount, charCount, 1);
        freeWords(words, wordCount);

        words[0] = strdup(word);

        if (!words[0]) {
          status = MEMORY_ALLOC_ERROR;
          break;
        }

        wordCount = 1;
        charCount = (int)wordLen;
        currentLineLen = (int)wordLen;
      }
    }

    word = strtok(NULL, " \t\n\v\f\r");
  }

  if (status == OK && wordCount > 0) {
    status = writeLine(outFile, words, wordCount, charCount, 0);
  }

  freeWords(words, wordCount);

  return status;
}

StatusCode processFiles(const char *inputPath, const char *outputPath) {
  FILE *inFile = fopen(inputPath, "r");
  if (!inFile) {
    return FILE_OPEN_ERROR;
  }

  FILE *outFile = fopen(outputPath, "w");
  if (!outFile) {
    fclose(inFile);
    return FILE_OPEN_ERROR;
  }

  char lineBuffer[MAX_INPUT_LINE];
  StatusCode status = OK;

  while (fgets(lineBuffer, MAX_INPUT_LINE, inFile)) {
    if (ferror(inFile)) {
      status = FILE_READ_ERROR;
      break;
    }

    status = processLine(outFile, lineBuffer);
    if (status != OK) {
      break;
    }
  }

  if (ferror(inFile) && status == OK) {
    status = FILE_READ_ERROR;
  }

  fclose(inFile);
  if (fclose(outFile) != 0 && status == OK) {
    status = FILE_WRITE_ERROR;
  }

  return status;
}

StatusCode readLineSafe(char *buffer, size_t size) {
  if (fgets(buffer, (int)size, stdin) == NULL) {
    if (feof(stdin)) {
      return END_OF_FILE;
    }
    return FILE_READ_ERROR;
  }

  buffer[strcspn(buffer, "\n")] = '\0';

  if (buffer[0] == '\0') {
    return INVALID_INPUT;
  }

  return OK;
}
