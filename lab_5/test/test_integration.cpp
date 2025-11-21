#include <gtest/gtest.h>

#include "../include/dynamic_memory_resource.hpp"
#include "../include/queue.hpp"

struct ComplexType {
  int id;
  std::string name;
  double value;

  ComplexType(int i, const std::string &n, double v)
      : id(i), name(n), value(v) {}
};

TEST(IntegrationTest, QueueWithCustomMemoryResource) {
  memory::DynamicMemoryResource memory_resource;

  custom::pmr::Queue<int> queue(&memory_resource);

  for (int i = 0; i < 10; ++i) {
    queue.Push(i);
  }

  int expected = 0;
  for (auto value : queue) {
    EXPECT_EQ(value, expected);
    ++expected;
  }

  while (!queue.IsEmpty()) {
    queue.Pop();
  }

  for (int i = 0; i < 10; ++i) {
    queue.Push(i * 2);
  }

  expected = 0;
  for (auto value : queue) {
    EXPECT_EQ(value, expected);
    expected += 2;
  }
}

TEST(IntegrationTest, ComplexTypesWithMemoryResource) {
  memory::DynamicMemoryResource memory_resource;
  custom::pmr::Queue<ComplexType> queue(&memory_resource);

  queue.Emplace(1, "test1", 1.0);
  queue.Emplace(2, "test2", 2.0);
  queue.Emplace(3, "test3", 3.0);

  EXPECT_EQ(queue.GetSize(), 3);
  EXPECT_EQ(queue.Front().id, 1);

  int id_sum = 0;
  for (const auto &item : queue) {
    id_sum += item.id;
  }
  EXPECT_EQ(id_sum, 6);
}