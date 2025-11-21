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

    QueueIterator<IsConst> &operator++() noexcept {
      if (current_node_) {
        current_node_ = current_node_->next_node;
      }
      return *this;
    }

    QueueIterator<IsConst> operator++(int) noexcept {
      QueueIterator<IsConst> temp = *this;
      ++(*this);
      return temp;
    }

    reference operator*() const noexcept { return current_node_->value; }

    pointer operator->() const noexcept { return &current_node_->value; }

    template <bool IsOtherConst>
    bool operator==(const QueueIterator<IsOtherConst> &other) const noexcept {
      return current_node_ == other.current_node_;
    }

    template <bool IsOtherConst>
    bool operator!=(const QueueIterator<IsOtherConst> &other) const noexcept {
      return current_node_ != other.current_node_;
    }

    operator QueueIterator<true>() const noexcept {
      return QueueIterator<true>(current_node_);
    }
  };

public:
  using Iterator = QueueIterator<false>;
  using ConstIterator = QueueIterator<true>;

  Queue(const Allocator &allocator = Allocator())
      : node_allocator_(allocator), head_node_(nullptr), tail_node_(nullptr),
        size_(0) {}

  Queue(const std::initializer_list<T> &initializer_list,
        const Allocator &allocator = Allocator())
      : Queue(allocator) {
    for (const auto &item : initializer_list) {
      Push(item);
    }
  }

  template <typename InputIterator>
  Queue(InputIterator start, InputIterator end,
        const Allocator &allocator = Allocator())
      : node_allocator_(allocator), head_node_(nullptr), tail_node_(nullptr),
        size_(0) {
    for (; start != end; ++start) {
      Push(*start);
    }
  }

  Queue(const Queue &other)
      : node_allocator_(AllocatorTraits::select_on_container_copy_construction(
            other.node_allocator_)),
        head_node_(nullptr), tail_node_(nullptr), size_(0) {
    for (const auto &item : other) {
      Push(item);
    }
  }

  Queue(Queue &&other) noexcept
      : node_allocator_(std::move(other.node_allocator_)),
        head_node_(other.head_node_), tail_node_(other.tail_node_),
        size_(other.size_) {
    other.head_node_ = nullptr;
    other.tail_node_ = nullptr;
    other.size_ = 0;
  }

  Queue &operator=(const Queue &other) {
    if (this != &other) {
      Clear();
      if constexpr (AllocatorTraits::propagate_on_container_copy_assignment::
                        value) {
        node_allocator_ = other.node_allocator_;
      }
      for (const auto &item : other) {
        Push(item);
      }
    }
    return *this;
  }

  Queue &operator=(Queue &&other) noexcept {
    if (this != &other) {
      Clear();

      if (node_allocator_ == other.node_allocator_) {
        head_node_ = other.head_node_;
        tail_node_ = other.tail_node_;
        size_ = other.size_;
        other.head_node_ = nullptr;
        other.tail_node_ = nullptr;
        other.size_ = 0;
      } else if constexpr (AllocatorTraits::
                               propagate_on_container_move_assignment::value) {
        node_allocator_ = std::move(other.node_allocator_);
        head_node_ = other.head_node_;
        tail_node_ = other.tail_node_;
        size_ = other.size_;
        other.head_node_ = nullptr;
        other.tail_node_ = nullptr;
        other.size_ = 0;
      } else {
        for (auto &item : other) {
          Push(std::move(item));
        }
        other.Clear();
      }
    }
    return *this;
  }

  std::size_t GetSize() const noexcept { return size_; };
  bool IsEmpty() const noexcept { return size_ == 0; };

  void Clear() {
    while (head_node_) {
      Node *next_node = head_node_->next_node;
      AllocatorTraits::destroy(node_allocator_, head_node_);
      AllocatorTraits::deallocate(node_allocator_, head_node_, 1);
      head_node_ = next_node;
    }
    tail_node_ = nullptr;
    size_ = 0;
  }

  void Push(const T &value) { Emplace(value); }

  void Push(T &&value) { Emplace(std::move(value)); }

  template <typename... Args> void Emplace(Args &&...args) {
    Node *new_node = AllocatorTraits::allocate(node_allocator_, 1);
    try {
      AllocatorTraits::construct(node_allocator_, new_node,
                                 std::forward<Args>(args)...);
    } catch (...) {
      AllocatorTraits::deallocate(node_allocator_, new_node, 1);
      throw;
    }

    new_node->next_node = nullptr;

    if (tail_node_) {
      tail_node_->next_node = new_node;
      tail_node_ = new_node;
    } else {
      head_node_ = new_node;
      tail_node_ = new_node;
    }
    ++size_;
  }

  T &Front() {
    if (!head_node_) {
      throw std::runtime_error("Queue is empty");
    }
    return head_node_->value;
  }

  const T &Front() const {
    if (!head_node_) {
      throw std::runtime_error("Queue is empty");
    }
    return head_node_->value;
  }

  void Pop() {
    if (!head_node_) {
      throw std::runtime_error("Queue is empty");
    }

    Node *node_to_remove = head_node_;
    head_node_ = head_node_->next_node;

    if (!head_node_) {
      tail_node_ = nullptr;
    }

    AllocatorTraits::destroy(node_allocator_, node_to_remove);
    AllocatorTraits::deallocate(node_allocator_, node_to_remove, 1);
    --size_;
  }

  Iterator begin() noexcept { return Iterator(head_node_); }
  Iterator end() noexcept { return Iterator(); }

  ConstIterator begin() const noexcept { return ConstIterator(head_node_); }
  ConstIterator end() const noexcept { return ConstIterator(); }

  ConstIterator cbegin() const noexcept { return ConstIterator(head_node_); }
  ConstIterator cend() const noexcept { return ConstIterator(); }

  ~Queue() { Clear(); }

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