#include <gtest/gtest.h>
#include <octagon.h>
#include <point.h>
#include <sstream>
#include <stdexcept>

class OctagonTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(OctagonTest, DefaultConstructor) {
    Octagon<double> octagon;
    EXPECT_EQ(octagon.vertex_count(), 8);
    EXPECT_NO_THROW(octagon.area());
    EXPECT_NO_THROW(octagon.center());
}

TEST_F(OctagonTest, ValidInitialization) {
    Octagon<double> octagon({
        Point<double>(1, 0), Point<double>(0.707, 0.707),
        Point<double>(0, 1), Point<double>(-0.707, 0.707),
        Point<double>(-1, 0), Point<double>(-0.707, -0.707),
        Point<double>(0, -1), Point<double>(0.707, -0.707)
    });
    EXPECT_EQ(octagon.vertex_count(), 8);
}

TEST_F(OctagonTest, AreaCalculation) {
    Octagon<double> octagon({
        Point<double>(1, 0), Point<double>(0.707, 0.707),
        Point<double>(0, 1), Point<double>(-0.707, 0.707),
        Point<double>(-1, 0), Point<double>(-0.707, -0.707),
        Point<double>(0, -1), Point<double>(0.707, -0.707)
    });
    EXPECT_NEAR(octagon.area(), 2.828427, 1e-3);
}

TEST_F(OctagonTest, CenterCalculation) {
    Octagon<double> octagon({
        Point<double>(1, 0), Point<double>(0.707, 0.707),
        Point<double>(0, 1), Point<double>(-0.707, 0.707),
        Point<double>(-1, 0), Point<double>(-0.707, -0.707),
        Point<double>(0, -1), Point<double>(0.707, -0.707)
    });
    Point<double> center = octagon.center();
    EXPECT_NEAR(center.x, 0.0, 1e-9);
    EXPECT_NEAR(center.y, 0.0, 1e-9);
}

TEST_F(OctagonTest, Name) {
    Octagon<double> octagon;
    EXPECT_STREQ(octagon.name(), "Octagon");
}