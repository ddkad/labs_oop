#include "../include/npc.h"
#include "../include/visitor.h"

#include <cmath>
#include <iostream>

NPC::NPC(const std::string &name, int x, int y) : name(name), x(x), y(y) {}

std::string NPC::getName() const { return name; }
int NPC::getX() const { return x; }
int NPC::getY() const { return y; }

double NPC::distanceTo(const NPC &other) const {
  return std::sqrt(std::pow(x - other.x, 2) + std::pow(y - other.y, 2));
}

bool NPC::isValidPosition() const {
  return x >= 0 && x <= 500 && y >= 0 && y <= 500;
}

Dragon::Dragon(const std::string &name, int x, int y) : NPC(name, x, y) {}

void Dragon::accept(Visitor &visitor) { visitor.visit(*this); }

std::string Dragon::getType() const { return "Dragon"; }

Bull::Bull(const std::string &name, int x, int y) : NPC(name, x, y) {}

void Bull::accept(Visitor &visitor) { visitor.visit(*this); }

std::string Bull::getType() const { return "Bull"; }

Frog::Frog(const std::string &name, int x, int y) : NPC(name, x, y) {}

void Frog::accept(Visitor &visitor) { visitor.visit(*this); }

std::string Frog::getType() const { return "Frog"; }