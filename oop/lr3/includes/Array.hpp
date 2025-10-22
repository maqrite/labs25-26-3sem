#pragma once

#include "Figure.hpp"

class Array {
public:
  Array();

  ~Array();

  Array(const Array &other);

  Array &operator=(const Array &other);

  Array(Array &&other) noexcept;

  Array &operator=(Array &&other) noexcept;

  void push_back(Figure *fig);

  void remove(size_t index);

  Figure *operator[](size_t index) const;

  size_t size() const;

private:
  Figure **data_;
  size_t size_;
  size_t capacity_;

  void resize(size_t new_capacity);
};
