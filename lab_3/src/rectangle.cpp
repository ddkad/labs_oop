#include "rectangle.h"

Rectangle::Rectangle() {
  for (int i = 0; i < 4; ++i) {
    vertices_.push(Point(0, 0));
  }
}

Rectangle::Rectangle(Point p1, Point p2, Point p3, Point p4) {
  vertices_.push(p1);
  vertices_.push(p2);
  vertices_.push(p3);
  vertices_.push(p4);
}

double Rectangle::Area() const { return Figure::Area(); }

Point Rectangle::Center() const { return Figure::Center(); }

Rectangle::~Rectangle() {}