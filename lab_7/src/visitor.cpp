#include "../include/visitor.h"
#include "../include/npc.h"
#include <iostream>

class BattleVisitor : public Visitor {
private:
    std::shared_ptr<NPC> attacker;
    
public:
    BattleVisitor(std::shared_ptr<NPC> attacker) : attacker(attacker) {}
    
    void visit(Dragon& dragon) override {
        if (auto bull = std::dynamic_pointer_cast<Bull>(attacker)) {
            int attackPower = 0, defensePower = 0;
            attacker->attack(attackPower);
            dragon.defend(defensePower);
            
            if (attackPower > defensePower) {
                dragon.mustDie();
            }
        }
    }
    
    void visit(Bull& bull) override {
        if (auto dragon = std::dynamic_pointer_cast<Dragon>(attacker)) {
            int attackPower = 0, defensePower = 0;
            attacker->attack(attackPower);
            bull.defend(defensePower);
            
            if (attackPower > defensePower) {
                bull.mustDie();
            }
        }
    }
    
    void visit(Frog& frog) override {
        if (auto bull = std::dynamic_pointer_cast<Bull>(attacker)) {
            int attackPower = 0, defensePower = 0;
            attacker->attack(attackPower);
            frog.defend(defensePower);
            
            if (attackPower > defensePower) {
                frog.mustDie();
            }
        }
    }
};