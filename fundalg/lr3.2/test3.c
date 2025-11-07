#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define VECTOR_TYPE unsigned long long

#include "actions.h"
#include "vector.h"

VECTOR_TYPE copy_ull(VECTOR_TYPE val) { return val; }
void delete_ull(VECTOR_TYPE val) { (void)val; }

void test_create_push_get_ull() {
  printf("Running: test_create_push_get (ull)\n");
  Vector v = create_vector(2, copy_ull, delete_ull);

  assert(v.size == 0);
  assert(v.capacity == 2);

  push_back_vector(&v, 1000000000000ULL);
  push_back_vector(&v, 2000000000000ULL);
  assert(v.size == 2);
  assert(get_at_vector(&v, 0) == 1000000000000ULL);
  assert(get_at_vector(&v, 1) == 2000000000000ULL);

  erase_vector(&v);
  printf("PASS (ull)\n");
}

void test_copy_and_equal_ull() {
  printf("Running: test_copy_and_equal (ull)\n");
  Vector v1 = create_vector(8, copy_ull, delete_ull);
  push_back_vector(&v1, 9876543210ULL);

  Vector *v3 = copy_vector_new(&v1);
  assert(v3 != NULL);
  assert(is_equal_vector(&v1, v3) == 1);

  push_back_vector(&v1, 1ULL);
  assert(is_equal_vector(&v1, v3) == 0);

  erase_vector(&v1);
  delete_vector(v3);
  printf("PASS (ull)\n");
}

int main() {
  printf("Запуск тестов для unsigned long long\n");
  test_create_push_get_ull();
  test_copy_and_equal_ull();
  printf("Тесты для unsigned long long пройдены\n\n");
  return 0;
}
