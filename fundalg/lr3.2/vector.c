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
