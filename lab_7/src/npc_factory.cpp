#include "../include/npc_factory.h"
#include <random>

std::shared_ptr<NPC> NPCFactory::createNPC(NpcType type, const std::string& name, int x, int y) {
    switch (type) {
        case NpcType::Dragon:
            return std::make_shared<Dragon>(name, x, y);
        case NpcType::Bull:
            return std::make_shared<Bull>(name, x, y);
        case NpcType::Frog:
            return std::make_shared<Frog>(name, x, y);
        default:
            return nullptr;
    }
}

std::shared_ptr<NPC> NPCFactory::createRandomNPC(const std::string& name, int maxX, int maxY) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> typeDist(0, 2);
    static std::uniform_int_distribution<> coordDist(0, 100);
    
    NpcType type = static_cast<NpcType>(typeDist(gen));
    int x = coordDist(gen) % (maxX + 1);
    int y = coordDist(gen) % (maxY + 1);
    
    return createNPC(type, name + "_" + std::to_string(typeDist(gen)), x, y);
}