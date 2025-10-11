#include "twelve.h"
#include <gtest/gtest.h>

TEST(TwelveTest, DefaultConstructor) {
  Twelve num;
  EXPECT_EQ(num.getSize(), 1);
  EXPECT_EQ(num.toString(), "0");
}

TEST(TwelveTest, StringConstructor) {
  Twelve num("1B2");
  EXPECT_EQ(num.toString(), "1B2");
  EXPECT_EQ(num.getSize(), 3);
}

TEST(TwelveTest, StringConstructorInvalid) {
  EXPECT_THROW(Twelve num("3R3"), std::exception);
}

TEST(TwelveTest, InitializerListConstructor) {
  Twelve num({'1', 'A', '0'});
  EXPECT_EQ(num.toString(), "1A0");
}

TEST(TwelveTest, SizeValueConstructor) {
  Twelve num(3, 10);
  EXPECT_EQ(num.toString(), "AAA");
  EXPECT_EQ(num.getSize(), 3);
}

TEST(TwelveTest, SizeValueConstructorInvalid) {
  EXPECT_THROW(Twelve num(3, 15), std::exception);
}

TEST(TwelveTest, CopyConstructor) {
  Twelve num1("B2");
  Twelve num2(num1);
  EXPECT_EQ(num2.toString(), "B2");
  EXPECT_EQ(num2.getSize(), 2);
}

TEST(TwelveTest, SumOperation) {
  Twelve num1("1A");
  Twelve num2("B");
  Twelve result = num1.sum(num2);
  EXPECT_EQ(result.toString(), "29");
}

TEST(TwelveTest, SubtractOperation) {
  Twelve num1("2B");
  Twelve num2("1A");
  Twelve result = num1.subtract(num2);
  EXPECT_EQ(result.toString(), "11");
}

TEST(TwelveTest, SubtractInvalid) {
  Twelve num1("A");
  Twelve num2("B");
  EXPECT_THROW(num1.subtract(num2), std::exception);
}

TEST(TwelveTest, ComparisonOperations) {
  Twelve num1("1A");
  Twelve num2("1B");
  Twelve num3("1A");
  EXPECT_TRUE(num1.lessThan(num2));
  EXPECT_TRUE(num2.greaterThan(num1));
  EXPECT_TRUE(num1.equals(num3));
  EXPECT_FALSE(num1.equals(num2));
}

TEST(TwelveTest, SumAssignOperation) {
  Twelve num1("1A");
  Twelve num2("B");
  Twelve result = num1.sumAssign(num2);
  EXPECT_EQ(result.toString(), "29");
}

TEST(TwelveTest, RemoveLeadingZeros) {
  Twelve num({'0', '0', '1', 'A'});
  EXPECT_EQ(num.toString(), "1A");
  EXPECT_EQ(num.getSize(), 2);
}