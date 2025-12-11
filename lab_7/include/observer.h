#ifndef OBSERVER_H
#define OBSERVER_H

#include <memory>
#include <string>

class NPC;

class IFightObserver {
public:
    virtual ~IFightObserver() = default;
    virtual void onFight(const std::shared_ptr<NPC> attacker, 
                        const std::shared_ptr<NPC> defender, 
                        bool win) = 0;
};

class TextObserver : public IFightObserver {
public:
    void onFight(const std::shared_ptr<NPC> attacker, 
                const std::shared_ptr<NPC> defender, 
                bool win) override;
};

#endif