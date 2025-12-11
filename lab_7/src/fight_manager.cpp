#include "../include/fight_manager.h"
#include <thread>
#include <iostream>

FightManager::FightManager() : stopped(false) {}

FightManager& FightManager::get() {
    static FightManager instance;
    return instance;
}

void FightManager::addEvent(FightEvent&& event) {
    std::lock_guard<std::mutex> lock(mtx);
    if (!stopped) {
        events.push(std::move(event));
        cv.notify_one();
    }
}

void FightManager::processEvents() {
    while (!stopped) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait_for(lock, std::chrono::milliseconds(100), [this]() {
            return !events.empty() || stopped;
        });
        
        if (stopped && events.empty()) break;
        
        if (!events.empty()) {
            auto event = std::move(events.front());
            events.pop();
            lock.unlock();
            
            if (event.attacker && event.defender && 
                event.attacker->isAlive() && event.defender->isAlive()) {
                
                int attackPower = 0, defensePower = 0;
                event.attacker->attack(attackPower);
                event.defender->defend(defensePower);
                
                if (attackPower > defensePower) {
                    if (event.defender->accept(event.attacker)) {
                        event.defender->mustDie();
                    }
                }
            }
        }
    }
}

void FightManager::stop() {
    std::lock_guard<std::mutex> lock(mtx);
    stopped = true;
    cv.notify_all();
}

size_t FightManager::getQueueSize() const {
    std::lock_guard<std::mutex> lock(mtx);
    return events.size();
}