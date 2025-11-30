#include "../include/visitor.h"
#include "../include/observer.h"

#include <iostream>
#include <algorithm>
#include <random>
#include <memory>

CombatVisitor::CombatVisitor(double range, Observer* obs) 
    : combatRange(range), observer(obs) {}

void CombatVisitor::visit(Dragon& dragon) {
    (void)dragon;
}

void CombatVisitor::visit(Bull& bull) {
    (void)bull;
}

void CombatVisitor::visit(Frog& frog) {
    (void)frog;
}

void CombatVisitor::battle(std::vector<std::shared_ptr<NPC>>& npcs, double range) {
    this->combatRange = range;
    
    std::vector<std::shared_ptr<NPC>> survivors;
    std::vector<bool> killed(npcs.size(), false);
    
    std::random_device rd;
    std::mt19937 g(rd());
    
    for (size_t i = 0; i < npcs.size(); ++i) {
        if (killed[i]) continue;
        
        for (size_t j = i + 1; j < npcs.size(); ++j) {
            if (killed[j]) continue;
            
            if (npcs[i]->distanceTo(*npcs[j]) <= combatRange) {
                auto& npc1 = *npcs[i];
                auto& npc2 = *npcs[j];
                
                if (dynamic_cast<Dragon*>(&npc1) && dynamic_cast<Bull*>(&npc2)) {
                    dragonVsBull(static_cast<Dragon&>(npc1), static_cast<Bull&>(npc2));
                    killed[j] = true;
                }
                else if (dynamic_cast<Dragon*>(&npc2) && dynamic_cast<Bull*>(&npc1)) {
                    dragonVsBull(static_cast<Dragon&>(npc2), static_cast<Bull&>(npc1));
                    killed[i] = true;
                }
                else if (dynamic_cast<Bull*>(&npc1) && dynamic_cast<Frog*>(&npc2)) {
                    bullVsFrog(static_cast<Bull&>(npc1), static_cast<Frog&>(npc2));
                    killed[j] = true;
                }
                else if (dynamic_cast<Bull*>(&npc2) && dynamic_cast<Frog*>(&npc1)) {
                    bullVsFrog(static_cast<Bull&>(npc2), static_cast<Frog&>(npc1));
                    killed[i] = true;
                }
                else if (dynamic_cast<Dragon*>(&npc1) && dynamic_cast<Frog*>(&npc2)) {
                    frogVsDragon(static_cast<Frog&>(npc2), static_cast<Dragon&>(npc1));
                    killed[j] = true;
                }
                else if (dynamic_cast<Dragon*>(&npc2) && dynamic_cast<Frog*>(&npc1)) {
                    frogVsDragon(static_cast<Frog&>(npc1), static_cast<Dragon&>(npc2));
                    killed[i] = true;
                }
            }
        }
    }
    
    for (size_t i = 0; i < npcs.size(); ++i) {
        if (!killed[i]) {
            survivors.push_back(npcs[i]);
        }
    }
    
    npcs = survivors;
}

void CombatVisitor::dragonVsBull(Dragon& dragon, Bull& bull) {
    if (observer) {
        observer->onKill(dragon.getName(), bull.getName(), "ate");
    }
}

void CombatVisitor::bullVsFrog(Bull& bull, Frog& frog) {
    if (observer) {
        observer->onKill(bull.getName(), frog.getName(), "trampled on");
    }
}

void CombatVisitor::frogVsDragon(Frog& frog, Dragon& dragon) {
    if (observer) {
        observer->onKill(dragon.getName(), frog.getName(), "couldn't escape from");
    }
}