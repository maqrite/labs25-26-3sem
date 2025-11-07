#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define VECTOR_TYPE int

#include "actions.h"
#include "vector.h"

VECTOR_TYPE copy_int(VECTOR_TYPE val) { return val; }

void delete_int(VECTOR_TYPE val) { (void)val; }

void print_test_vector(const char *title, const Vector *v) {
  printf("%s (size: %zu, cap: %zu): [ ", title, v->size, v->capacity);
  for (size_t i = 0; i < v->size; i++) {
    printf("%d ", get_at_vector(v, i));
  }
  printf("]\n");
}

void test_create_push_get() {
  printf("Running: test_create_push_get (int)\n");
  Vector v = create_vector(2, copy_int, delete_int);

  assert(v.size == 0);
  assert(v.capacity == 2);
  assert(v.data != NULL);

  push_back_vector(&v, 10);
  push_back_vector(&v, 20);
  assert(v.size == 2);
  assert(get_at_vector(&v, 0) == 10);
  assert(get_at_vector(&v, 1) == 20);

  push_back_vector(&v, 30);
  assert(v.size == 3);
  assert(v.capacity == 4);
  assert(get_at_vector(&v, 2) == 30);

  erase_vector(&v);
  printf("PASS (int)\n");
}

void test_delete_at() {
  printf("Running: test_delete_at (int)\n");
  Vector v = create_vector(8, copy_int, delete_int);
  push_back_vector(&v, 10);
  push_back_vector(&v, 20);
  push_back_vector(&v, 30);
  push_back_vector(&v, 40);
  push_back_vector(&v, 50);

  delete_at_vector(&v, 2);
  assert(v.size == 4);
  assert(get_at_vector(&v, 2) == 40);

  delete_at_vector(&v, 3);
  assert(v.size == 3);
  assert(get_at_vector(&v, 2) == 40);

  delete_at_vector(&v, 0);
  assert(v.size == 2);
  assert(get_at_vector(&v, 0) == 20);

  erase_vector(&v);
  printf("PASS (int)\n");
}

void test_copy_and_equal() {
  printf("Running: test_copy_and_equal (int)\n");
  Vector v1 = create_vector(8, copy_int, delete_int);
  push_back_vector(&v1, 100);
  push_back_vector(&v1, 200);

  Vector v2 = create_vector(0, copy_int, delete_int);

  assert(is_equal_vector(&v1, &v2) == 0);

  copy_vector(&v2, &v1);
  assert(is_equal_vector(&v1, &v2) == 1);
  assert(v2.size == 2);
  assert(v2.capacity >= 2);
  assert(get_at_vector(&v2, 1) == 200);

  Vector *v3 = copy_vector_new(&v1);
  assert(v3 != NULL);
  assert(is_equal_vector(&v1, v3) == 1);

  push_back_vector(&v1, 300);
  assert(is_equal_vector(&v1, v3) == 0);
  assert(v3->size == 2);

  erase_vector(&v1);
  erase_vector(&v2);
  delete_vector(v3);
  printf("PASS (int)\n");
}

int main() {
  printf("Запуск тестов для int\n");

  test_create_push_get();
  test_delete_at();
  test_copy_and_equal();

  printf("тесты для int пройдены\n\n");
  return 0;
}
