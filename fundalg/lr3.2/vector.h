#ifndef VECTOR_H
#define VECTOR_H

#include "actions.h"

#include <stddef.h>

#ifndef VECTOR_TYPE

#define VECTOR_TYPE size_t // убрать потом size_t

// #error "VECTOR_TYPE не определен"

#endif

typedef struct {
  VECTOR_TYPE *data;
  size_t size;
  size_t capacity;

  VECTOR_TYPE (*copyVoidPtr)(VECTOR_TYPE);
  void (*deleteVoidPtr)(VECTOR_TYPE);
} Vector;

#endif
