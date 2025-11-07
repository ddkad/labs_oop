#include <gtest/gtest.h>
#include <memory>
#include <figure.h>
#include <triangle.h>
#include <hexagon.h>
#include <octagon.h>
#include <array.h>

class FigureTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(FigureTest, VirtualFunctions) {
    std::shared_ptr<Figure<double>> triangle = std::make_shared<Triangle<double>>();
    std::shared_ptr<Figure<double>> hexagon = std::make_shared<Hexagon<double>>();
    std::shared_ptr<Figure<double>> octagon = std::make_shared<Octagon<double>>();
    
    EXPECT_NO_THROW(triangle->area());
    EXPECT_NO_THROW(hexagon->area());
    EXPECT_NO_THROW(octagon->area());
    
    EXPECT_NO_THROW(triangle->center());
    EXPECT_NO_THROW(hexagon->center());
    EXPECT_NO_THROW(octagon->center());
    
    EXPECT_STRNE(triangle->name(), hexagon->name());
    EXPECT_STRNE(hexagon->name(), octagon->name());
}

TEST_F(FigureTest, ArrayOfFigures) {
    Array<std::shared_ptr<Figure<double>>> figures;
    
    figures.push(std::make_shared<Triangle<double>>());
    figures.push(std::make_shared<Hexagon<double>>());
    figures.push(std::make_shared<Octagon<double>>());
    
    EXPECT_EQ(figures.size(), 3);
    
    for (int i = 0; i < figures.size(); ++i) {
        EXPECT_NO_THROW(figures[i]->area());
        EXPECT_NO_THROW(figures[i]->center());
        EXPECT_NO_THROW(figures[i]->name());
        EXPECT_GE(figures[i]->area(), 0.0);
    }
}