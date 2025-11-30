#ifndef OBSERVER_H
#define OBSERVER_H

#include <fstream>
#include <string>

class Observer {
public:
  virtual ~Observer() = default;
  virtual void onKill(const std::string &killer, const std::string &victim,
                      const std::string &reason) = 0;
  virtual void onCombatStart() = 0;
  virtual void onCombatEnd() = 0;
};

class FileObserver : public Observer {
private:
  std::ofstream logFile;

public:
  FileObserver(const std::string &filename);
  ~FileObserver();

  void onKill(const std::string &killer, const std::string &victim,
              const std::string &reason) override;
  void onCombatStart() override;
  void onCombatEnd() override;
};

class ConsoleObserver : public Observer {
public:
  void onKill(const std::string &killer, const std::string &victim,
              const std::string &reason) override;
  void onCombatStart() override;
  void onCombatEnd() override;
};

#endif