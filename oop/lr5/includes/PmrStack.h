#include <cstddef>
#include <iostream>
#include <iterator>
#include <memory>
#include <memory_resource>
#include <stdexcept>
#include <utility>

template <typename T> class PmrStack {
private:
  struct Node {
    T data;
    Node *next;

    template <typename... Args>
    Node(std::pmr::polymorphic_allocator<T> alloc, Args &&...args)
        : data(std::forward<Args>(args)...), next(nullptr) {}
  };

  using Allocator = std::pmr::polymorphic_allocator<Node>;

  Node *top_ = nullptr;
  size_t size_ = 0;
  Allocator allocator_;

public:
  class Iterator {
  public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T *;
    using reference = T &;

  private:
    Node *current_ = nullptr;

  public:
    Iterator(Node *node = nullptr) : current_(node) {}

    reference operator*() const {
      if (!current_) {
        throw std::out_of_range("");
      }
      return current_->data;
    }

    pointer operator->() const { return &(operator*()); }

    Iterator &operator++() {
      if (current_) {
        current_ = current_->next;
      }
      return *this;
    }

    Iterator operator++(int) {
      Iterator temp = *this;
      ++(*this);
      return temp;
    }

    bool operator==(const Iterator &other) const {
      return current_ == other.current_;
    }

    bool operator!=(const Iterator &other) const { return !(*this == other); }
  };

  PmrStack(std::pmr::memory_resource *resource) : allocator_(resource) {}

  template <typename... Args> void push(Args &&...args) {
    Node *new_node_ptr = allocator_.allocate(1);

    try {
      std::__construct_at(new_node_ptr, allocator_,
                          std::forward<Args>(args)...);
    } catch (...) {
      allocator_.deallocate(new_node_ptr, 1);
      throw;
    }

    new_node_ptr->next = top_;
    top_ = new_node_ptr;
    size_++;
  }

  void pop() {
    if (!top_) {
      throw std::out_of_range("stack is epmty");
    }

    Node *old_top = top_;
    top_ = top_->next;

    std::destroy_at(&old_top->data);
    allocator_.deallocate(old_top, 1);
    size_--;
  }

  T &top() {
    if (!top_) {
      throw std::out_of_range("stack is empty");
    }

    return top_->data;
  }

  const T &top() const {
    if (!top_) {
      throw std::out_of_range("stack is empty");
    }

    return top_->data;
  }

  size_t size() const { return size_; }
  bool empty() const { return top_ == nullptr; }

  ~PmrStack() {
    while (!empty()) {
      pop();
    }
  }

  Iterator begin() { return Iterator(top_); }
  Iterator end() { return Iterator(nullptr); }
  const Iterator begin() const { return Iterator(top_); }
  const Iterator end() const { return Iterator(nullptr); }
};
