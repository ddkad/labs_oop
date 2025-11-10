#include <gtest/gtest.h>
#include <point.h>
#include <sstream>

class PointTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(PointTest, DefaultConstructor) {
    Point<double> p;
    EXPECT_DOUBLE_EQ(p.x, 0.0);
    EXPECT_DOUBLE_EQ(p.y, 0.0);
}

TEST_F(PointTest, ParameterizedConstructor) {
    Point<double> p(3.5, 2.1);
    EXPECT_DOUBLE_EQ(p.x, 3.5);
    EXPECT_DOUBLE_EQ(p.y, 2.1);
}

TEST_F(PointTest, EqualityOperator) {
    Point<double> p1(1.0, 2.0);
    Point<double> p2(1.0, 2.0);
    Point<double> p3(1.0, 3.0);
    
    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 == p3);
}

TEST_F(PointTest, InequalityOperator) {
    Point<double> p1(1.0, 2.0);
    Point<double> p2(1.0, 3.0);
    Point<double> p3(1.0, 2.0);
    
    EXPECT_TRUE(p1 != p2);
    EXPECT_FALSE(p1 != p3);
}

TEST_F(PointTest, StreamOutput) {
    Point<double> p(1.5, 2.5);
    std::ostringstream oss;
    oss << p;
    
    std::string output = oss.str();
    EXPECT_TRUE(output.find("1.5") != std::string::npos);
    EXPECT_TRUE(output.find("2.5") != std::string::npos);
}

TEST_F(PointTest, StreamInput) {
    Point<double> p;
    std::istringstream iss("3.14 2.71");
    iss >> p;
    
    EXPECT_DOUBLE_EQ(p.x, 3.14);
    EXPECT_DOUBLE_EQ(p.y, 2.71);
}

TEST_F(PointTest, StreamInputInvalid) {
    Point<double> p;
    std::istringstream iss("invalid data");
    
    EXPECT_NO_THROW(iss >> p);
}

TEST_F(PointTest, NegativeCoordinates) {
    Point<double> p(-1.5, -2.5);
    EXPECT_DOUBLE_EQ(p.x, -1.5);
    EXPECT_DOUBLE_EQ(p.y, -2.5);
}

TEST_F(PointTest, ZeroCoordinates) {
    Point<double> p(0.0, 0.0);
    EXPECT_DOUBLE_EQ(p.x, 0.0);
    EXPECT_DOUBLE_EQ(p.y, 0.0);
}

TEST_F(PointTest, LargeCoordinates) {
    Point<double> p(1e10, -1e10);
    EXPECT_DOUBLE_EQ(p.x, 1e10);
    EXPECT_DOUBLE_EQ(p.y, -1e10);
}