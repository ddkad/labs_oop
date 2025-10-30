#ifndef VECTOR_FIGURES_H
#define VECTOR_FIGURES_H

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

  Figure *get(size_t index);

  size_t len();

  double totalArea() const;
};

#endif