#pragma once
#include "defs.h"
#include <mutex>
#include <memory>
#include <string>

class NPCVisitor; 

class NPC {
protected:
    std::string name;
    NpcType type;
    int x, y;
    bool alive;
    
public:
    mutable std::mutex npc_mutex;

    NPC(NpcType t, int _x, int _y, std::string _name);
    virtual ~NPC() = default;

    NpcType get_type() const { return type; }
    std::string get_name() const;
    bool is_alive() const;
    std::pair<int, int> get_position() const;

    virtual void accept(NPCVisitor& visitor) = 0;

    void move(int max_dist, int map_w, int map_h);
    void kill();

    friend class BattleManager;
    friend class FightVisitor;
    friend class GameMap; 
    friend void print_map_state(); 
};