#include "ast-allocator.h"
#include <math.h>

namespace formulaEngine {

size_t AstAllocator::RoundAlign(size_t size, size_t alignment) {
  return std::ceil(1.0 * size / alignment) * alignment;
}

AstAllocator::~AstAllocator() {
  DeleteAll();
}

void* AstAllocator::Allocate(size_t size) {
  size = RoundAlign(size, kAlignment);
  uintptr_t result = position;

  if (size > top - position) {
    result = Expand(size);
  }

  position += size;

  return reinterpret_cast<void*>(result);
}

void AstAllocator::DeleteAll() {
    AstAllocatorNode* current = head;

    head = nullptr;

    while (current) {
      AstAllocatorNode* next = current->next();

      DeallocateNode(current);
      current = next;
    }

    position = 0;
    top = 0;
  }

uintptr_t AstAllocator::Expand(size_t size) {
  size_t oldSize = head ? head->total_size() : 0;
  static const size_t kNodeOverhead = sizeof(AstAllocatorNode);
  size_t newSize = size + (oldSize << 1) + kNodeOverhead;

  size_t necessarySize = kNodeOverhead + size;

  if (newSize < kMinimumExpandSize) {
    newSize = kMinimumExpandSize;
  } else if (newSize > kMaximumExpandSize) {
    newSize = kMaximumExpandSize > necessarySize ? kMaximumExpandSize : necessarySize;
  }

  // TODO add nullptr check
  AstAllocatorNode* newNode = AllocateNode(newSize);
  newNode->setNext(head);
  head = newNode;

  top = newNode->end();

  uintptr_t result = RoundAlign(newNode->begin(), kAlignment);
  position = result;

  return result;
}

AstAllocator::AstAllocatorNode* AstAllocator::AllocateNode (size_t size) {
  void* memory = malloc(size);
  return new (memory) AstAllocatorNode(size);
}

void AstAllocator::DeallocateNode (AstAllocatorNode* node) {
  free(node);
}
}