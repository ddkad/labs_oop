#include <gtest/gtest.h>

#include "dungeon.h"

#include <filesystem>
#include <fstream>

class DungeonTest : public ::testing::Test {
protected:
  void SetUp() override {
    std::remove("test_save.txt");
    std::remove("test_log.txt");
  }

  void TearDown() override {
    std::remove("test_save.txt");
    std::remove("test_log.txt");
  }
};

TEST_F(DungeonTest, AddValidNPC) {
  DungeonEditor editor;

  EXPECT_TRUE(editor.addNPC("Dragon", "Smaug", 100, 100));
  EXPECT_TRUE(editor.addNPC("Bull", "Horny", 200, 200));
  EXPECT_TRUE(editor.addNPC("Frog", "Greeny", 300, 300));

  EXPECT_EQ(editor.getNPCCount(), 3);
}

TEST_F(DungeonTest, AddInvalidNPC) {
  DungeonEditor editor;
  EXPECT_FALSE(editor.addNPC("Dragon", "Invalid1", -1, 100));
  EXPECT_FALSE(editor.addNPC("Bull", "Invalid2", 100, 501));
  EXPECT_FALSE(editor.addNPC("Frog", "Invalid3", 600, 600));

  EXPECT_FALSE(editor.addNPC("Unicorn", "Magic", 100, 100));

  EXPECT_TRUE(editor.addNPC("Dragon", "Unique", 100, 100));
  EXPECT_FALSE(editor.addNPC("Bull", "Unique", 200, 200));

  EXPECT_EQ(editor.getNPCCount(), 1);
}

TEST_F(DungeonTest, SaveAndLoad) {
  DungeonEditor editor;

  editor.addNPC("Dragon", "Smaug", 100, 100);
  editor.addNPC("Bull", "Horny", 200, 200);
  editor.addNPC("Frog", "Greeny", 300, 300);

  size_t originalCount = editor.getNPCCount();

  editor.saveToFile("test_save.txt");

  std::ifstream file("test_save.txt");
  EXPECT_TRUE(file.is_open());

  DungeonEditor loadedEditor;
  loadedEditor.loadFromFile("test_save.txt");

  EXPECT_EQ(loadedEditor.getNPCCount(), originalCount);
}

TEST_F(DungeonTest, LoadNonExistentFile) {
  DungeonEditor editor;

  editor.loadFromFile("non_existent_file.txt");

  EXPECT_EQ(editor.getNPCCount(), 0);
}

TEST_F(DungeonTest, EmptyDungeonOperations) {
  DungeonEditor editor;

  editor.printNPCs();
  editor.saveToFile("empty_save.txt");

  editor.startCombat(100.0);
}