#include "actions.h"
#include <assert.h>
#include <stdio.h>

#define defaultEpsilon 0.000000001

void test_hasFinReprImpl();
void test_checkFinRepres();

int main() {
  test_hasFinReprImpl();
  test_checkFinRepres();

  printf("All internal tests passed successfully!\n");
  return 0;
}

void test_hasFinReprImpl() {
  printf("Running tests for hasFinReprImpl...\n");

  assert(hasFinReprImpl(0.5, 2, defaultEpsilon) == true);
  assert(hasFinReprImpl(0.5, 10, defaultEpsilon) == true);
  assert(hasFinReprImpl(0.25, 10, defaultEpsilon) == true);
  assert(hasFinReprImpl(1.0 / 9.0, 6, defaultEpsilon) == true);
  assert(hasFinReprImpl(1.0 / 3.0, 10, defaultEpsilon) == false);
  assert(hasFinReprImpl(0.1, 2, defaultEpsilon) == false);
  assert(hasFinReprImpl(1.0 / 5.0, 6, defaultEpsilon) == false);
}

void test_checkFinRepres() {
  printf("Running tests for checkFinRepres...\n");
  StatusCode status;
  int count = 3;
  bool results[count];

  status = checkFinRepres(results, 10, count, 0.5, 0.25, 1.0 / 3.0);
  assert(status == OK);
  assert(results[0] == true);
  assert(results[1] == true);
  assert(results[2] == false);

  status = checkFinRepres(results, 1, 1, 0.5);
  assert(status == INVALID_BASE);

  status = checkFinRepres(results, 10, 1, -0.5);
  assert(status == INVALID_FRACTION);

  status = checkFinRepres(results, 10, 1, 1.0);
  assert(status == INVALID_FRACTION);
}
