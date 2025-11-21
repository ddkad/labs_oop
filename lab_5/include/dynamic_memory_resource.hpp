#pragma once

#include <memory>
#include <memory_resource>
#include <vector>

namespace memory {

class DynamicMemoryResource : public std::pmr::memory_resource {
public:
  DynamicMemoryResource();
  virtual ~DynamicMemoryResource() noexcept final;

private:
  struct MemoryBlock {
    void *pointer;
    std::size_t size;
    std::size_t alignment;
  };

  virtual void *do_allocate(std::size_t size, std::size_t alignment) final;
  virtual void do_deallocate(void *pointer, std::size_t size,
                             std::size_t alignment) final;
  virtual bool
  do_is_equal(const std::pmr::memory_resource &other) const noexcept final;

  std::vector<MemoryBlock> allocated_blocks_;
  std::vector<MemoryBlock> deallocated_blocks_;
};
} 