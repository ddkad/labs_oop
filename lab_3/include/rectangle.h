#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "figures.h"

class Rectangle : public Figure {
public:
  Rectangle();
  Rectangle(Point p1, Point p2, Point p3, Point p4);
  ~Rectangle();

  double Area() const override;
  Point Center() const override;
};
#endif