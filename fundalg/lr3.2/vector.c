#include "vector.h"
#include "actions.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

Vector create_vector(size_t initialCapacity, size_t (*copyFunc)(size_t),
                     void (*deleteFunc)(size_t)) {

  Vector v;

  v.data = NULL;
  v.size = 0;
  v.capacity = 0;
  v.copyVoidPtr = copyFunc;
  v.deleteVoidPtr = deleteFunc;

  if (initialCapacity > 0) {
    v.data = (VECTOR_TYPE *)malloc(initialCapacity * sizeof(VECTOR_TYPE));
    if (v.data == NULL) {
      v.capacity = 0;
      return v;
    }

    v.capacity = initialCapacity;
  }

  return v;
}

void erase_vector(Vector *v) {
  if (v == NULL) {
    return;
  }

  for (size_t i = 0; i < v->size; i++) {
    v->deleteVoidPtr(v->data);
  }

  free(v->data);
  v->data = NULL;
  v->size = 0;
  v->capacity = 0;
}

int is_equal_vector(const Vector *v1, const Vector *v2) {
  if (v1->size != v2->size) {
    return 0;
  }

  for (size_t i = 0; i < v1->size; i++) {
    if (v1->data[i] != v2->data[i]) {
      return 0;
    }
  }

  return 1;
}

int vectorResize(Vector *v, size_t newCapacity) {
  if (newCapacity == 0) {
    free(v->data);
    v->data = NULL;
    v->capacity = 0;
    v->size = 0;
    return 0;
  }

  VECTOR_TYPE *newData =
      (VECTOR_TYPE *)realloc(v->data, newCapacity * sizeof(VECTOR_TYPE));
  if (newData == NULL) {
    return 1;
  }

  v->data = newData;
  v->capacity = newCapacity;

  return 0;
}

void copy_vector(Vector *dest, const Vector *src) {
  if (dest == NULL || src == NULL) {
    return;
  }

  erase_vector(dest);

  if (dest->capacity < src->size) {
    if (vectorResize(dest, src->size) != 0) {
      return;
    }
  }

  dest->copyVoidPtr = src->copyVoidPtr;
  dest->deleteVoidPtr = src->deleteVoidPtr;

  for (size_t i = 0; i < src->size; i++) {
    dest->data[i] = dest->copyVoidPtr(src->data[i]);
  }

  dest->size = src->size;
}

Vector *copy_vector_new(const Vector *src) {
  if (src == NULL) {
    return NULL;
  }

  Vector *newV = (Vector *)malloc(sizeof(Vector));
  if (newV == NULL) {
    return NULL;
  }

  newV->data = NULL;
  newV->size = 0;
  newV->capacity = 0;
  newV->copyVoidPtr = src->copyVoidPtr;
  newV->deleteVoidPtr = src->deleteVoidPtr;

  copy_vector(newV, src);

  return newV;
}

void push_back_vector(Vector *v, size_t value) {
  if (v == NULL) {
    return;
  }

  if (v->size == v->capacity) {
    size_t newCapacity = (v->capacity == 0) ? 8 : v->capacity * 2;

    if (vectorResize(v, newCapacity) != 0) {
      return;
    }
  }

  v->data[v->size] = v->copyVoidPtr(value);
  v->size++;
}

void delete_at_vector(Vector *v, size_t index) {
  if (v == NULL || index >= v->size) {
    return;
  }

  v->deleteVoidPtr(v->data[index]);

  if (index < v->size - 1) {
    memmove(&v->data[index], &v->data[index + 1],
            (v->size - index - 1) * sizeof(VECTOR_TYPE));
  }

  v->size--;
}

VECTOR_TYPE get_at_vector(const Vector *v, size_t index) {
  if (v == NULL || index >= v->size) {
    printf("выход за границы массива\n");
    exit(INVALID_INPUT);
  }

  return v->data[index];
}

void delete_vector(Vector *v) {
  if (v == NULL) {
    return;
  }

  erase_vector(v);
  free(v);
}
