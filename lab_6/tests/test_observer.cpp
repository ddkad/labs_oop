#include <gtest/gtest.h>

#include "observer.h"

#include <fstream>
#include <sstream>

class ObserverTest : public ::testing::Test {
protected:
  void SetUp() override { std::remove("test_observer_log.txt"); }

  void TearDown() override { std::remove("test_observer_log.txt"); }
};

TEST_F(ObserverTest, FileObserverCreatesFile) {
  {
    FileObserver observer("test_observer_log.txt");
    observer.onCombatStart();
    observer.onKill("Dragon", "Bull", "ate");
    observer.onCombatEnd();
  }

  std::ifstream file("test_observer_log.txt");
  EXPECT_TRUE(file.is_open());

  std::stringstream buffer;
  buffer << file.rdbuf();
  std::string content = buffer.str();

  EXPECT_NE(content.find("ate"), std::string::npos);
  EXPECT_NE(content.find("The beginning of the battle"), std::string::npos);
  EXPECT_NE(content.find("The end of the fight"), std::string::npos);
}

TEST_F(ObserverTest, ConsoleObserverInterface) {
  ConsoleObserver observer;

  observer.onCombatStart();
  observer.onKill("TestKiller", "TestVictim", "tested");
  observer.onCombatEnd();

  SUCCEED();
}

TEST_F(ObserverTest, MultipleEvents) {
  FileObserver observer("test_observer_log.txt");

  observer.onCombatStart();
  observer.onKill("Dragon1", "Bull1", "ate");
  observer.onKill("Bull2", "Frog1", "trampled on");
  observer.onKill("Dragon2", "Frog2", "couldn't escape from");
  observer.onCombatEnd();

  std::ifstream file("test_observer_log.txt");
  std::stringstream buffer;
  buffer << file.rdbuf();
  std::string content = buffer.str();

  EXPECT_NE(content.find("ate"), std::string::npos);
  EXPECT_NE(content.find("trampled on"), std::string::npos);
  EXPECT_NE(content.find("couldn't escape from"), std::string::npos);
}