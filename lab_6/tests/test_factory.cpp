#include <gtest/gtest.h>

#include "npc_factory.h"

TEST(FactoryTest, CreateAllTypes) {
  auto dragon = NPCFactory::createNPC("Dragon", "Smaug", 100, 100);
  auto bull = NPCFactory::createNPC("Bull", "Horny", 200, 200);
  auto frog = NPCFactory::createNPC("Frog", "Greeny", 300, 300);

  EXPECT_NE(dragon, nullptr);
  EXPECT_NE(bull, nullptr);
  EXPECT_NE(frog, nullptr);

  EXPECT_EQ(dragon->getType(), "Dragon");
  EXPECT_EQ(bull->getType(), "Bull");
  EXPECT_EQ(frog->getType(), "Frog");
}

TEST(FactoryTest, CreateInvalidType) {
  auto invalid = NPCFactory::createNPC("Unicorn", "Magic", 100, 100);
  EXPECT_EQ(invalid, nullptr);
}

TEST(FactoryTest, SerializationRoundTrip) {
  Dragon original("TestDragon", 123, 456);

  std::string serialized = NPCFactory::saveToString(original);
  auto restored = NPCFactory::loadFromString(serialized);

  EXPECT_NE(restored, nullptr);
  EXPECT_EQ(restored->getType(), "Dragon");
  EXPECT_EQ(restored->getName(), "TestDragon");
  EXPECT_EQ(restored->getX(), 123);
  EXPECT_EQ(restored->getY(), 456);
}

TEST(FactoryTest, SerializationAllTypes) {
  Dragon dragon("D", 1, 2);
  Bull bull("B", 3, 4);
  Frog frog("F", 5, 6);

  std::string dragonStr = NPCFactory::saveToString(dragon);
  std::string bullStr = NPCFactory::saveToString(bull);
  std::string frogStr = NPCFactory::saveToString(frog);

  auto dragonRestored = NPCFactory::loadFromString(dragonStr);
  auto bullRestored = NPCFactory::loadFromString(bullStr);
  auto frogRestored = NPCFactory::loadFromString(frogStr);

  EXPECT_EQ(dragonRestored->getType(), "Dragon");
  EXPECT_EQ(bullRestored->getType(), "Bull");
  EXPECT_EQ(frogRestored->getType(), "Frog");
}

TEST(FactoryTest, LoadInvalidData) {
  auto invalid1 = NPCFactory::loadFromString("Dragon OnlyType");
  EXPECT_EQ(invalid1, nullptr);

  auto invalid2 = NPCFactory::loadFromString("InvalidType Name 100 100");
  EXPECT_EQ(invalid2, nullptr);

  auto invalid3 = NPCFactory::loadFromString("Dragon Name not_number 100");
}