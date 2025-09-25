#include "actions.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

void test_FlagParse();
void test_forD();
void test_forI();
void test_forS();
void test_forA();

int main() {
  test_FlagParse();
  test_forD();
  test_forI();
  test_forS();
  test_forA();

  printf("All internal tests passed successfully!\n");
  return 0;
}

void test_FlagParse() {
  printf("Running tests for FlagParse...\n");
  InputFlag flag;
  StatusCode status;

  char *argv1[] = {"./app", "-d", "file.txt"};
  status = FlagParse(&flag, argv1, 3);
  assert(status == OK && flag.isN == false && flag.option == 'd');

  char *argv2[] = {"./app", "/nd", "in.txt", "out.txt"};
  status = FlagParse(&flag, argv2, 4);
  assert(status == OK && flag.isN == true && flag.option == 'd');

  char *argv3[] = {"./app", "-d", "file.txt", "extra.txt"};
  status = FlagParse(&flag, argv3, 4);
  assert(status == INVALID_NUMBER_OF_ARGS);

  char *argv4[] = {"./app", "-x", "file.txt"};
  status = FlagParse(&flag, argv4, 3);
  assert(status == FLAG_ERROR);
}

void test_forD() {
  printf("Running tests for forD (delete digits)...\n");
  char *output = NULL;
  forD("abc123xyz", &output);
  assert(strcmp(output, "abcxyz") == 0);
  free(output);

  forD("12345", &output);
  assert(strcmp(output, "") == 0);
  free(output);
}

void test_forI() {
  printf("Running tests for forI (count letters)...\n");
  char *output = NULL;
  forI("Hello World 123!", &output);
  assert(strcmp(output, "10") == 0);
  free(output);

  forI("123!@#", &output);
  assert(strcmp(output, "0") == 0);
  free(output);
}

void test_forS() {
  printf("Running tests for forS (count special chars)...\n");
  char *output = NULL;
  forS("abc 123 !@#$", &output);
  assert(strcmp(output, "4") == 0);
  free(output);

  forS("Just letters and numbers", &output);
  assert(strcmp(output, "0") == 0);
  free(output);
}

void test_forA() {
  printf("Running tests for forA (ASCII to hex)...\n");
  char *output = NULL;
  forA("a1b2", &output);
  assert(strcmp(output, "611622") == 0);
  free(output);

  forA("Hi!", &output);
  assert(strcmp(output, "486921") == 0);
  free(output);
}
