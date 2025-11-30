#ifndef DUNGEON_H
#define DUNGEON_H

#include "npc.h"
#include "observer.h"

#include <memory>
#include <string>
#include <vector>

class DungeonEditor {
private:
  std::vector<std::shared_ptr<NPC>> npcs;
  std::vector<std::unique_ptr<Observer>> observers;

  bool isValidCoordinates(int x, int y) const;
  bool isNameUnique(const std::string &name) const;

public:
  DungeonEditor();

  void addObserver(std::unique_ptr<Observer> observer);

  bool addNPC(const std::string &type, const std::string &name, int x, int y);
  void printNPCs() const;
  void saveToFile(const std::string &filename) const;
  void loadFromFile(const std::string &filename);
  void startCombat(double combatRange);

  size_t getNPCCount() const;
  const std::vector<std::shared_ptr<NPC>> &getNPCs() const;
};

#endif