#include "pure_number.h"

#include <iostream>

using namespace std;

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