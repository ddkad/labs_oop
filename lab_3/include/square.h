#ifndef SQUARE_H
#define SQUARE_H

#include "figures.h"

class Square : public Figure {
public:
  Square();
  Square(Point p1, Point p2, Point p3, Point p4);
  ~Square();

  double Area() const override;
  Point Center() const override;
};
#endif