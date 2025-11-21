template <class T, class Allocator>
template <bool IsConst>
typename custom::Queue<T, Allocator>::template QueueIterator<IsConst> & 
custom::Queue<T, Allocator>::QueueIterator<IsConst>::operator++() noexcept {
  if (current_node_) {
    current_node_ = current_node_->next_node;
  }
  return *this;
}

template <class T, class Allocator>
template <bool IsConst>
typename custom::Queue<T, Allocator>::template QueueIterator<IsConst> 
custom::Queue<T, Allocator>::QueueIterator<IsConst>::operator++(int) noexcept {
  QueueIterator<IsConst> temp = *this;
  ++(*this);
  return temp;
}

template <class T, class Allocator>
template <bool IsConst>
typename custom::Queue<T, Allocator>::template QueueIterator<IsConst>::reference 
custom::Queue<T, Allocator>::QueueIterator<IsConst>::operator*() const noexcept { 
  return current_node_->value; 
}

template <class T, class Allocator>
template <bool IsConst>
typename custom::Queue<T, Allocator>::template QueueIterator<IsConst>::pointer 
custom::Queue<T, Allocator>::QueueIterator<IsConst>::operator->() const noexcept { 
  return &current_node_->value; 
}

template <class T, class Allocator>
template <bool IsConst>
template <bool IsOtherConst>
bool custom::Queue<T, Allocator>::QueueIterator<IsConst>::operator==(const QueueIterator<IsOtherConst> &other) const noexcept {
  return current_node_ == other.current_node_;
}

template <class T, class Allocator>
template <bool IsConst>
template <bool IsOtherConst>
bool custom::Queue<T, Allocator>::QueueIterator<IsConst>::operator!=(const QueueIterator<IsOtherConst> &other) const noexcept {
  return current_node_ != other.current_node_;
}

template <class T, class Allocator>
template <bool IsConst>
custom::Queue<T, Allocator>::QueueIterator<IsConst>::operator QueueIterator<true>() const noexcept {
  return QueueIterator<true>(current_node_);
}


template <class T, class Allocator>
custom::Queue<T, Allocator>::Queue(const Allocator &allocator)
    : node_allocator_(allocator), head_node_(nullptr), tail_node_(nullptr),
      size_(0) {}

template <class T, class Allocator>
custom::Queue<T, Allocator>::Queue(const std::initializer_list<T> &initializer_list,
      const Allocator &allocator)
    : Queue(allocator) {
  for (const auto &item : initializer_list) {
    Push(item);
  }
}

template <class T, class Allocator>
template <typename InputIterator>
custom::Queue<T, Allocator>::Queue(InputIterator start, InputIterator end,
      const Allocator &allocator)
    : node_allocator_(allocator), head_node_(nullptr), tail_node_(nullptr),
      size_(0) {
  for (; start != end; ++start) {
    Push(*start);
  }
}

template <class T, class Allocator>
custom::Queue<T, Allocator>::Queue(const Queue &other)
    : node_allocator_(AllocatorTraits::select_on_container_copy_construction(
          other.node_allocator_)),
      head_node_(nullptr), tail_node_(nullptr), size_(0) {
  for (const auto &item : other) {
    Push(item);
  }
}

template <class T, class Allocator>
custom::Queue<T, Allocator>::Queue(Queue &&other) noexcept
    : node_allocator_(std::move(other.node_allocator_)),
      head_node_(other.head_node_), tail_node_(other.tail_node_),
      size_(other.size_) {
  other.head_node_ = nullptr;
  other.tail_node_ = nullptr;
  other.size_ = 0;
}

template <class T, class Allocator>
custom::Queue<T, Allocator> &custom::Queue<T, Allocator>::operator=(const Queue &other) {
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

template <class T, class Allocator>
custom::Queue<T, Allocator> &custom::Queue<T, Allocator>::operator=(Queue &&other) noexcept {
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

template <class T, class Allocator>
std::size_t custom::Queue<T, Allocator>::GetSize() const noexcept { return size_; }

template <class T, class Allocator>
bool custom::Queue<T, Allocator>::IsEmpty() const noexcept { return size_ == 0; }

template <class T, class Allocator>
void custom::Queue<T, Allocator>::Clear() {
  while (head_node_) {
    Node *next_node = head_node_->next_node;
    AllocatorTraits::destroy(node_allocator_, head_node_);
    AllocatorTraits::deallocate(node_allocator_, head_node_, 1);
    head_node_ = next_node;
  }
  tail_node_ = nullptr;
  size_ = 0;
}

template <class T, class Allocator>
void custom::Queue<T, Allocator>::Push(const T &value) { Emplace(value); }

template <class T, class Allocator>
void custom::Queue<T, Allocator>::Push(T &&value) { Emplace(std::move(value)); }

template <class T, class Allocator>
template <typename... Args> 
void custom::Queue<T, Allocator>::Emplace(Args &&...args) {
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

template <class T, class Allocator>
T &custom::Queue<T, Allocator>::Front() {
  if (!head_node_) {
    throw std::runtime_error("Queue is empty");
  }
  return head_node_->value;
}

template <class T, class Allocator>
const T &custom::Queue<T, Allocator>::Front() const {
  if (!head_node_) {
    throw std::runtime_error("Queue is empty");
  }
  return head_node_->value;
}

template <class T, class Allocator>
void custom::Queue<T, Allocator>::Pop() {
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

template <class T, class Allocator>
typename custom::Queue<T, Allocator>::Iterator custom::Queue<T, Allocator>::begin() noexcept { 
  return Iterator(head_node_); 
}

template <class T, class Allocator>
typename custom::Queue<T, Allocator>::Iterator custom::Queue<T, Allocator>::end() noexcept { 
  return Iterator(); 
}

template <class T, class Allocator>
typename custom::Queue<T, Allocator>::ConstIterator custom::Queue<T, Allocator>::begin() const noexcept { 
  return ConstIterator(head_node_); 
}

template <class T, class Allocator>
typename custom::Queue<T, Allocator>::ConstIterator custom::Queue<T, Allocator>::end() const noexcept { 
  return ConstIterator(); 
}

template <class T, class Allocator>
typename custom::Queue<T, Allocator>::ConstIterator custom::Queue<T, Allocator>::cbegin() const noexcept { 
  return ConstIterator(head_node_); 
}

template <class T, class Allocator>
typename custom::Queue<T, Allocator>::ConstIterator custom::Queue<T, Allocator>::cend() const noexcept { 
  return ConstIterator(); 
}

template <class T, class Allocator>
custom::Queue<T, Allocator>::~Queue() { Clear(); }