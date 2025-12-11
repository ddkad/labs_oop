#include "../include/npc.h"
#include "../include/observer.h"
#include <random>
#include <iostream>
#include <cmath>

extern std::mutex print_mutex;

NPC::NPC(const std::string& name, int x, int y) 
    : name(name), x(x), y(y), alive(true) {}

std::string NPC::getName() const {
    std::lock_guard<std::mutex> lock(mtx);
    return name;
}

int NPC::getX() const {
    std::lock_guard<std::mutex> lock(mtx);
    return x;
}

int NPC::getY() const {
    std::lock_guard<std::mutex> lock(mtx);
    return y;
}

bool NPC::isAlive() const {
    std::lock_guard<std::mutex> lock(mtx);
    return alive;
}

void NPC::move(int dx, int dy, int maxX, int maxY) {
    std::lock_guard<std::mutex> lock(mtx);
    if (!alive) return;
    
    int newX = x + dx;
    int newY = y + dy;
    
    if (newX < 0) newX = 0;
    if (newY < 0) newY = 0;
    if (newX > maxX) newX = maxX;
    if (newY > maxY) newY = maxY;
    
    x = newX;
    y = newY;
}

double NPC::distanceTo(const std::shared_ptr<NPC>& other) const {
    std::lock_guard<std::mutex> lock(mtx);
    if (!other) return std::numeric_limits<double>::max();
    
    auto otherLock = std::unique_lock(other->mtx, std::try_to_lock);
    if (!otherLock) return std::numeric_limits<double>::max();
    
    return std::sqrt(std::pow(x - other->x, 2) + std::pow(y - other->y, 2));
}

bool NPC::isClose(const std::shared_ptr<NPC>& other, int distance) const {
    return distanceTo(other) <= distance;
}

void NPC::mustDie() {
    std::lock_guard<std::mutex> lock(mtx);
    alive = false;
}

void NPC::addObserver(std::shared_ptr<IFightObserver> observer) {
    std::lock_guard<std::mutex> lock(mtx);
    observers.push_back(observer);
}

void NPC::removeObserver(std::shared_ptr<IFightObserver> observer) {
    std::lock_guard<std::mutex> lock(mtx);
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void NPC::fightNotify(std::shared_ptr<NPC> defender, bool win) {
    std::vector<std::shared_ptr<IFightObserver>> currentObservers;
    {
        std::lock_guard<std::mutex> lock(mtx);
        currentObservers = observers;
    }
    
    for (auto& observer : currentObservers) {
        observer->onFight(shared_from_this(), defender, win);
    }
}


Dragon::Dragon(const std::string& name, int x, int y) : NPC(name, x, y) {}

bool Dragon::accept(std::shared_ptr<NPC> visitor) {
    return visitor->fight(std::static_pointer_cast<Dragon>(shared_from_this()));
}

bool Dragon::fight(std::shared_ptr<NPC> other) {
    return other->fight(std::static_pointer_cast<Dragon>(shared_from_this()));
}

bool Dragon::fight(std::shared_ptr<Dragon> other) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 6);
    
    int attackPower = dist(gen);
    int defensePower = dist(gen);
    
    bool win = attackPower > defensePower;
    fightNotify(other, win);
    return win;
}

bool Dragon::fight(std::shared_ptr<Bull> other) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 6);
    
    int attackPower = dist(gen);
    int defensePower = dist(gen);
    
    bool win = attackPower > defensePower;
    fightNotify(other, win);
    return win;
}

bool Dragon::fight(std::shared_ptr<Frog> other) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 6);
    
    int attackPower = dist(gen);
    int defensePower = dist(gen);
    
    bool win = attackPower > defensePower;
    fightNotify(other, win);
    return win;
}

void Dragon::attack(int& attackPower) const {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 6);
    attackPower = dist(gen);
}

void Dragon::defend(int& defensePower) const {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 6);
    defensePower = dist(gen);
}


Bull::Bull(const std::string& name, int x, int y) : NPC(name, x, y) {}

bool Bull::accept(std::shared_ptr<NPC> visitor) {
    return visitor->fight(std::static_pointer_cast<Bull>(shared_from_this()));
}

bool Bull::fight(std::shared_ptr<NPC> other) {
    return other->fight(std::static_pointer_cast<Bull>(shared_from_this()));
}

bool Bull::fight(std::shared_ptr<Dragon> other) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 6);
    
    int attackPower = dist(gen);
    int defensePower = dist(gen);
    
    bool win = attackPower > defensePower;
    fightNotify(other, win);
    return win;
}

bool Bull::fight(std::shared_ptr<Bull> other) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 6);
    
    int attackPower = dist(gen);
    int defensePower = dist(gen);
    
    bool win = attackPower > defensePower;
    fightNotify(other, win);
    return win;
}

bool Bull::fight(std::shared_ptr<Frog> other) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 6);
    
    int attackPower = dist(gen);
    int defensePower = dist(gen);
    
    bool win = attackPower > defensePower;
    fightNotify(other, win);
    return win;
}

void Bull::attack(int& attackPower) const {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 6);
    attackPower = dist(gen);
}

void Bull::defend(int& defensePower) const {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 6);
    defensePower = dist(gen);
}


Frog::Frog(const std::string& name, int x, int y) : NPC(name, x, y) {}

bool Frog::accept(std::shared_ptr<NPC> visitor) {
    return visitor->fight(std::static_pointer_cast<Frog>(shared_from_this()));
}

bool Frog::fight(std::shared_ptr<NPC> other) {
    return other->fight(std::static_pointer_cast<Frog>(shared_from_this()));
}

bool Frog::fight(std::shared_ptr<Dragon> other) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 6);
    
    int attackPower = dist(gen);
    int defensePower = dist(gen);
    
    bool win = attackPower > defensePower;
    fightNotify(other, win);
    return win;
}

bool Frog::fight(std::shared_ptr<Bull> other) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 6);
    
    int attackPower = dist(gen);
    int defensePower = dist(gen);
    
    bool win = attackPower > defensePower;
    fightNotify(other, win);
    return win;
}

bool Frog::fight(std::shared_ptr<Frog> other) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 6);
    
    int attackPower = dist(gen);
    int defensePower = dist(gen);
    
    bool win = attackPower > defensePower;
    fightNotify(other, win);
    return win;
}

void Frog::attack(int& attackPower) const {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 6);
    attackPower = dist(gen);
}

void Frog::defend(int& defensePower) const {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 6);
    defensePower = dist(gen);
}