#pragma once

#include <iostream>

struct Point {
  double x, y;

  Point();
  Point(double x, double y);

  bool operator==(const Point &other) const;
  bool operator!=(const Point &other) const;

  friend std::istream &operator>>(std::istream &is, Point &p);
  friend std::ostream &operator<<(std::ostream &os, const Point &p);
};
