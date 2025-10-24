#include "point.h"
#include "rectangle.h"
#include "square.h"
#include "trapezoid.h"
#include <gtest/gtest.h>

TEST(SquareTest, AreaCalculation) {
  Point p1(0, 0);
  Point p2(2, 0);
  Point p3(2, 2);
  Point p4(0, 2);
  Square square(p1, p2, p3, p4);
  EXPECT_NEAR(static_cast<double>(square.Area()), 4.0, 1e-10);
}

TEST(RectangleTest, AreaCalculation) {
  Point p1(0, 0);
  Point p2(4, 0);
  Point p3(4, 2);
  Point p4(0, 2);
  Rectangle rectangle(p1, p2, p3, p4);
  EXPECT_NEAR(static_cast<double>(rectangle.Area()), 8.0, 1e-10);
}

TEST(TrapezoidTest, AreaCalculation) {
  Point p1(0, 0);
  Point p2(4, 0);
  Point p3(3, 2);
  Point p4(1, 2);
  Trapezoid trapezoid(p1, p2, p3, p4);
  EXPECT_NEAR(static_cast<double>(trapezoid.Area()), 6.0, 1e-10);
}