#include <gtest/gtest.h>

#include "../include/pure_number.h"

TEST(PureNumberTest, PositiveNums) {
  EXPECT_TRUE(is_pure_number(0));
  EXPECT_TRUE(is_pure_number(1));
  EXPECT_TRUE(is_pure_number(123));
  EXPECT_TRUE(is_pure_number(1123));
  EXPECT_TRUE(is_pure_number(333));
}

TEST(PureNumberTest, NegativeNums) {
  EXPECT_FALSE(is_pure_number(-123));
  EXPECT_FALSE(is_pure_number(-1));
  EXPECT_FALSE(is_pure_number(-100500));
}

TEST(PureNumberTest, NonPureNumbers) {
  EXPECT_FALSE(is_pure_number(321));
  EXPECT_FALSE(is_pure_number(132));
  EXPECT_FALSE(is_pure_number(1221));
  EXPECT_FALSE(is_pure_number(1231));
}

TEST(PureNumberTest, EdgeCases) {
  EXPECT_TRUE(is_pure_number(6));
  EXPECT_TRUE(is_pure_number(123456789));
  EXPECT_FALSE(is_pure_number(987654321));
}