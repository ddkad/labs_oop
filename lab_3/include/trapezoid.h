#ifndef TRAPEZOID_H
#define TRAPEZOID_H

#include "figures.h"

class Trapezoid : public Figure {
public:
  Trapezoid();
  Trapezoid(Point p1, Point p2, Point p3, Point p4);
  ~Trapezoid();

  double Area() const override;
  Point Center() const override;
};
#endif