#pragma once

#include <queue>
#include <vector>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <atomic>

#include "observer.h"

struct FightEvent {
    std::shared_ptr<NPC> attacker;
    std::shared_ptr<NPC> defender;
};

class BattleManager {
    std::queue<FightEvent> events;
    std::mutex queue_mutex;
    std::condition_variable cv;
    std::atomic<bool> running{true};
    std::thread worker;
    
    std::vector<std::shared_ptr<IFightObserver>> observers;

    void process_battles();

public:
    BattleManager();
    ~BattleManager();

    void add_observer(std::shared_ptr<IFightObserver> obs);
    void add_event(FightEvent event);
    void stop();
};