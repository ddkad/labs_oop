#pragma once

#include "npc.h"

#include <vector>
#include <memory>
#include <shared_mutex>
#include <string>


class GameMap {
    std::vector<std::shared_ptr<NPC>> npcs;
    std::shared_mutex map_mutex;

    GameMap() = default; 

public:
    GameMap(const GameMap&) = delete;
    void operator=(const GameMap&) = delete;

    static GameMap& get();

    void add_npc(std::shared_ptr<NPC> npc);
    std::vector<std::shared_ptr<NPC>> get_snapshot();
    void save(const std::string& filename);
};