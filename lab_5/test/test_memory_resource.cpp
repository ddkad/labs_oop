#include <gtest/gtest.h>

#include "../include/dynamic_memory_resource.hpp"

TEST(DynamicMemoryResourceTest, BasicAllocationDeallocation) {
  memory::DynamicMemoryResource resource;

  void *block1 = resource.allocate(64, 8);
  ASSERT_NE(block1, nullptr);
  resource.deallocate(block1, 64, 8);

  void *block2 = resource.allocate(64, 8);
  ASSERT_NE(block2, nullptr);
  resource.deallocate(block2, 64, 8);
}

TEST(DynamicMemoryResourceTest, MemoryReuse) {
  memory::DynamicMemoryResource resource;

  void *original_block = resource.allocate(128, 16);
  ASSERT_NE(original_block, nullptr);
  resource.deallocate(original_block, 128, 16);

  void *reused_block = resource.allocate(128, 16);
  ASSERT_NE(reused_block, nullptr);
  ASSERT_EQ(original_block, reused_block);
  resource.deallocate(reused_block, 128, 16);
}

TEST(DynamicMemoryResourceTest, DifferentSizesNoReuse) {
  memory::DynamicMemoryResource resource;

  void *small_block = resource.allocate(64, 8);
  ASSERT_NE(small_block, nullptr);
  resource.deallocate(small_block, 64, 8);

  void *large_block = resource.allocate(128, 8);
  ASSERT_NE(large_block, nullptr);
  ASSERT_NE(small_block, large_block);
  resource.deallocate(large_block, 128, 8);
}

TEST(DynamicMemoryResourceTest, ZeroSizeAllocation) {
  memory::DynamicMemoryResource resource;

  void *zero_block = resource.allocate(0, 8);
  ASSERT_EQ(zero_block, nullptr);
}

TEST(DynamicMemoryResourceTest, DifferentAlignments) {
  memory::DynamicMemoryResource resource;

  std::vector<size_t> alignments = {1, 2, 4, 8, 16, 32, 64, 128};

  for (size_t alignment : alignments) {
    void *block = resource.allocate(64, alignment);
    ASSERT_NE(block, nullptr)
        << "Failed to allocate with alignment " << alignment;
    resource.deallocate(block, 64, alignment);
  }

  void *block1 = resource.allocate(100, 16);
  ASSERT_NE(block1, nullptr);
  resource.deallocate(block1, 100, 16);

  void *block2 = resource.allocate(100, 8);
  ASSERT_NE(block2, nullptr);
  void *block3 = resource.allocate(100, 32);
  ASSERT_NE(block3, nullptr);
  ASSERT_NE(block2, block3);

  resource.deallocate(block2, 100, 8);
  resource.deallocate(block3, 100, 32);
}