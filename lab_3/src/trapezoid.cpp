#include "trapezoid.h"

Trapezoid::Trapezoid() {
  for (int i = 0; i < 4; ++i) {
    vertices_.push(Point(0, 0));
  }
}

Trapezoid::Trapezoid(Point p1, Point p2, Point p3, Point p4) {
  vertices_.push(p1);
  vertices_.push(p2);
  vertices_.push(p3);
  vertices_.push(p4);
}

double Trapezoid::Area() const { return Figure::Area(); }

Point Trapezoid::Center() const { return Figure::Center(); }

Trapezoid::~Trapezoid() {}