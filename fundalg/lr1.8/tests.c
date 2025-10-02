#include "actions.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

void test_charToDigit();
void test_toLongLong();
void test_fromLongLong();
void test_reverseString();

int main() {
  test_charToDigit();
  test_toLongLong();
  test_reverseString();
  test_fromLongLong();

  printf("All internal tests passed successfully!\n");
  return 0;
}

void test_charToDigit() {
  printf("Running tests for charToDigit...\n");
  int digit;
  assert(charToDigit('7', &digit) == OK && digit == 7);
  assert(charToDigit('a', &digit) == OK && digit == 10);
  assert(charToDigit('Z', &digit) == OK && digit == 35);
  assert(charToDigit('!', &digit) == INVALID_NUMBER_FORMAT);
}

void test_toLongLong() {
  printf("Running tests for toLongLong...\n");
  long long result;
  assert(toLongLong("101", 2, &result) == OK && result == 5);
  assert(toLongLong("ff", 16, &result) == OK && result == 255);
  assert(toLongLong("-1A", 16, &result) == OK && result == -26);
  assert(toLongLong("Z", 36, &result) == OK && result == 35);
  assert(toLongLong("123", 2, &result) == INVALID_NUMBER_FORMAT);
  assert(toLongLong("", 10, &result) == INVALID_NUMBER_FORMAT);
}

void test_reverseString() {
  printf("Running tests for reverseString...\n");
  char str1[] = "abcd";
  reverseString(str1);
  assert(strcmp(str1, "dcba") == 0);

  char str2[] = "abcde";
  reverseString(str2);
  assert(strcmp(str2, "edcba") == 0);

  char str3[] = "";
  reverseString(str3);
  assert(strcmp(str3, "") == 0);
}

void test_fromLongLong() {
  printf("Running tests for fromLongLong...\n");
  char *resultStr = NULL;

  assert(fromLongLong(255, 16, &resultStr) == OK &&
         strcmp(resultStr, "FF") == 0);
  free(resultStr);

  assert(fromLongLong(-26, 16, &resultStr) == OK &&
         strcmp(resultStr, "-1A") == 0);
  free(resultStr);

  assert(fromLongLong(0, 10, &resultStr) == OK && strcmp(resultStr, "0") == 0);
  free(resultStr);

  assert(fromLongLong(35, 36, &resultStr) == OK && strcmp(resultStr, "Z") == 0);
  free(resultStr);
}
