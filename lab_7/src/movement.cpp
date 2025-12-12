#include "movement.h"
#include "map.h"
#include "coro.h"
#include "defs.h"
#include "battle.h"

#include <map>
#include <chrono>
#include <thread>
#include <cmath>
#include <iostream>

int get_move_dist(NpcType t) {
    switch(t) {
        case NpcType::Dragon: return 50;
        case NpcType::Toad:   return 1;
        case NpcType::Bull:   return 30;
    }
    return 0;
}

int get_kill_dist(NpcType t) {
    switch(t) {
        case NpcType::Dragon: return 30;
        case NpcType::Toad:   return 10;
        case NpcType::Bull:   return 10;
    }
    return 0;
}

int dist_sq(const std::pair<int, int>& p1, const std::pair<int, int>& p2) {
    int dx = p1.first - p2.first;
    int dy = p1.second - p2.second;
    return dx*dx + dy*dy;
}

static Generator<FightEvent> detect_fights(const std::vector<std::shared_ptr<NPC>>& npcs) {
    for (size_t i = 0; i < npcs.size(); ++i) {
        for (size_t j = i + 1; j < npcs.size(); ++j) {
            auto& a = npcs[i];
            auto& b = npcs[j];

            if (!a->is_alive() || !b->is_alive()) continue;

            auto pos_a = a->get_position();
            auto pos_b = b->get_position();
            int dist = dist_sq(pos_a, pos_b);

            int range_a = get_kill_dist(a->get_type());
            if (dist <= range_a * range_a) {
                co_yield FightEvent{a, b};
            }

            int range_b = get_kill_dist(b->get_type());
            if (dist <= range_b * range_b) {
                co_yield FightEvent{b, a};
            }
        }
    }
}

void movement_thread_func(BattleManager& battle_mgr, std::atomic<bool>& running) {
    try {
        while (running) {
            auto npcs = GameMap::get().get_snapshot();

            for (auto& npc : npcs) {
                npc->move(get_move_dist(npc->get_type()), MAP_WIDTH, MAP_HEIGHT);
            }

            for (auto event : detect_fights(npcs)) {
                battle_mgr.add_event(event);
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(500)); 
        }
    } catch (const std::exception& e) {
        std::cerr << "Error in Movement Thread: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown error in Movement Thread" << std::endl;
    }
}