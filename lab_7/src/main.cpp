#include "../include/npc_factory.h"
#include "../include/observer.h"
#include "../include/game_world.h"
#include "../include/fight_manager.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <memory>
#include <atomic>
#include <mutex>
#include <random>

std::mutex print_mutex;
std::atomic<bool> gameRunning{true};

void movementThread(GameWorld& world) {
    while (gameRunning) {
        world.moveNPCs();
        world.detectBattles();
        world.removeDeadNPCs();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void fightThread() {
    FightManager::get().processEvents();
}

void displayThread(GameWorld& world) {
    while (gameRunning) {
        world.printMap();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main() {
    const int MAX_X = 100;
    const int MAX_Y = 100;
    const int TOTAL_NPCS = 50;
    const int GAME_DURATION = 30; 
    
    std::cout << "NPC battle simulation\n";
    std::cout << "Creating " << TOTAL_NPCS << " NPCs...\n";
    
    GameWorld world(MAX_X, MAX_Y);
    auto textObserver = std::make_shared<TextObserver>();
    
    std::random_device rd;
    std::mt19937 gen(rd());
    
    for (int i = 0; i < TOTAL_NPCS; ++i) {
        std::string name = "NPC_" + std::to_string(i);
        std::uniform_int_distribution<> typeDist(0, 2);
        NpcType type = static_cast<NpcType>(typeDist(gen));
        
        std::uniform_int_distribution<> coordDist(0, MAX_X);
        int x = coordDist(gen);
        int y = coordDist(gen);
        
        auto npc = NPCFactory::createNPC(type, name, x, y);
        npc->addObserver(textObserver);
        world.addNPC(npc);
    }
    
    std::cout << "Game started! Running for " << GAME_DURATION << " seconds...\n";
    
    std::thread movement(movementThread, std::ref(world));
    std::thread fight(fightThread);
    std::thread display(displayThread, std::ref(world));
    
    std::this_thread::sleep_for(std::chrono::seconds(GAME_DURATION));
    
    gameRunning = false;
    FightManager::get().stop();

    movement.join();
    fight.join();
    display.join();

    world.printSurvivors();
    
    std::cout << "\nGame over\n";
    std::cout << "Total battles processed: " << FightManager::get().getQueueSize() << "\n";
    
    return 0;
}