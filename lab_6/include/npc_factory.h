#ifndef NPC_FACTORY_H
#define NPC_FACTORY_H

#include "npc.h"

#include <memory>
#include <string>

class NPCFactory {
public:
  static std::unique_ptr<NPC> createNPC(const std::string &type,
                                        const std::string &name, int x, int y);
  static std::unique_ptr<NPC> loadFromString(const std::string &data);
  static std::string saveToString(const NPC &npc);
};

#endif