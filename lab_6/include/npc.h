#ifndef NPC_H
#define NPC_H

#include <memory>
#include <string>

class NPC {
protected:
  std::string name;
  int x, y;

public:
  NPC(const std::string &name, int x, int y);
  virtual ~NPC() = default;

  std::string getName() const;
  int getX() const;
  int getY() const;

  virtual void accept(class Visitor &visitor) = 0;
  virtual std::string getType() const = 0;
  double distanceTo(const NPC &other) const;
  bool isValidPosition() const;
};

class Dragon : public NPC {
public:
  Dragon(const std::string &name, int x, int y);
  void accept(Visitor &visitor) override;
  std::string getType() const override;
};

class Bull : public NPC {
public:
  Bull(const std::string &name, int x, int y);
  void accept(Visitor &visitor) override;
  std::string getType() const override;
};

class Frog : public NPC {
public:
  Frog(const std::string &name, int x, int y);
  void accept(Visitor &visitor) override;
  std::string getType() const override;
};

#endif