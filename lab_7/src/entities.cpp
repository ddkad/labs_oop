#include "entities.h"
#include "visitor.h"


Dragon::Dragon(int x, int y, std::string name) : NPC(NpcType::Dragon, x, y, name) {}

void Dragon::accept(NPCVisitor& visitor) { 
    visitor.visit(*this); 
}


Toad::Toad(int x, int y, std::string name) : NPC(NpcType::Toad, x, y, name) {}

void Toad::accept(NPCVisitor& visitor) { 
    visitor.visit(*this); 
}


Bull::Bull(int x, int y, std::string name) : NPC(NpcType::Bull, x, y, name) {}

void Bull::accept(NPCVisitor& visitor) { 
    visitor.visit(*this); 
}