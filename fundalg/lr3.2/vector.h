#ifndef VECTOR_H
#define VECTOR_H

#include "actions.h"

#include <cstddef>
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

Vector create_vector(size_t initialCapacity,
                     VECTOR_TYPE (*copyFunc)(VECTOR_TYPE),
                     void (*deleteFunc)(VECTOR_TYPE));

void erase_vector(Vector *);

int is_equal_vector(const Vector *v1, const Vector *v2);

void copy_vector(Vector *dest, const Vector *src);

Vector *copy_vector_new(const Vector *src);

void push_back_vector(Vector *v, VECTOR_TYPE value);

void delete_at_vector(Vector *v, size_t index);

VECTOR_TYPE get_at_vector(const Vector *v, size_t index);

void delete_vector(Vector *v);

#endif
