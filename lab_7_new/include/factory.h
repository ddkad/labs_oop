#pragma once

#include <memory>
#include <string>

#include "npc.h"

class NpcFactory {
public:
    static std::shared_ptr<NPC> create_npc(NpcType type, int x, int y);
    static std::shared_ptr<NPC> load_from_file(std::ifstream& is);
};