#include <gtest/gtest.h>

#include "point.h"
#include "rectangle.h"
#include "square.h"
#include "vector_figures.h"
#include "vector_points.h"

TEST(VectorPointsTest, AddAndGetPoints) {
  VectorPoints vp;
  Point p1(1, 2);
  Point p2(3, 4);
  vp.push(p1);
  vp.push(p2);
  EXPECT_EQ(vp.len(), 2);
  EXPECT_TRUE(vp[0]) == p1);
  EXPECT_TRUE(vp[1] == p2);
}

TEST(VectorFigureTest, AddFigures) {
  VectorFigure vf;
  Square *square = new Square();
  Rectangle *rectangle = new Rectangle();
  vf.push(square);
  vf.push(rectangle);
  EXPECT_EQ(vf.len(), 2);
  EXPECT_TRUE(vf[0] == square);   
  EXPECT_TRUE(vf[1] == rectangle);
}
