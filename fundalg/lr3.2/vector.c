#include "vector.h"

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
