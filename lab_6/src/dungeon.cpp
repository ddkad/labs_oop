#include "../include/dungeon.h"
#include "../include/npc_factory.h"
#include "../include/visitor.h"

#include <algorithm>
#include <fstream>
#include <iostream>

DungeonEditor::DungeonEditor() {
  addObserver(std::make_unique<FileObserver>("log.txt"));
  addObserver(std::make_unique<ConsoleObserver>());
}

void DungeonEditor::addObserver(std::unique_ptr<Observer> observer) {
  observers.push_back(std::move(observer));
}

bool DungeonEditor::isValidCoordinates(int x, int y) const {
  return x >= 0 && x <= 500 && y >= 0 && y <= 500;
}

bool DungeonEditor::isNameUnique(const std::string &name) const {
  return std::none_of(
      npcs.begin(), npcs.end(),
      [&](const std::shared_ptr<NPC> &npc) { return npc->getName() == name; });
}

bool DungeonEditor::addNPC(const std::string &type, const std::string &name,
                           int x, int y) {
  if (!isValidCoordinates(x, y)) {
    std::cout << "Error: coordinates should be in the range 0-500"
              << std::endl;
    return false;
  }

  if (!isNameUnique(name)) {
    std::cout << "Error: name " << name << " is already in use" << std::endl;
    return false;
  }

  auto npc = NPCFactory::createNPC(type, name, x, y);
  if (npc) {
    npcs.push_back(std::move(npc));
    std::cout << "Added " << type << name << "' in coordinates (" << x
              << ", " << y << ")" << std::endl;
    return true;
  }

  std::cout << "Error: Unknown type of NPC '" << type << "'" << std::endl;
  return false;
}

void DungeonEditor::printNPCs() const {
  std::cout << "\nThe list of NPCs in the dungeon: " << std::endl;

  if (npcs.empty()) {
    std::cout << "The dungeon is empty " << std::endl;
    return;
  }

  for (size_t i = 0; i < npcs.size(); ++i) {
    const auto &npc = npcs[i];
    std::cout << i + 1 << ". " << npc->getType() << " '" << npc->getName()
              << "' in (" << npc->getX() << ", " << npc->getY() << ")"
              << std::endl;
  }
  std::cout << "Total: " << npcs.size() << " NPC " << std::endl;
}

void DungeonEditor::saveToFile(const std::string &filename) const {
  std::ofstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error: couldn't open the file for writing" << std::endl;
    return;
  }

  for (const auto &npc : npcs) {
    file << NPCFactory::saveToString(*npc) << std::endl;
  }

  file.close();
  std::cout << "The data is saved to a file: " << filename << std::endl;
}

void DungeonEditor::loadFromFile(const std::string &filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error: couldn't open the file for reading" << std::endl;
    return;
  }

  npcs.clear();
  std::string line;
  int loadedCount = 0;

  while (std::getline(file, line)) {
    if (line.empty())
      continue;

    auto npc = NPCFactory::loadFromString(line);
    if (npc && npc->isValidPosition()) {
      npcs.push_back(std::move(npc));
      loadedCount++;
    }
  }

  file.close();
  std::cout << "Loaded " << loadedCount << " NPC from the file: " << filename
            << std::endl;
}

void DungeonEditor::startCombat(double combatRange) {
  if (npcs.size() < 2) {
    std::cout << "You need at least 2 NPCs to fight!" << std::endl;
    return;
  }

  for (auto& observer : observers) {
    observer->onCombatStart();
  }

  std::cout << "The battle begins with a range of " << combatRange << " meters"
            << std::endl;
  std::cout << "Before the fight: " << npcs.size() << " NPC" << std::endl;
    
  Observer* combatObserver = observers.empty() ? nullptr : observers[0].get();
  CombatVisitor visitor(combatRange, combatObserver);

  size_t initialCount = npcs.size();
  visitor.battle(npcs, combatRange);
  size_t survivors = npcs.size();

  for (auto &observer : observers) {
    observer->onCombatEnd();
  }

  std::cout << "The battle is over. Dead: " << (initialCount - survivors)
            << ", survived:" << survivors << std::endl;
}

size_t DungeonEditor::getNPCCount() const { return npcs.size(); }

const std::vector<std::shared_ptr<NPC>> &DungeonEditor::getNPCs() const {
  return npcs;
}