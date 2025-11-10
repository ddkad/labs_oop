#include <iostream>

#include "point.h"

Point::Point() : x(0), y(0) {}

Point::Point(double x_, double y_) : x(x_), y(y_) {}

bool operator==(const Point &p1, const Point &p2) {
  return p1.x == p2.x && p1.y == p2.y;
}

bool operator!=(const Point &p1, const Point &p2) { return !(p1 == p2); }

std::istream &operator>>(std::istream &is, Point &p) {
  is >> p.x >> p.y;
  return is;
}

std::ostream &operator<<(std::ostream &os, const Point &p) {
  os << '(' << p.x << ", " << p.y << ')';
  return os;
}
