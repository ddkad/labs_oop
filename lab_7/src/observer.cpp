#include "../include/observer.h"
#include "../include/npc.h"
#include <iostream>

extern std::mutex print_mutex;

void TextObserver::onFight(const std::shared_ptr<NPC> attacker, 
                          const std::shared_ptr<NPC> defender, 
                          bool win) {
    std::lock_guard<std::mutex> lock(print_mutex);
    
    if (win) {
        std::cout << attacker->getName() << " killed " << defender->getName() << std::endl;
    } else {
        std::cout << attacker->getName() << " failed to kill " << defender->getName() << std::endl;
    }
}