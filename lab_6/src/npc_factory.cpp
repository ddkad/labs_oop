#include "../include/npc_factory.h"

#include <sstream>

std::unique_ptr<NPC> NPCFactory::createNPC(const std::string &type,
                                           const std::string &name, int x,
                                           int y) {
  if (type == "Dragon") {
    return std::make_unique<Dragon>(name, x, y);
  } else if (type == "Bull") {
    return std::make_unique<Bull>(name, x, y);
  } else if (type == "Frog") {
    return std::make_unique<Frog>(name, x, y);
  }
  return nullptr;
}

std::unique_ptr<NPC> NPCFactory::loadFromString(const std::string &data) {
  std::istringstream iss(data);
  std::string type, name;
  int x, y;

  if (iss >> type >> name >> x >> y) {
    return createNPC(type, name, x, y);
  }
  return nullptr;
}

std::string NPCFactory::saveToString(const NPC &npc) {
  std::ostringstream oss;
  oss << npc.getType() << " " << npc.getName() << " " << npc.getX() << " "
      << npc.getY();
  return oss.str();
}