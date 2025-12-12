#include <random>
#include <iostream> 

#include "battle.h"
#include "visitor.h"
#include "npc.h"

BattleManager::BattleManager() {
    worker = std::thread([this]() { this->process_battles(); });
}

BattleManager::~BattleManager() {
    stop();
}

void BattleManager::add_observer(std::shared_ptr<IFightObserver> obs) {
    std::lock_guard<std::mutex> lock(queue_mutex);
    observers.push_back(obs);
}

void BattleManager::add_event(FightEvent event) {
    {
        std::lock_guard<std::mutex> lock(queue_mutex);
        events.push(event);
    }
    cv.notify_one();
}

void BattleManager::stop() {
    running = false;
    cv.notify_all();
    if (worker.joinable()) worker.join();
}

void BattleManager::process_battles() {
    try {
        static std::mt19937 gen(std::random_device{}());
        std::uniform_int_distribution<> d6(1, 6);

        while (running) {
            std::unique_lock<std::mutex> lock(queue_mutex);
            cv.wait(lock, [this] { return !events.empty() || !running; });
            if (!running && events.empty()) break;

            FightEvent evt = events.front();
            events.pop();
            lock.unlock();

            if (!evt.attacker || !evt.defender) continue;

            std::scoped_lock npc_lock(evt.attacker->npc_mutex, evt.defender->npc_mutex);

            if (evt.attacker->alive && evt.defender->alive) {
                FightVisitor fight_visitor(evt.attacker->get_type());
                evt.defender->accept(fight_visitor); 

                if (fight_visitor.can_fight()) {
                    int att_p = d6(gen);
                    int def_p = d6(gen);

                    bool win = att_p > def_p;
                    if (win) {
                        evt.defender->kill(); 
                    }

                    {
                        std::lock_guard<std::mutex> obs_lock(queue_mutex); 
                        for (auto& obs : observers) {
                            obs->on_fight(evt.attacker, evt.defender, win);
                        }
                    }
                }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error in Battle Thread: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown error in Battle Thread" << std::endl;
    }
}