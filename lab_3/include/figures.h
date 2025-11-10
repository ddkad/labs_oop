#pragma once

#include <iostream>

#include "vector_points.h"


class Figure {
public:
  Figure();
  virtual ~Figure();

  void ReadPoints(std::istream &is);
  void PrintPoints(std::ostream &os) const;

  virtual double Area() const;
  virtual Point Center() const;

  friend bool operator==(const Figure &f1, const Figure &f2);
  friend bool operator!=(const Figure &f1, const Figure &f2);

  operator double() const { return Area(); }

protected:
  VectorPoints vertices_;

  double CalcArea() const;
  Point CalcCenter() const;
};

std::istream &operator>>(std::istream &is, Figure &figure);
std::ostream &operator<<(std::ostream &os, const Figure &figure);
