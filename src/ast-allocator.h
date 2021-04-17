#pragma once

#include <stdlib.h>
#include <cstdint>
#include <new>

namespace formulaEngine {
// Efficiently allocates small chucks of memory for AstNodes
// Frees all the memory at once
class AstAllocator {
protected:
  class AstAllocatorNode {
  private:
    friend class AstAllocator;

    size_t size_;
    AstAllocatorNode* next_;

    explicit AstAllocatorNode(size_t size)
      : size_(size)
      {}
  public:
    AstAllocatorNode* next() const {
      return next_;
    }

    void setNext(AstAllocatorNode* next) {
      next_ = next;
    }

    size_t begin() const {
      return reinterpret_cast<size_t>(this) + sizeof(AstAllocatorNode);
    }

    size_t end() const{
      return reinterpret_cast<size_t>(this) + size_;
    }

    size_t capacity() const {
      return size_ - sizeof(AstAllocatorNode);
    }

    size_t total_size() const {
      return size_;
    }
  };

  AstAllocatorNode* head;
  uintptr_t position;
  uintptr_t top;
  // Todo add total size counter

  const size_t kAlignment = 8;
  const size_t kMinimumExpandSize = 1024;
  const size_t kMaximumExpandSize = 1024 * 8;

  size_t RoundAlign(size_t size, size_t alignment);

  void* Allocate(size_t size);
  uintptr_t Expand(size_t size);
  AstAllocatorNode* AllocateNode (size_t size);
  void DeallocateNode (AstAllocatorNode* node);
public:
  AstAllocator()
    : head(nullptr),
      position(0),
      top(0)
      {}

  ~AstAllocator();

  AstAllocator(const AstAllocator& other) = delete;
  AstAllocator& operator=(const AstAllocator& other) = delete;

  template <typename T, typename... Args>
  T* New(Args&&... args) {
    size_t size = RoundAlign(sizeof(T), kAlignment);
    void* memory = Allocate(size);
    return new (memory) T(std::forward<Args>(args)...);
  }

  void DeleteAll();
};
}
