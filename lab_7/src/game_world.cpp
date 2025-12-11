#include "../include/game_world.h"
#include "../include/fight_manager.h"
#include <random>
#include <iostream>
#include <iomanip>

extern std::mutex print_mutex;

GameWorld::GameWorld(int maxX, int maxY) : maxX(maxX), maxY(maxY) {}

void GameWorld::addNPC(std::shared_ptr<NPC> npc) {
    std::unique_lock<std::shared_mutex> lock(npcs_mutex);
    npcs.push_back(npc);
}

void GameWorld::removeDeadNPCs() {
    std::unique_lock<std::shared_mutex> lock(npcs_mutex);
    auto it = std::remove_if(npcs.begin(), npcs.end(), 
        [](const std::shared_ptr<NPC>& npc) { return !npc->isAlive(); });
    npcs.erase(it, npcs.end());
}

void GameWorld::moveNPCs() {
    std::shared_lock<std::shared_mutex> lock(npcs_mutex);
    static std::random_device rd;
    static std::mt19937 gen(rd());
    
    for (auto& npc : npcs) {
        if (npc->isAlive()) {
            int moveDist = npc->getMoveDistance();
            std::uniform_int_distribution<> dist(-moveDist, moveDist);
            int dx = dist(gen);
            int dy = dist(gen);
            npc->move(dx, dy, maxX, maxY);
        }
    }
}

void GameWorld::detectBattles() {
    std::shared_lock<std::shared_mutex> lock(npcs_mutex);
    
    for (size_t i = 0; i < npcs.size(); ++i) {
        if (!npcs[i]->isAlive()) continue;
        
        for (size_t j = i + 1; j < npcs.size(); ++j) {
            if (!npcs[j]->isAlive()) continue;
            
            if (npcs[i]->isClose(npcs[j], std::min(npcs[i]->getKillDistance(), 
                                                   npcs[j]->getKillDistance()))) {
                FightManager::get().addEvent(FightEvent{npcs[i], npcs[j]});
            }
        }
    }
}

std::vector<std::shared_ptr<NPC>> GameWorld::getNPCs() const {
    std::shared_lock<std::shared_mutex> lock(npcs_mutex);
    return npcs;
}

size_t GameWorld::getNPCsCount() const {
    std::shared_lock<std::shared_mutex> lock(npcs_mutex);
    return npcs.size();
}

void GameWorld::printMap() const {
    std::lock_guard<std::mutex> lock(print_mutex);
    
    const int CELL_WIDTH = 3;
    const int MAP_WIDTH = maxX / CELL_WIDTH + 1;
    const int MAP_HEIGHT = maxY / CELL_WIDTH + 1;
    
    std::vector<std::vector<char>> map(MAP_HEIGHT, std::vector<char>(MAP_WIDTH, ' '));
    
    {
        std::shared_lock<std::shared_mutex> npcs_lock(npcs_mutex);
        for (const auto& npc : npcs) {
            if (npc->isAlive()) {
                int gridX = npc->getX() / CELL_WIDTH;
                int gridY = npc->getY() / CELL_WIDTH;
                
                if (gridX >= 0 && gridX < MAP_WIDTH && gridY >= 0 && gridY < MAP_HEIGHT) {
                    char symbol = ' ';
                    if (dynamic_cast<Dragon*>(npc.get())) symbol = 'D';
                    else if (dynamic_cast<Bull*>(npc.get())) symbol = 'B';
                    else if (dynamic_cast<Frog*>(npc.get())) symbol = 'F';
                    
                    if (map[gridY][gridX] == ' ') {
                        map[gridY][gridX] = symbol;
                    } else {
                        map[gridY][gridX] = 'X'; 
                    }
                }
            }
        }
    }
    

    std::cout << "\nGame map\n";
    std::cout << std::string(MAP_WIDTH * 2 + 1, '-') << "\n";
    
    for (int y = 0; y < MAP_HEIGHT; ++y) {
        std::cout << "|";
        for (int x = 0; x < MAP_WIDTH; ++x) {
            std::cout << map[y][x] << "|";
        }
        std::cout << "\n";
        std::cout << std::string(MAP_WIDTH * 2 + 1, '-') << "\n";
    }
    
    std::cout << "Legend: D-Dragon, B-Bull, F-Frog, X-Multiple NPCs\n";
    std::cout << "Alive NPCs: " << getNPCsCount() << "\n";
}

void GameWorld::printSurvivors() const {
    std::lock_guard<std::mutex> lock(print_mutex);
    
    std::cout << "\nSurvivors after 30 seconds\n";
    
    std::shared_lock<std::shared_mutex> npcs_lock(npcs_mutex);
    if (npcs.empty()) {
        std::cout << "No survivors!\n";
    } else {
        std::cout << "Total survivors: " << npcs.size() << "\n";
        for (const auto& npc : npcs) {
            std::string type;
            if (dynamic_cast<Dragon*>(npc.get())) type = "Dragon";
            else if (dynamic_cast<Bull*>(npc.get())) type = "Bull";
            else if (dynamic_cast<Frog*>(npc.get())) type = "Frog";
            
            std::cout << "- " << npc->getName() << " (" << type 
                     << ") at (" << npc->getX() << ", " << npc->getY() << ")\n";
        }
    }
}

void GameWorld::clear() {
    std::unique_lock<std::shared_mutex> lock(npcs_mutex);
    npcs.clear();
}