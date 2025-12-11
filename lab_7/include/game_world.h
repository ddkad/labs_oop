#ifndef GAME_WORLD_H
#define GAME_WORLD_H

#include <memory>
#include <vector>
#include <mutex>
#include <shared_mutex> 
#include "npc.h"

class GameWorld {
private:
    std::vector<std::shared_ptr<NPC>> npcs;
    mutable std::shared_mutex npcs_mutex; 
    int maxX, maxY;
    
public:
    GameWorld(int maxX, int maxY);
    
    void addNPC(std::shared_ptr<NPC> npc);
    void removeDeadNPCs();
    void moveNPCs();
    void detectBattles();
    
    std::vector<std::shared_ptr<NPC>> getNPCs() const;
    size_t getNPCsCount() const;
    
    void printMap() const;
    void printSurvivors() const;
    
    void clear();
};

#endif 