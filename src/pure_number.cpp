#include "../include/pure_number.h"

#include <iostream>

using namespace std;

bool is_pure_number(long long number) {
  if (number < 0) {
    return false;
  }

  if (number == 0) {
    return true;
  }

  int max_dig = 9;
  while (number > 0) {
    int current_dig = number % 10;
    if (current_dig > max_dig) {
      return false;
    }
    max_dig = current_dig;
    number = number / 10;
  }
  return true;
}

bool is_pure_number(const std::string& number_to_str) {
    if (number_to_str.empty()) {
        return false;
    }

    if (number_to_str[0] == '-') {
        return false;
    }

    for (size_t i = 0; i < number_to_str.size() - 1; i++) {
        if (number_to_str[i] > number_to_str[i + 1]) {
            return false;
        }
    }
    return true;
}