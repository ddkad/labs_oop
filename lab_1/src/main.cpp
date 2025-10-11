#include <iostream>

#include <string>

#include "../include/pure_number.h"

using namespace std;
int main() {
    string number;
    while (true) {
        cout << "Enter a number or 'q' to exit: ";
        
        if (!(cin >> number) || number == "q") {
        break;
        }

        bool is_pure = is_pure_number(number);
        cout << number << " - " << (is_pure ? "pure number" : "not pure number") << endl;
  }
  return 0;
}