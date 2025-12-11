#ifndef COROUTINE_NPC_H
#define COROUTINE_NPC_H

#include <memory>
#include "npc.h"
#include "game_world.h"

class NPCBehavior {
public:
    virtual ~NPCBehavior() = default;
    virtual void resume() = 0;
    virtual bool done() const = 0;
};

class SimpleNPCBehavior : public NPCBehavior {
private:
    std::shared_ptr<NPC> npc;
    GameWorld& world;
    bool isDone;
    
public:
    SimpleNPCBehavior(std::shared_ptr<NPC> npc, GameWorld& world);
    void resume() override;
    bool done() const override { return isDone; }
};

#endif