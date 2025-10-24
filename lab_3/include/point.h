#ifndef POINT_H
#define POINT_H

#include <iostream>

struct Point {
  double x, y;

  Point();
  Point(double x, double y);

  friend bool operator==(const Point &p1, const Point &p2);
  friend bool operator!=(const Point &p1, const Point &p2);

  friend std::istream &operator>>(std::istream &is, Point &p);
  friend std::ostream &operator<<(std::ostream &os, const Point &p);
};

#endif