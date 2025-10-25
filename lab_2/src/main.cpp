#include "twelve.h"
#include <iostream>
#include <string>

Twelve getTwelveInput(const std::string &prompt) {
  std::string input;
  while (true) {
    std::cout << prompt;
    std::getline(std::cin, input);
    try {
      return Twelve(input);
    } catch (const std::exception &) {
      std::cout << "Invalid input." << '\n';
    }
  }
}

int main() {
  while (true) {
    std::cout << "Enter two twelve values" << '\n';
    Twelve a = getTwelveInput("First value: ");
    Twelve b = getTwelveInput("Second value: ");

    std::cout << "\nOperations:\n";
    std::cout << "a + b = " << std::right << a.sum(b).toString() << '\n';

    try {
      std::string res = a.subtract(b).toString();
      std::cout << "a - b = " << res << '\n';
    } catch (const std::exception &) {
      std::cout << "a - b: Error" << '\n';
    }

    try {
      std::string res = b.subtract(a).toString();
      std::cout << "b - a = " << res << '\n';
    } catch (const std::exception &) {
      std::cout << "b - a: Error" << '\n';
    }

    std::cout << "a > b: " << (a.greaterThan(b) ? "true" : "false") << '\n';
    std::cout << "a < b: " << (a.lessThan(b) ? "true" : "false") << '\n';
    std::cout << "a == b: " << (a.equals(b) ? "true" : "false") << '\n';

    std::string continue_input;
    std::cout << "\nPress q to exit ";
    std::getline(std::cin, continue_input);
    if (continue_input == "q") {
      break;
    }
    std::cout << '\n';
  }

  return 0;
}