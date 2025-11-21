#include <gtest/gtest.h>
#include <string>

#include "../include/queue.hpp"

struct ComplexType {
  int id;
  std::string name;
  double value;

  ComplexType(int i, const std::string &n, double v)
      : id(i), name(n), value(v) {}
  ComplexType(const ComplexType &) = default;
  ComplexType(ComplexType &&) = default;
  ComplexType &operator=(const ComplexType &) = default;
  ComplexType &operator=(ComplexType &&) = default;
};

TEST(QueueTest, BasicIntOperations) {
  custom::Queue<int> queue;

  EXPECT_TRUE(queue.IsEmpty());
  EXPECT_EQ(queue.GetSize(), 0);

  queue.Push(1);
  queue.Push(2);
  queue.Push(3);

  EXPECT_FALSE(queue.IsEmpty());
  EXPECT_EQ(queue.GetSize(), 3);
  EXPECT_EQ(queue.Front(), 1);

  queue.Pop();
  EXPECT_EQ(queue.Front(), 2);
  EXPECT_EQ(queue.GetSize(), 2);
}

TEST(QueueTest, ComplexTypeOperations) {
  custom::Queue<ComplexType> queue;

  queue.Push(ComplexType(1, "first", 1.1));
  queue.Emplace(2, "second", 2.2);
  queue.Emplace(3, "third", 3.3);

  EXPECT_EQ(queue.GetSize(), 3);
  EXPECT_EQ(queue.Front().id, 1);
  EXPECT_EQ(queue.Front().name, "first");

  queue.Pop();
  EXPECT_EQ(queue.Front().id, 2);
}

TEST(QueueTest, IteratorOperations) {
  custom::Queue<int> queue = {1, 2, 3, 4, 5};

  int sum = 0;
  int count = 0;
  for (auto it = queue.begin(); it != queue.end(); ++it) {
    sum += *it;
    ++count;
  }

  EXPECT_EQ(sum, 15);
  EXPECT_EQ(count, 5);

  const auto &const_queue = queue;
  sum = 0;
  for (auto it = const_queue.begin(); it != const_queue.end(); ++it) {
    sum += *it;
  }
  EXPECT_EQ(sum, 15);
}

TEST(QueueTest, MoveSemantics) {
  custom::Queue<std::string> queue1;
  queue1.Push("hello");
  queue1.Push("world");

  custom::Queue<std::string> queue2 = std::move(queue1);

  EXPECT_EQ(queue1.GetSize(), 0);
  EXPECT_EQ(queue2.GetSize(), 2);
  EXPECT_EQ(queue2.Front(), "hello");
}

TEST(QueueTest, CopySemantics) {
  custom::Queue<int> queue1 = {1, 2, 3};
  custom::Queue<int> queue2 = queue1;

  EXPECT_EQ(queue1.GetSize(), 3);
  EXPECT_EQ(queue2.GetSize(), 3);

  queue1.Pop();
  EXPECT_EQ(queue1.GetSize(), 2);
  EXPECT_EQ(queue2.GetSize(), 3);
}

TEST(QueueTest, EmptyQueueOperations) {
  custom::Queue<int> queue;

  EXPECT_THROW(queue.Front(), std::runtime_error);
  EXPECT_THROW(queue.Pop(), std::runtime_error);
}