#include "twelve.h"
#include <iomanip>
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
      std::cout << "a - b = " << std::right << res << '\n';
    } catch (const std::exception &) {
      std::cout << "a - b: " << std::right << "Error" << '\n';
    }

    try {
      std::string res = b.subtract(a).toString();
      std::cout << "b - a = " << std::right << res << '\n';
    } catch (const std::exception &) {
      std::cout << "b - a: " << std::right << "Error" << '\n';
    }

    std::cout << "a > b: " << std::right
              << (a.greaterThan(b) ? "true" : "false") << '\n';
    std::cout << "a < b: " << std::right << (a.lessThan(b) ? "true" : "false")
              << '\n';
    std::cout << "a == b: " << std::right << (a.equals(b) ? "true" : "false")
              << '\n';

    Twelve c = a;
    c.sumAssign(b);
    std::cout << "c = a, c += b, c = " << std::right << c.toString() << '\n';
    Twelve d = a;
    try {
      d.subtractAssign(b);
      std::cout << "d = a, d -= b, d = " << std::right << d.toString() << '\n';
    } catch (const std::exception &) {
      std::cout << "d = a, d -= b: " << std::right << "Error" << '\n';
    }

    std::cout << "Size of a: " << std::right << a.getSize() << '\n';
    std::cout << "Size of b: " << std::right << b.getSize() << '\n';

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