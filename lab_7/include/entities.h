#pragma once

#include "npc.h"

class NPCVisitor;

class Dragon : public NPC {
public:
    Dragon(int x, int y, std::string name);
    void accept(NPCVisitor& visitor) override;
};

class Toad : public NPC {
public:
    Toad(int x, int y, std::string name);
    void accept(NPCVisitor& visitor) override;
};

class Bull : public NPC {
public:
    Bull(int x, int y, std::string name);
    void accept(NPCVisitor& visitor) override;
};