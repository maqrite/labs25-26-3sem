#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define VECTOR_TYPE char

#include "actions.h"
#include "vector.h"

VECTOR_TYPE copy_char(VECTOR_TYPE val) { return val; }
void delete_char(VECTOR_TYPE val) { (void)val; }

void test_create_push_get_char() {
  printf("Running: test_create_push_get (char)\n");
  Vector v = create_vector(2, copy_char, delete_char);

  assert(v.size == 0);
  assert(v.capacity == 2);

  push_back_vector(&v, 'a');
  push_back_vector(&v, 'b');
  assert(v.size == 2);
  assert(get_at_vector(&v, 0) == 'a');
  assert(get_at_vector(&v, 1) == 'b');

  erase_vector(&v);
  printf("PASS (char)\n");
}

void test_copy_and_equal_char() {
  printf("Running: test_copy_and_equal (char)\n");
  Vector v1 = create_vector(8, copy_char, delete_char);
  push_back_vector(&v1, 'x');
  push_back_vector(&v1, 'y');

  Vector v2 = create_vector(0, copy_char, delete_char);
  assert(is_equal_vector(&v1, &v2) == 0);

  copy_vector(&v2, &v1);
  assert(is_equal_vector(&v1, &v2) == 1);

  erase_vector(&v1);
  erase_vector(&v2);
  printf("PASS (char)\n");
}

int main() {
  printf("Запуск тестов для char\n");
  test_create_push_get_char();
  test_copy_and_equal_char();
  printf("Тесты для char пройдены\n\n");
  return 0;
}
