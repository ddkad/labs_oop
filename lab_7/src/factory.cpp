#include "factory.h"
#include "entities.h"

#include <atomic>
#include <format>
#include <iostream>
#include <fstream> 

std::shared_ptr<NPC> NpcFactory::create_npc(NpcType type, int x, int y) {
    static std::atomic<int> d_count{0}, t_count{0}, b_count{0};

    switch (type) {
        case NpcType::Dragon: 
            return std::make_shared<Dragon>(x, y, std::format("Dragon_{}", ++d_count));
        case NpcType::Toad:   
            return std::make_shared<Toad>(x, y, std::format("Toad_{}", ++t_count));
        case NpcType::Bull:   
            return std::make_shared<Bull>(x, y, std::format("Bull_{}", ++b_count));
    }
    return nullptr;
}

std::shared_ptr<NPC> NpcFactory::load_from_file(std::ifstream& is) {
    int type_int, x, y;
    std::string name;

    if (is >> type_int >> name >> x >> y) {
        NpcType t = static_cast<NpcType>(type_int);
        switch (t) {
            case NpcType::Dragon: return std::make_shared<Dragon>(x, y, name);
            case NpcType::Toad:   return std::make_shared<Toad>(x, y, name);
            case NpcType::Bull:   return std::make_shared<Bull>(x, y, name);
        }
    }
    return nullptr;
}