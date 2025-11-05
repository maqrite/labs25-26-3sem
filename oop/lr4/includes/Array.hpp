#pragma once

#include "Figure.hpp"
#include <new>
#include <stdexcept>
#include <utility>

template <class T> class Array {
public:
  Array() : data_(nullptr), size_(0), capacity_(0) {}

  ~Array() { delete[] data_; }

  Array(const Array &other) : size_(other.size_), capacity_(other.capacity_) {

    data_ = (capacity_ > 0) ? new T[capacity_] : nullptr;

    try {
      for (size_t i = 0; i < size_; ++i) {
        data_[i] = other.data_[i];
      }
    } catch (...) {
      delete[] data_;
      throw;
    }
  }

  Array &operator=(const Array &other) {
    if (this == &other) {
      return *this;
    }

    Array temp(other);

    swap(temp);
    return *this;
  }

  Array(Array &&other) noexcept
      : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
  }

  Array &operator=(Array &&other) noexcept {
    if (this == &other) {
      return *this;
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

  void push_back(const T &fig) {
    if (size_ == capacity_) {
      resize((capacity_ == 0) ? 1 : capacity_ * 2);
    }

    data_[size_] = fig;
    size_++;
  }

  void push_back(T &&fig) {
    if (size_ == capacity_) {
      resize((capacity_ == 0) ? 1 : capacity_ * 2);
    }
    data_[size_] = std::move(fig);
    size_++;
  }

  void remove(size_t index) {
    if (index >= size_) {
      throw std::out_of_range("Index out of range");
    }

    for (size_t i = index; i < size_ - 1; ++i) {
      data_[i] = std::move(data_[i + 1]);
    }

    size_--;
  }

  T &operator[](size_t index) {
    if (index >= size_) {
      throw std::out_of_range("index out of range");
    }
    return data_[index];
  }

  const T &operator[](size_t index) const {
    if (index >= size_) {
      throw std::out_of_range("index out of range");
    }
    return data_[index];
  }

  size_t size() const { return size_; }

  size_t capacity() const { return capacity_; }

private:
  T *data_;
  size_t size_;
  size_t capacity_;

  void resize(size_t new_capacity) {
    T *new_data = new T[new_capacity];

    try {
      for (size_t i = 0; i < size_; ++i) {
        new_data[i] = std::move(data_[i]);
      }
    } catch (...) {
      delete[] new_data;
      throw;
    }

    delete[] data_;

    data_ = new_data;
    capacity_ = new_capacity;
  }

  void swap(Array &other) noexcept {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
  }
};
