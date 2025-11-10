#include <gtest/gtest.h>

#include "point.h"

TEST(PointTest, DefaultConstructor) {
  Point p;
  EXPECT_EQ(p.x, 0);
  EXPECT_EQ(p.y, 0);
}

TEST(PointTest, ParameterizedConstructor) {
  Point p(3, 4);
  EXPECT_EQ(p.x, 3);
  EXPECT_EQ(p.y, 4);
}

TEST(PointTest, EqualityOperator) {
  Point p1(1, 2);
  Point p2(1, 2);
  Point p3(2, 2);
  EXPECT_TRUE(p1 == p2);
  EXPECT_FALSE(p1 == p3);
}
