#include "vector_figures.h"
#include "figures.h"

VectorFigure::VectorFigure()
    : size(0), capacity(1), v(new Figure *[capacity]) {}

VectorFigure::VectorFigure(const VectorFigure &other)
    : size(other.size), capacity(other.capacity), v(new Figure *[capacity]) {
  for (size_t i = 0; i < size; ++i) {
    v[i] = other.v[i];
  }
}

VectorFigure::VectorFigure(VectorFigure &&other) noexcept
    : size(other.size), capacity(other.capacity), v(other.v) {
  other.size = 0;
  other.capacity = 0;
  other.v = nullptr;
}

VectorFigure::~VectorFigure() {
  for (size_t i = 0; i < size; ++i) {
    delete v[i];
  }
  delete[] v;
}

void VectorFigure::resize(size_t newsize) {
  capacity = newsize;
  Figure **t = new Figure *[capacity];
  for (size_t i = 0; i < size; ++i) {
    t[i] = v[i];
  }
  delete[] v;
  v = t;
}

void VectorFigure::push(Figure *c) {
  if (size >= capacity) {
    resize(2 * capacity);
  }
  v[size++] = c;
}

void VectorFigure::pop() {
  if (size) {
    delete v[size - 1];
  }
}

void VectorFigure::erase(size_t ind) {
  if (ind < size) {
    delete v[ind];
    for (size_t i = ind; i < size - 1; ++i) {
      v[i] = v[i + 1];
    }
    --size;
  }
}

Figure *VectorFigure::get(size_t i) { return v[i]; }

size_t VectorFigure::len() { return size; }

void VectorFigure::clear() {
  for (size_t i = 0; i < size; ++i) {
    delete v[i];
  }
  size = 0;
  capacity = 1;
  delete[] v;
  v = new Figure *[capacity];
}