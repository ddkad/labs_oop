#pragma once

#include "figures.h"

class VectorFigure {
private:
  size_t size;
  size_t capacity;
  Figure **v;

  void resize(size_t new_capacity);

public:
  VectorFigure();
  VectorFigure(const VectorFigure &other);
  VectorFigure(VectorFigure &&other) noexcept;
  ~VectorFigure();

  VectorFigure &operator=(const VectorFigure &other);
  VectorFigure &operator=(VectorFigure &&other) noexcept;

  void push(Figure *figure);
  void pop();
  void clear();
  void erase(size_t index);

  Figure *operator[](size_t index);
  const Figure *operator[](size_t index) const;

  size_t len();

  double totalArea() const;
};

#endif
