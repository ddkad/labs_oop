#ifndef FIGHT_MANAGER_H
#define FIGHT_MANAGER_H

#include <memory>
#include <queue>
#include <mutex>
#include <condition_variable>
#include "npc.h"

struct FightEvent {
    std::shared_ptr<NPC> attacker;
    std::shared_ptr<NPC> defender;
    
    FightEvent(std::shared_ptr<NPC> a, std::shared_ptr<NPC> d) 
        : attacker(std::move(a)), defender(std::move(d)) {}
};

class FightManager {
private:
    std::queue<FightEvent> events;
    mutable std::mutex mtx;
    std::condition_variable cv;
    bool stopped;
    
    FightManager();
    
public:
    static FightManager& get();
    
    FightManager(const FightManager&) = delete;
    FightManager& operator=(const FightManager&) = delete;
    
    void addEvent(FightEvent&& event);
    void processEvents();
    void stop();
    
    size_t getQueueSize() const;
};

#endif