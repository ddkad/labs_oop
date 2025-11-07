#pragma once
#include <memory>
#include <algorithm>
#include <initializer_list>
#include <concepts>

template<class T> 
class Array {
    size_t current_size = 0;
    size_t current_capacity = 0;
    std::shared_ptr<T[]> elements;

public:
    Array();
    Array(size_t);
    Array(size_t, const T&);
    Array(const std::initializer_list<T>&);
    // Array(const Array&);
    Array(Array&&) noexcept;
    ~Array();

    void resize(size_t new_capacity);
    void push(const T&);
    void push(T&&);
    void pop();
    void erase(size_t);
    void clear();
    
    size_t size() const;
    size_t capacity() const;
    T& operator[](size_t);
    const T& operator[](size_t) const;
    // Array& operator=(const Array&);
    Array& operator=(Array&&) noexcept;
};

#include "array.ipp"