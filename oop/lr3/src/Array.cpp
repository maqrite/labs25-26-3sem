#include "../includes/Array.hpp"
#include <cstddef>
#include <new>
#include <stdexcept>
#include <utility>

Array::Array() : data_(nullptr), size_(0), capacity_(0) {}

Array::~Array() {
  for (size_t i = 0; i < size_; ++i) {
    delete data_[i];
  }

  delete[] data_;
}

Array::Array(const Array &other)
    : size_(other.size_), capacity_(other.capacity_) {

  data_ = new Figure *[capacity_];

  for (size_t i = 0; i < size_; ++i) {
    data_[i] = other.data_[i]->clone();
  }
}

Array &Array::operator=(const Array &other) {
  if (this == &other) {
    return *this;
  }

  Array temp(other);

  std::swap(data_, temp.data_);
  std::swap(size_, temp.size_);
  std::swap(capacity_, temp.capacity_);

  return *this;
}

Array::Array(Array &&other) noexcept
    : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {

  other.data_ = nullptr;
  other.size_ = 0;
  other.capacity_ = 0;
}

Array &Array::operator=(Array &&other) noexcept {
  if (this == &other) {
    return *this;
  }

  for (size_t i = 0; i < size_; ++i) {
    delete data_[i];
  }

  delete[] data_;

  data_ = other.data_;
  size_ = other.size_;
  capacity_ = other.capacity_;

  other.data_ = nullptr;
  other.size_ = 0;
  other.capacity_ = 0;

  return *this;
}

void Array::push_back(Figure *fig) {
  if (size_ == capacity_) {
    resize((capacity_ == 0) ? 1 : capacity_ * 2);
  }

  data_[size_] = fig;
  size_++;
}

void Array::remove(size_t index) {
  if (index >= size_) {
    throw std::out_of_range("Index out of range");
  }

  delete data_[index];

  for (size_t i = index; i < size_ - 1; ++i) {
    data_[i] = data_[i + 1];
  }

  data_[size_ - 1] = nullptr;
  size_--;
}

Figure *Array::operator[](size_t index) const {
  if (index >= size_) {
    throw std::out_of_range("index out of range");
  }

  return data_[index];
}

size_t Array::size() const { return size_; }

void Array::resize(size_t new_capacity) {
  Figure **new_data = new Figure *[new_capacity];

  for (size_t i = 0; i < size_; ++i) {
    new_data[i] = data_[i];
  }

  delete[] data_;

  data_ = new_data;
  capacity_ = new_capacity;
}
