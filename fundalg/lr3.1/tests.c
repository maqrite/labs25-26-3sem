#include "actions.h"
#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

void test_reverse_string(void);
void test_convert_to_base_2r(void);

int main(void) {
  printf("Запуск внутренних тестов...\n");

  test_reverse_string();
  test_convert_to_base_2r();

  printf("Все внутренние тесты пройдены!\n");
  return 0;
}

void test_reverse_string(void) {
  printf("  Тестирование reverseString...\n");

  char str_even[] = "ABCD";
  reverseString(str_even, 4);
  assert(strcmp(str_even, "DCBA") == 0);

  char str_odd[] = "ABC";
  reverseString(str_odd, 3);
  assert(strcmp(str_odd, "CBA") == 0);

  char str_one[] = "A";
  reverseString(str_one, 1);
  assert(strcmp(str_one, "A") == 0);

  char str_empty[] = "";
  reverseString(str_empty, 0);
  assert(strcmp(str_empty, "") == 0);
}

void test_convert_to_base_2r(void) {
  printf("  Тестирование convertToBase2r...\n");
  char buffer[65];
  StatusCode status;

  status = convertToBase2r(10, 1, buffer, sizeof(buffer));
  assert(status == OK);
  assert(strcmp(buffer, "1010") == 0);

  status = convertToBase2r(10, 4, buffer, sizeof(buffer));
  assert(status == OK);
  assert(strcmp(buffer, "A") == 0);

  status = convertToBase2r(31, 5, buffer, sizeof(buffer));
  assert(status == OK);
  assert(strcmp(buffer, "V") == 0);

  status = convertToBase2r(UINT_MAX, 4, buffer, sizeof(buffer));
  assert(status == OK);
  assert(strcmp(buffer, "FFFFFFFF") == 0);

  status = convertToBase2r((unsigned int)-10, 4, buffer, sizeof(buffer));
  assert(status == OK);
  assert(strcmp(buffer, "FFFFFFF6") == 0);

  status = convertToBase2r((unsigned int)-10, 5, buffer, sizeof(buffer));
  assert(status == OK);
  assert(strcmp(buffer, "3VVVVVM") == 0);

  status = convertToBase2r(0, 2, buffer, sizeof(buffer));
  assert(status == OK);
  assert(strcmp(buffer, "0") == 0);

  status = convertToBase2r(10, 6, buffer, sizeof(buffer));
  assert(status == INVALID_ARGS);
  status = convertToBase2r(10, 0, buffer, sizeof(buffer));
  assert(status == INVALID_ARGS);

  status = convertToBase2r(10, 4, NULL, sizeof(buffer));
  assert(status == INVALID_ARGS);

  status = convertToBase2r(10, 1, buffer, 3);
  assert(status == BUFFER_TOO_SMALL);
}
