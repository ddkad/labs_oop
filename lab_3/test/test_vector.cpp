#include "point.h"
#include "rectangle.h"
#include "square.h"
#include "vector_figures.h"
#include "vector_points.h"
#include <gtest/gtest.h>

TEST(VectorPointsTest, AddAndGetPoints) {
  VectorPoints vp;
  Point p1(1, 2);
  Point p2(3, 4);
  vp.push(p1);
  vp.push(p2);
  EXPECT_EQ(vp.len(), 2);
  EXPECT_TRUE(vp.get(0) == p1);
  EXPECT_TRUE(vp.get(1) == p2);
}

TEST(VectorFigureTest, AddFigures) {
  VectorFigure vf;
  Square *square = new Square();
  Rectangle *rectangle = new Rectangle();
  vf.push(square);
  vf.push(rectangle);
  EXPECT_EQ(vf.len(), 2);
}