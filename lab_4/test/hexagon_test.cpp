#include <gtest/gtest.h>
#include <hexagon.h>
#include <point.h>
#include <sstream>
#include <stdexcept>

class HexagonTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(HexagonTest, DefaultConstructor) {
    Hexagon<double> hexagon;
    EXPECT_EQ(hexagon.vertex_count(), 6);
    EXPECT_NO_THROW(hexagon.area());
    EXPECT_NO_THROW(hexagon.center());
}

TEST_F(HexagonTest, ValidInitialization) {
    Hexagon<double> hexagon({
        Point<double>(1, 0), Point<double>(0.5, 0.866),
        Point<double>(-0.5, 0.866), Point<double>(-1, 0),
        Point<double>(-0.5, -0.866), Point<double>(0.5, -0.866)
    });
    EXPECT_EQ(hexagon.vertex_count(), 6);
}

TEST_F(HexagonTest, AreaCalculation) {
    Hexagon<double> hexagon({
        Point<double>(1, 0), Point<double>(0.5, 0.866),
        Point<double>(-0.5, 0.866), Point<double>(-1, 0),
        Point<double>(-0.5, -0.866), Point<double>(0.5, -0.866)
    });
    EXPECT_NEAR(hexagon.area(), 2.598076, 1e-3);
}

TEST_F(HexagonTest, CenterCalculation) {
    Hexagon<double> hexagon({
        Point<double>(1, 0), Point<double>(0.5, 0.866),
        Point<double>(-0.5, 0.866), Point<double>(-1, 0),
        Point<double>(-0.5, -0.866), Point<double>(0.5, -0.866)
    });
    Point<double> center = hexagon.center();
    EXPECT_NEAR(center.x, 0.0, 1e-9);
    EXPECT_NEAR(center.y, 0.0, 1e-9);
}

TEST_F(HexagonTest, Name) {
    Hexagon<double> hexagon;
    EXPECT_STREQ(hexagon.name(), "Hexagon");
}

TEST_F(HexagonTest, InputOutput) {
    Hexagon<double> hexagon;
    std::stringstream ss("1 0 0.5 0.866 -0.5 0.866 -1 0 -0.5 -0.866 0.5 -0.866");
    EXPECT_NO_THROW(ss >> hexagon);
    
    std::stringstream out;
    EXPECT_NO_THROW(out << hexagon);
    EXPECT_FALSE(out.str().empty());
}