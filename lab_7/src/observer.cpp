#include "observer.h"
#include "npc.h"
#include "defs.h"

#include <iostream>
#include <format>
#include <mutex>

void ConsoleObserver::on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win) {
    std::lock_guard<std::mutex> lock(mtx);
    if (win) {
        std::cout << std::format("\n[KILL] {} ({}) killed {} ({})", 
            attacker->get_name(), type_to_string(attacker->get_type()), 
            defender->get_name(), type_to_string(defender->get_type())) << std::endl;
    } 
}

FileObserver::FileObserver() {
    file.open("log.txt");
}

FileObserver::~FileObserver() {
    if (file.is_open()) file.close();
}

void FileObserver::on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win) {
    std::lock_guard<std::mutex> lock(mtx);
    if (win) {
        file << std::format("{} killed {}\n", attacker->get_name(), defender->get_name());
    }
}