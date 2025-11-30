#include "../include/observer.h"

#include <chrono>
#include <iomanip>
#include <iostream>

FileObserver::FileObserver(const std::string &filename) {
  logFile.open(filename, std::ios::app);
  if (!logFile.is_open()) {
    std::cerr << "Couldn't open the log file: " << filename << std::endl;
  }
}

FileObserver::~FileObserver() {
  if (logFile.is_open()) {
    logFile.close();
  }
}

void FileObserver::onKill(const std::string &killer, const std::string &victim,
                          const std::string &reason) {
  if (logFile.is_open()) {
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);

    logFile << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S")
            << " | " << killer << " " << reason << " " << victim << std::endl;
  }
}

void FileObserver::onCombatStart() {
  if (logFile.is_open()) {
    logFile << "The beginning of the battle" << std::endl;
  }
}

void FileObserver::onCombatEnd() {
  if (logFile.is_open()) {
    logFile << "The end of the fight" << std::endl << std::endl;
  }
}

void ConsoleObserver::onKill(const std::string &killer,
                             const std::string &victim,
                             const std::string &reason) {
  std::cout << killer << " " << reason << " " << victim << "!" << std::endl;
}

void ConsoleObserver::onCombatStart() {
  std::cout << "\nThe battle begins" << std::endl;
}

void ConsoleObserver::onCombatEnd() {
  std::cout << "The battle is over\n" << std::endl;
}