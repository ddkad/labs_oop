#pragma once

#include <string>
#include <memory>
#include <fstream>
#include <mutex>

class NPC; 

class IFightObserver {
public:
    virtual ~IFightObserver() = default;
    virtual void on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win) = 0;
};

class ConsoleObserver : public IFightObserver {
    std::mutex mtx;
public:
    void on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win) override;
};

class FileObserver : public IFightObserver {
    std::ofstream file;
    std::mutex mtx;
public:
    FileObserver();
    ~FileObserver();
    void on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win) override;
};