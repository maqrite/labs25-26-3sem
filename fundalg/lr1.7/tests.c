#include "actions.h"
#include <assert.h>
#include <stdio.h>

void test_getDigitValue();
void test_processNumber();

int main() {
  test_getDigitValue();
  test_processNumber();

  printf("All internal tests passed successfully!\n");
  return 0;
}

void test_getDigitValue() {
  printf("Running tests for getDigitValue...\n");
  int value;

  assert(getDigitValue('0', &value) == OK && value == 0);
  assert(getDigitValue('9', &value) == OK && value == 9);

  assert(getDigitValue('a', &value) == OK && value == 10);
  assert(getDigitValue('z', &value) == OK && value == 35);

  assert(getDigitValue('A', &value) == OK && value == 10);
  assert(getDigitValue('Z', &value) == OK && value == 35);

  assert(getDigitValue('!', &value) == INVALID_CHARACTER_IN_NUMBER);
  assert(getDigitValue('-', &value) == INVALID_CHARACTER_IN_NUMBER);
}

void test_processNumber() {
  printf("Running tests for processNumber...\n");
  int base;
  unsigned long long value;

  assert(processNumber("101", &base, &value) == OK && base == 2 && value == 5);
  assert(processNumber("12", &base, &value) == OK && base == 3 && value == 5);
  assert(processNumber("ff", &base, &value) == OK && base == 16 &&
         value == 255);
  assert(processNumber("z", &base, &value) == OK && base == 36 && value == 35);

  assert(processNumber("FF", &base, &value) == OK && base == 16 &&
         value == 255);
  assert(processNumber("Ff", &base, &value) == OK && base == 16 &&
         value == 255);

  assert(processNumber("0", &base, &value) == OK && base == 2 && value == 0);
  assert(processNumber("1", &base, &value) == OK && base == 2 && value == 1);
  assert(processNumber("007", &base, &value) == OK && base == 8 && value == 7);

  assert(processNumber("hello!", &base, &value) == INVALID_CHARACTER_IN_NUMBER);
  assert(processNumber("zzzzzzzzzzzzzzzzzzzz", &base, &value) ==
         NUMBER_OVERFLOW);
}
