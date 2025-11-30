#include <gtest/gtest.h>

#include "dungeon.h"
#include "observer.h"
#include "visitor.h"

class MockObserver : public Observer {
public:
  std::vector<std::string> killEvents;
  int combatStarts = 0;
  int combatEnds = 0;

  void onKill(const std::string &killer, const std::string &victim,
              const std::string &reason) override {
    killEvents.push_back(killer + " " + reason + " " + victim);
  }

  void onCombatStart() override { combatStarts++; }
  void onCombatEnd() override { combatEnds++; }
};

class CombatTest : public ::testing::Test {
protected:
  void SetUp() override { std::remove("combat_test_log.txt"); }

  void TearDown() override { std::remove("combat_test_log.txt"); }
};

TEST_F(CombatTest, NoCombatWhenNotInRange) {
  DungeonEditor editor;

  editor.addNPC("Dragon", "FarDragon", 0, 0);
  editor.addNPC("Bull", "FarBull", 500, 500);

  size_t initialCount = editor.getNPCCount();
  editor.startCombat(10.0);

  EXPECT_EQ(editor.getNPCCount(), initialCount);
}

TEST_F(CombatTest, CombatWithOneNPC) {
  DungeonEditor editor;

  editor.addNPC("Dragon", "Lonely", 100, 100);

  size_t initialCount = editor.getNPCCount();
  editor.startCombat(100.0);

  EXPECT_EQ(editor.getNPCCount(), initialCount);
}

TEST_F(CombatTest, ObserverNotifications) {
  auto mockObserver = std::make_unique<MockObserver>();
  MockObserver *observerPtr = mockObserver.get();

  DungeonEditor editor;
  editor.addObserver(std::move(mockObserver));

  editor.addNPC("Dragon", "D", 10, 10);
  editor.addNPC("Bull", "B", 15, 15);

  editor.startCombat(100.0);

  EXPECT_GE(observerPtr->combatStarts, 1);
  EXPECT_GE(observerPtr->combatEnds, 1);
}