#include "visitor.h"
#include "entities.h"

FightVisitor::FightVisitor(NpcType attacker) : attacker_type(attacker), fight_possible(false) {}

void FightVisitor::visit(Dragon& dragon) {
    if (attacker_type == NpcType::Toad) fight_possible = true;
    else fight_possible = false;
}

void FightVisitor::visit(Toad& toad) {
    if (attacker_type == NpcType::Bull) fight_possible = true;
    else fight_possible = false;
}

void FightVisitor::visit(Bull& bull) {
    if (attacker_type == NpcType::Dragon) fight_possible = true;
    else fight_possible = false;
}