#include <gtest/gtest.h>

#include "npc.h"

TEST(NPCTest, BasicCreation) {
  Dragon dragon("Smaug", 100, 200);
  EXPECT_EQ(dragon.getName(), "Smaug");
  EXPECT_EQ(dragon.getX(), 100);
  EXPECT_EQ(dragon.getY(), 200);
  EXPECT_EQ(dragon.getType(), "Dragon");
}

TEST(NPCTest, PositionValidation) {
  Dragon valid1("Valid1", 0, 0);
  Dragon valid2("Valid2", 500, 500);
  Dragon valid3("Valid3", 250, 250);

  EXPECT_TRUE(valid1.isValidPosition());
  EXPECT_TRUE(valid2.isValidPosition());
  EXPECT_TRUE(valid3.isValidPosition());

  Dragon invalid1("Invalid1", -1, 100);
  Dragon invalid2("Invalid2", 100, -1);
  Dragon invalid3("Invalid3", 501, 100);
  Dragon invalid4("Invalid4", 100, 501);
  Dragon invalid5("Invalid5", -10, -10);

  EXPECT_FALSE(invalid1.isValidPosition());
  EXPECT_FALSE(invalid2.isValidPosition());
  EXPECT_FALSE(invalid3.isValidPosition());
  EXPECT_FALSE(invalid4.isValidPosition());
  EXPECT_FALSE(invalid5.isValidPosition());
}

TEST(NPCTest, DistanceCalculation) {
  Dragon dragon1("D1", 0, 0);
  Dragon dragon2("D2", 3, 4);

  EXPECT_DOUBLE_EQ(dragon1.distanceTo(dragon2), 5.0);

  Bull bull1("B1", 10, 10);
  Bull bull2("B2", 10, 20);

  EXPECT_DOUBLE_EQ(bull1.distanceTo(bull2), 10.0);
}

TEST(NPCTest, DifferentNPCTypes) {
  Dragon dragon("FireBreather", 100, 100);
  Bull bull("Horned", 200, 200);
  Frog frog("Green", 300, 300);

  EXPECT_EQ(dragon.getType(), "Dragon");
  EXPECT_EQ(bull.getType(), "Bull");
  EXPECT_EQ(frog.getType(), "Frog");
}