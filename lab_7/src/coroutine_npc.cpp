#include "../include/coroutine_npc.h"
#include "../include/fight_manager.h"
#include <random>
#include <chrono>

SimpleNPCBehavior::SimpleNPCBehavior(std::shared_ptr<NPC> npc, GameWorld& world) 
    : npc(npc), world(world), isDone(false) {}

void SimpleNPCBehavior::resume() {
    if (!npc->isAlive()) {
        isDone = true;
        return;
    }

    static std::random_device rd;
    static std::mt19937 gen(rd());
    

    {
        int moveDist = npc->getMoveDistance();
        std::uniform_int_distribution<> dist(-moveDist, moveDist);
        int dx = dist(gen);
        int dy = dist(gen);
        npc->move(dx, dy, 100, 100);
    }
    

    {
        auto allNPCs = world.getNPCs();
        for (const auto& other : allNPCs) {
            if (other != npc && other->isAlive() && 
                npc->isClose(other, std::min(npc->getKillDistance(), 
                                             other->getKillDistance()))) {
                FightManager::get().addEvent(FightEvent{npc, other});
            }
        }
    }
    
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    if (!npc->isAlive()) {
        isDone = true;
    }
}