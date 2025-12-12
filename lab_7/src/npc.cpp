#include "npc.h"

#include <algorithm>
#include <random>


NPC::NPC(NpcType t, int _x, int _y, std::string _name) 
    : type(t), x(_x), y(_y), name(_name), alive(true) {}

std::string NPC::get_name() const {
    std::lock_guard<std::mutex> lock(npc_mutex);
    return name;
}

bool NPC::is_alive() const {
    std::lock_guard<std::mutex> lock(npc_mutex);
    return alive;
}

std::pair<int, int> NPC::get_position() const {
    std::lock_guard<std::mutex> lock(npc_mutex);
    return {x, y};
}

void NPC::kill() {
    std::lock_guard<std::mutex> lock(npc_mutex);
    alive = false;
}

void NPC::move(int max_dist, int map_w, int map_h) {
    std::lock_guard<std::mutex> lock(npc_mutex);
    if (!alive) return;

    static thread_local std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> dir(-1, 1);

    x = std::clamp(x + dir(gen) * max_dist, 0, map_w - 1);
    y = std::clamp(y + dir(gen) * max_dist, 0, map_h - 1);
}


std::string type_to_string(NpcType t) {
    switch(t) {
        case NpcType::Dragon: return "Dragon";
        case NpcType::Toad:   return "Toad";
        case NpcType::Bull:   return "Bull";
    }
    return "Unknown";
}