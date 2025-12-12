#include "map.h"

#include <fstream>

GameMap& GameMap::get() {
    static GameMap instance;
    return instance;
}

void GameMap::add_npc(std::shared_ptr<NPC> npc) {
    std::unique_lock lock(map_mutex);
    npcs.push_back(npc);
}

std::vector<std::shared_ptr<NPC>> GameMap::get_snapshot() {
    std::shared_lock lock(map_mutex);
    return npcs;
}

void GameMap::save(const std::string& filename) {
    std::shared_lock lock(map_mutex);
    std::ofstream fs(filename);
    if (!fs.is_open()) return;
    
    fs << npcs.size() << "\n";
    for (const auto& npc : npcs) {
        std::lock_guard<std::mutex> npc_lock(npc->npc_mutex);
        if (npc->alive) {
            fs << (int)npc->type << " " << npc->name << " " << npc->x << " " << npc->y << "\n";
        }
    }
}