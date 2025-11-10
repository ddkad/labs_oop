template<class T>
Array<T>::Array() : current_size(0), current_capacity(1), elements(new T[current_capacity], array_deleter) {}

template<class T>
Array<T>::Array(size_t n) : current_size(n), current_capacity(n > 0 ? 2 * n : 1), elements(new T[current_capacity], array_deleter) {}

template<class T>
Array<T>::Array(size_t n, const T& elem) : current_size(n), current_capacity(n > 0 ? 2 * n : 1), elements(new T[current_capacity], array_deleter) {
    for (size_t i = 0; i < current_size; ++i) {
        elements[i] = elem;
    }
}

template<class T>
Array<T>::Array(const std::initializer_list<T>& lst) : current_size(0), current_capacity(1), elements(new T[current_capacity], array_deleter) {
    for (const T& elem : lst) { 
        push(elem); 
    }
}

template<class T>
Array<T>::Array(Array&& other) noexcept : current_size(other.current_size), current_capacity(other.current_capacity), elements(std::move(other.elements)) {
    other.current_size = 0;
    other.current_capacity = 0;
    other.elements = std::shared_ptr<T[]>(new T[1], array_deleter);
}

template<class T>
Array<T>::~Array() = default;


template<class T>
Array<T>& Array<T>::operator=(Array&& other) noexcept {
    if (this != &other) {
        current_size = other.current_size;
        current_capacity = other.current_capacity;
        elements = std::move(other.elements);
        
        other.current_size = 0;
        other.current_capacity = 0;
        other.elements = std::shared_ptr<T[]>(new T[1], array_deleter);
    }
    return *this;
}

template<class T>
void Array<T>::resize(size_t new_capacity) {
    auto new_elements = std::shared_ptr<T[]>(new T[new_capacity], array_deleter);
    for (size_t i = 0; i < current_size && i < new_capacity; ++i) {
        new_elements[i] = std::move(elements[i]);
    }
    elements = std::move(new_elements);
    current_capacity = new_capacity;

    if (current_size > current_capacity) {
        current_size = current_capacity;
    }
}

template<class T>
void Array<T>::push(const T& elem) {
    if (current_size >= current_capacity) {
        resize(2 * current_capacity);
    }
    elements[current_size++] = elem;
}

template<class T>
void Array<T>::push(T&& elem) {
    if (current_size >= current_capacity) {
        resize(2 * current_capacity);
    }
    elements[current_size++] = std::move(elem);
}

template<class T>
void Array<T>::pop() {
    if (current_size) {
        --current_size;
    }
}

template<class T>
void Array<T>::erase(size_t index) {
    if (index >= current_size) return;
    for (size_t i = index; i + 1 < current_size; ++i) {
        elements[i] = std::move(elements[i + 1]);
    }
    --current_size;
}

template<class T>
void Array<T>::clear() { 
    current_size = 0; 
}

template<class T>
T& Array<T>::operator[](size_t index) { 
    return elements[index]; 
}

template<class T>
const T& Array<T>::operator[](size_t index) const { 
    return elements[index]; 
}

template<class T>
size_t Array<T>::size() const { 
    return current_size; 
}

template<class T>
size_t Array<T>::capacity() const { 
    return current_capacity; 
}
