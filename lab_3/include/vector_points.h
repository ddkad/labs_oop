#pragma once

#include "point.h"

class VectorPoints {
private:
  size_t size;
  size_t capacity;
  Point *v;
  void resize(size_t new_capacity);

public:
  VectorPoints();
  VectorPoints(size_t n);
  VectorPoints(const VectorPoints &other);
  VectorPoints(VectorPoints &&other) noexcept;
  ~VectorPoints();

  VectorPoints &operator=(const VectorPoints &other);
  VectorPoints &operator=(VectorPoints &&other) noexcept;

  void push(Point c);
  void pop();
  void clear();
  void set(size_t i, Point p);
  void resize(size_t newsize);
 
  Point &operator[](size_t index);
  const Point &operator[](size_t index) const;

   size_t len() const;
};

#endif
