#include <iostream>
#include <thread> 
#include <chrono>
#include <vector>
#include <string>
#include <atomic>
#include <exception>

#include "defs.h"
#include "factory.h"
#include "map.h"
#include "battle.h"
#include "movement.h"
#include "observer.h"

void print_map_state() {
    auto npcs = GameMap::get().get_snapshot();

    std::vector<std::string> grid(MAP_HEIGHT, std::string(MAP_WIDTH, '.'));

    for (const auto& npc : npcs) {
        auto pos = npc->get_position();
        int x = pos.first;
        int y = pos.second;
        
        if (npc->is_alive()) {
            if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT) {
                char symbol = '?';
                switch (npc->get_type()) {
                    case NpcType::Dragon: symbol = 'D'; break; 
                    case NpcType::Bull:   symbol = 'B'; break; 
                    case NpcType::Toad:   symbol = 'T'; break; 
                }
                grid[y][x] = symbol;
            }
        }
    }

    std::string buffer;
    buffer.reserve((MAP_WIDTH + 1) * MAP_HEIGHT + 100);
    buffer += "\nSTART\n";
    for (const auto& row : grid) {
        buffer += row;
        buffer += '\n';
    }
    buffer += "END\n";
    std::cout << buffer << std::flush;
}

int main() {
    try {
        std::srand(std::time(nullptr));

        std::cout << "Generating NPCs..." << std::endl;
        for (int i = 0; i < NPC_COUNT; ++i) {
            NpcType t = static_cast<NpcType>(std::rand() % 3);
            GameMap::get().add_npc(NpcFactory::create_npc(t, std::rand() % MAP_WIDTH, std::rand() % MAP_HEIGHT));
        }

        BattleManager battle_mgr;
        battle_mgr.add_observer(std::make_shared<ConsoleObserver>());
        battle_mgr.add_observer(std::make_shared<FileObserver>());

        std::atomic<bool> game_running{true};

        std::jthread move_thread(movement_thread_func, std::ref(battle_mgr), std::ref(game_running));

        auto start_time = std::chrono::steady_clock::now();
        
        while (true) {
            auto now = std::chrono::steady_clock::now();
            if (std::chrono::duration_cast<std::chrono::seconds>(now - start_time).count() >= GAME_DURATION_SEC) {
                break;
            }
            print_map_state();
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }


        game_running = false;

        
        battle_mgr.stop();

        std::cout << "\nGAME OVER\nSaving survivors...\n";
        GameMap::get().save("map_dump.txt");

    } catch (const std::exception& e) {
        std::cerr << "CRITICAL ERROR: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "UNKNOWN ERROR" << std::endl;
        return 1;
    }

    return 0;
}