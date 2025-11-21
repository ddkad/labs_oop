#include <iostream>

#include "dynamic_memory_resource.hpp"

namespace memory {

DynamicMemoryResource::DynamicMemoryResource() = default;

void *DynamicMemoryResource::do_allocate(std::size_t size,
                                         std::size_t alignment) {
  if (size == 0) {
    return nullptr;
  }

  if (alignment == 0 || (alignment & (alignment - 1)) != 0) {
    throw std::bad_alloc();
  }

  auto it = std::find_if(deallocated_blocks_.begin(), deallocated_blocks_.end(),
        [size, alignment](const MemoryBlock& block) {
            return block.size >= size && block.alignment >= alignment;
        });
    
    if (it != deallocated_blocks_.end()) {
        void* ptr = it->pointer;
        allocated_blocks_.push_back(*it);
        deallocated_blocks_.erase(it);
        return ptr;
    }

    void* new_ptr = ::operator new(size, std::align_val_t(alignment));
    allocated_blocks_.push_back({new_ptr, size, alignment});
    return new_ptr;
}

void DynamicMemoryResource::do_deallocate(void *pointer, std::size_t size,
                                          std::size_t alignment) {
  (void)size;
  (void)alignment;
  for (auto iterator = allocated_blocks_.begin();
       iterator != allocated_blocks_.end(); ++iterator) {
    if (iterator->pointer == pointer) {
      deallocated_blocks_.push_back(*iterator);
      allocated_blocks_.erase(iterator);
      return;
    }
  }
}

bool DynamicMemoryResource::do_is_equal(
    const std::pmr::memory_resource &other) const noexcept {
  return this == &other;
}

DynamicMemoryResource::~DynamicMemoryResource() noexcept {
  for (auto &block : allocated_blocks_) {
    ::operator delete(block.pointer, std::align_val_t(block.alignment));
  }

  for (auto &block : deallocated_blocks_) {
    ::operator delete(block.pointer, std::align_val_t(block.alignment));
  }
}
} 