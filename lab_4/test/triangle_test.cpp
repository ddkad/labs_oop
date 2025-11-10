#include <gtest/gtest.h>
#include <triangle.h>
#include <point.h>
#include <sstream>
#include <stdexcept>

class TriangleTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TriangleTest, DefaultConstructor) {
    Triangle<double> triangle;
    EXPECT_EQ(triangle.vertex_count(), 3);
    EXPECT_NO_THROW(triangle.area());
    EXPECT_NO_THROW(triangle.center());
}

TEST_F(TriangleTest, ValidInitialization) {
    Triangle<double> triangle({
        Point<double>(0, 0),
        Point<double>(4, 0), 
        Point<double>(0, 3)
    });
    EXPECT_EQ(triangle.vertex_count(), 3);
}


TEST_F(TriangleTest, AreaCalculation) {
    Triangle<double> triangle({
        Point<double>(0, 0),
        Point<double>(4, 0), 
        Point<double>(0, 3)
    });
    EXPECT_NEAR(triangle.area(), 6.0, 1e-9);
}

TEST_F(TriangleTest, AreaDegenerateTriangle) {
    Triangle<double> triangle({
        Point<double>(0, 0),
        Point<double>(2, 2), 
        Point<double>(4, 4)
    });
    EXPECT_NEAR(triangle.area(), 0.0, 1e-9);
}

TEST_F(TriangleTest, AreaNegativeCoordinates) {
    Triangle<double> triangle({
        Point<double>(-1, -1),
        Point<double>(-4, 0), 
        Point<double>(0, -3)
    });
    EXPECT_GE(triangle.area(), 0.0);
}

TEST_F(TriangleTest, CenterCalculation) {
    Triangle<double> triangle({
        Point<double>(0, 0),
        Point<double>(4, 0), 
        Point<double>(0, 3)
    });
    Point<double> center = triangle.center();
    EXPECT_NEAR(center.x, 4.0/3.0, 1e-9);
    EXPECT_NEAR(center.y, 1.0, 1e-9);
}

TEST_F(TriangleTest, Name) {
    Triangle<double> triangle;
    EXPECT_STREQ(triangle.name(), "Triangle");
}

TEST_F(TriangleTest, InputOutput) {
    Triangle<double> triangle;
    std::stringstream ss("0 0 4 0 0 3");
    EXPECT_NO_THROW(ss >> triangle);
    
    std::stringstream out;
    EXPECT_NO_THROW(out << triangle);
    EXPECT_FALSE(out.str().empty());
}

TEST_F(TriangleTest, VerySmallTriangle) {
    Triangle<double> triangle({
        Point<double>(0, 0),
        Point<double>(1e-10, 0), 
        Point<double>(0, 1e-10)
    });
    EXPECT_GE(triangle.area(), 0.0);
}

TEST_F(TriangleTest, LargeCoordinates) {
    Triangle<double> triangle({
        Point<double>(1e10, 1e10),
        Point<double>(1e10 + 1, 1e10), 
        Point<double>(1e10, 1e10 + 1)
    });
    EXPECT_NEAR(triangle.area(), 0.5, 1e-9);
}