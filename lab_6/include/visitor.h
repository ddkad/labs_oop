#ifndef VISITOR_H
#define VISITOR_H

#include "npc.h"

#include <memory>
#include <vector>

class Observer;

class Visitor {
public:
  virtual ~Visitor() = default;

  virtual void visit(Dragon &dragon) = 0;
  virtual void visit(Bull &bull) = 0;
  virtual void visit(Frog &frog) = 0;

  virtual void battle(std::vector<std::shared_ptr<NPC>>& npcs, double combatRange) = 0;
};

class CombatVisitor : public Visitor {
private:
  double combatRange;
  Observer *observer;

public:
  CombatVisitor(double range, Observer *obs);

  void visit(Dragon& dragon) override;
  void visit(Bull& bull) override;
  void visit(Frog& frog) override;

  void battle(std::vector<std::shared_ptr<NPC>>& npcs, double combatRange) override;

  void dragonVsBull(Dragon& dragon, Bull& bull);
  void bullVsFrog(Bull& bull, Frog& frog);
  void frogVsDragon(Frog& frog, Dragon& dragon);
};

#endif