#ifndef NPC_H
#define NPC_H

#include <memory>
#include <mutex>
#include <string>
#include <vector>

class Visitor;
class IFightObserver;

enum class NpcType {
    Dragon,
    Bull,
    Frog
};

class NPC : public std::enable_shared_from_this<NPC> {  
protected:
    std::string name;
    int x, y;
    bool alive;
    mutable std::mutex mtx;
    std::vector<std::shared_ptr<IFightObserver>> observers;
    
public:
    NPC(const std::string& name, int x, int y);
    virtual ~NPC() = default;
    
    std::string getName() const;
    int getX() const;
    int getY() const;
    bool isAlive() const;
    
    void move(int dx, int dy, int maxX, int maxY);
    double distanceTo(const std::shared_ptr<NPC>& other) const;
    bool isClose(const std::shared_ptr<NPC>& other, int distance) const;
    void mustDie();
    
    virtual bool accept(std::shared_ptr<NPC> visitor) = 0;
    virtual bool fight(std::shared_ptr<NPC> other) = 0;
    virtual bool fight(std::shared_ptr<class Dragon> other) = 0;
    virtual bool fight(std::shared_ptr<class Bull> other) = 0;
    virtual bool fight(std::shared_ptr<class Frog> other) = 0;
    
    void addObserver(std::shared_ptr<IFightObserver> observer);
    void removeObserver(std::shared_ptr<IFightObserver> observer);
    void fightNotify(std::shared_ptr<NPC> defender, bool win);
    
    virtual int getMoveDistance() const = 0;
    virtual int getKillDistance() const = 0;
    
    virtual void attack(int& attackPower) const = 0;
    virtual void defend(int& defensePower) const = 0;
};

class Dragon : public NPC {
public:
    Dragon(const std::string& name, int x, int y);
    bool accept(std::shared_ptr<NPC> visitor) override;
    bool fight(std::shared_ptr<NPC> other) override;
    bool fight(std::shared_ptr<Dragon> other) override;
    bool fight(std::shared_ptr<Bull> other) override;
    bool fight(std::shared_ptr<Frog> other) override;
    
    int getMoveDistance() const override { return 50; }
    int getKillDistance() const override { return 30; }
    
    void attack(int& attackPower) const override;
    void defend(int& defensePower) const override;
};

class Bull : public NPC {
public:
    Bull(const std::string& name, int x, int y);
    bool accept(std::shared_ptr<NPC> visitor) override;
    bool fight(std::shared_ptr<NPC> other) override;
    bool fight(std::shared_ptr<Dragon> other) override;
    bool fight(std::shared_ptr<Bull> other) override;
    bool fight(std::shared_ptr<Frog> other) override;
    
    int getMoveDistance() const override { return 30; }
    int getKillDistance() const override { return 10; }
    
    void attack(int& attackPower) const override;
    void defend(int& defensePower) const override;
};

class Frog : public NPC {
public:
    Frog(const std::string& name, int x, int y);
    bool accept(std::shared_ptr<NPC> visitor) override;
    bool fight(std::shared_ptr<NPC> other) override;
    bool fight(std::shared_ptr<Dragon> other) override;
    bool fight(std::shared_ptr<Bull> other) override;
    bool fight(std::shared_ptr<Frog> other) override;
    
    int getMoveDistance() const override { return 1; }
    int getKillDistance() const override { return 10; }
    
    void attack(int& attackPower) const override;
    void defend(int& defensePower) const override;
};

#endif 