#pragma once

#include <iterator>
#include <memory>
#include <memory_resource>
#include <stdexcept>

namespace custom {

template <class T, class Allocator = std::allocator<T>> class Queue {
private:
  struct Node {
    T value;
    Node *next_node = nullptr;
    template <typename... Args>
    Node(Args &&...args)
        : value(std::forward<Args>(args)...), next_node(nullptr) {}
  };

  template <bool IsConst> class QueueIterator {
  private:
    using NodePointerType = std::conditional_t<IsConst, const Node *, Node *>;
    NodePointerType current_node_;

  public:
    QueueIterator(Node *node) : current_node_(node) {}
    QueueIterator() : QueueIterator(nullptr) {}

    using value_type = std::conditional_t<IsConst, const T, T>;
    using reference = value_type &;
    using pointer = value_type *;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;

    QueueIterator<IsConst> &operator++() noexcept;
    QueueIterator<IsConst> operator++(int) noexcept;
    reference operator*() const noexcept;
    pointer operator->() const noexcept;

    template <bool IsOtherConst>
    bool operator==(const QueueIterator<IsOtherConst> &other) const noexcept;

    template <bool IsOtherConst>
    bool operator!=(const QueueIterator<IsOtherConst> &other) const noexcept;

    operator QueueIterator<true>() const noexcept;
  };

public:
  using Iterator = QueueIterator<false>;
  using ConstIterator = QueueIterator<true>;

  Queue(const Allocator &allocator = Allocator());
  Queue(const std::initializer_list<T> &initializer_list,
        const Allocator &allocator = Allocator());
  template <typename InputIterator>
  Queue(InputIterator start, InputIterator end,
        const Allocator &allocator = Allocator());
  Queue(const Queue &other);
  Queue(Queue &&other) noexcept;
  Queue &operator=(const Queue &other);
  Queue &operator=(Queue &&other) noexcept;

  std::size_t GetSize() const noexcept;
  bool IsEmpty() const noexcept;

  void Clear();
  void Push(const T &value);
  void Push(T &&value);
  template <typename... Args> void Emplace(Args &&...args);
  T &Front();
  const T &Front() const;
  void Pop();

  Iterator begin() noexcept;
  Iterator end() noexcept;
  ConstIterator begin() const noexcept;
  ConstIterator end() const noexcept;
  ConstIterator cbegin() const noexcept;
  ConstIterator cend() const noexcept;

  ~Queue();

private:
  using NodeAllocatorType =
      typename std::allocator_traits<Allocator>::template rebind_alloc<Node>;
  using AllocatorTraits = std::allocator_traits<NodeAllocatorType>;

  NodeAllocatorType node_allocator_;
  Node *head_node_;
  Node *tail_node_;
  std::size_t size_;
};

namespace pmr {
template <class T>
using Queue = ::custom::Queue<T, std::pmr::polymorphic_allocator<T>>;
}

} 

#include "queue.ipp"