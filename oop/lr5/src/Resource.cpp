#include "../includes/Resource.hpp"
#include <cstddef>
#include <iostream>
#include <memory_resource>
#include <new>
#include <stdexcept>

Resource::Resource()
    : allocated_blocks_internal_(std::pmr::new_delete_resource()) {}

Resource::~Resource() {
  for (const auto &block : allocated_blocks_internal_) {
    ::operator delete(block.ptr);
  }
}

void *Resource::do_allocate(size_t bytes, size_t alignment) {
  for (auto &block : allocated_blocks_internal_) {
    if (block.is_free && block.bytes >= bytes) {
      block.is_free = false;
      return block.ptr;
    }
  }

  void *p = ::operator new(bytes);

  allocated_blocks_internal_.push_back({p, bytes, false});

  return p;
}

void Resource::do_deallocate(void *p, size_t bytes, size_t alignment) {
  if (p == nullptr) {
    return;
  }

  for (auto &block : allocated_blocks_internal_) {
    if (block.ptr == p) {
      block.is_free = true;
      return;
    }
  }

  throw std::runtime_error("");
}

bool Resource::do_is_equal(
    const std::pmr::memory_resource &other) const noexcept {
  return this == &other;
}
