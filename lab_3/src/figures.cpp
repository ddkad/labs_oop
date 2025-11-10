#include <cmath>
#include <iostream>

#include "figures.h"

Figure::Figure() {}

Figure::~Figure() {}

double Figure::CalcArea() const {
  double area = 0.0;
  size_t n = vertices_.len();
  for (size_t i = 0; i < n; ++i) {
    const Point &p1 = vertices_[i]; 
    const Point &p2 = vertices_[(i + 1) % n];
    area += (p1.x * p2.y - p2.x * p1.y);
  }
  return std::abs(area) / 2.0;
}

Point Figure::CalcCenter() const {
  double center_x = 0.0, center_y = 0.0;
  size_t n = vertices_.len();
  for (size_t i = 0; i < n; ++i) {
    center_x += vertices_[i].x;
    center_y += vertices_[i].y;
  }
  return Point(center_x / n, center_y / n);
}

double Figure::Area() const { return CalcArea(); }

Point Figure::Center() const { return CalcCenter(); }

void Figure::ReadPoints(std::istream &is) {
  for (size_t i = 0; i < vertices_.len(); ++i) {
    Point p;
    is >> p.x >> p.y;
    vertices_.set(i, p);
  }
}

void Figure::PrintPoints(std::ostream &os) const {
  for (size_t i = 0; i < vertices_.len(); ++i) {
    const Point &p = vertices_[i];
    os << p;
    if (i < vertices_.len() - 1) {
      os << " ";
    }
  }
}

std::istream &operator>>(std::istream &is, Figure &figure) {
  figure.ReadPoints(is);
  return is;
}

std::ostream &operator<<(std::ostream &os, const Figure &figure) {
  figure.PrintPoints(os);
  return os;
}

bool operator==(const Figure &f1, const Figure &f2) {
  if (f1.vertices_.len() != f2.vertices_.len()) {
    return false;
  }
  for (size_t i = 0; i < f1.vertices_.len(); ++i) {
    if (f1.vertices_[i] != f2.vertices_[i]) {
      return false;
    }
  }
  return true;
}

bool operator!=(const Figure &f1, const Figure &f2) { return !(f1 == f2); }
