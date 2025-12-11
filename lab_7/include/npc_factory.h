#ifndef NPC_FACTORY_H
#define NPC_FACTORY_H

#include <memory>
#include "npc.h"

class NPCFactory {
public:
    static std::shared_ptr<NPC> createNPC(NpcType type, const std::string& name, int x, int y);
    static std::shared_ptr<NPC> createRandomNPC(const std::string& name, int maxX, int maxY);
};

#endif