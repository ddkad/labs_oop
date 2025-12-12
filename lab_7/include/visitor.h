#pragma once

#include "defs.h"


class Dragon;
class Toad;
class Bull;

class NPCVisitor {
public:
    virtual void visit(Dragon& dragon) = 0;
    virtual void visit(Toad& toad) = 0;
    virtual void visit(Bull& bull) = 0;
};


class FightVisitor : public NPCVisitor {
    NpcType attacker_type;
    bool fight_possible;
public:
    FightVisitor(NpcType attacker);
    bool can_fight() const { return fight_possible; }

    void visit(Dragon& dragon) override;
    void visit(Toad& toad) override;
    void visit(Bull& bull) override;
};