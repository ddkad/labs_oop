#ifndef VECTOR_POINTS_H
#define VECTOR_POINTS_H

#include "point.h"

class VectorPoints {
private:
  size_t size;
  size_t capacity;
  Point *v;

public:
  VectorPoints();
  VectorPoints(size_t n);
  VectorPoints(const VectorPoints &other);
  VectorPoints(VectorPoints &&other) noexcept;
  ~VectorPoints();

  void push(Point c);
  void pop();
  void clear();
  void set(size_t i, Point p);
  void resize(size_t newsize);

  Point get(size_t i) const;
  size_t len() const;
};

#endif