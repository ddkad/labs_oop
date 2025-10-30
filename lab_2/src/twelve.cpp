#include "twelve.h"
#include <stdexcept>

void Vector::resize(size_t new_capacity) {
    if (new_capacity <= memory_size) return;
    
    unsigned char* new_v = new unsigned char[new_capacity];
    for (size_t i = 0; i < cnt_elem; ++i) {
        new_v[i] = v[i];
    }
    delete[] v;
    v = new_v;
    memory_size = new_capacity;
}

Vector::Vector() : cnt_elem(0), memory_size(1), v(new unsigned char[1]) {}

Vector::Vector(const Vector &other) 
    : cnt_elem(other.cnt_elem), memory_size(other.memory_size), v(new unsigned char[other.memory_size]) {
    for (size_t i = 0; i < cnt_elem; ++i) {
        v[i] = other.v[i];
    }
}

Vector::Vector(Vector&& other) noexcept 
    : cnt_elem(other.cnt_elem), memory_size(other.memory_size), v(other.v) {
    other.v = nullptr;
    other.cnt_elem = 0;
    other.memory_size = 0;
}

Vector::~Vector() {
    delete[] v;
}

void Vector::push(unsigned char value) {
    if (cnt_elem >= memory_size) {
        resize(memory_size * 2);
    }
    v[cnt_elem++] = value;
}

void Vector::pop() {
    if (cnt_elem > 0) {
        --cnt_elem;
    }
}

void Vector::clear() {
    cnt_elem = 0;
    memory_size = 1;
    delete[] v;
    v = new unsigned char[1];
}

unsigned char Vector::get(size_t index) const {
    if (index >= cnt_elem) {
        throw std::out_of_range("Index out of range");
    }
    return v[index];
}

void Vector::set(size_t index, unsigned char value) {
    if (index >= cnt_elem) {
        throw std::out_of_range("Index out of range");
    }
    v[index] = value;
}

void Vector::swap(size_t i, size_t j) {
    if (i >= cnt_elem || j >= cnt_elem) {
        throw std::out_of_range("Index out of range");
    }
    unsigned char temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

size_t Vector::len() const {
    return cnt_elem;
}


Twelve::Twelve() {
    nums.push(0);
}

Twelve::Twelve(const size_t &n, unsigned char t) {
    if (n == 0) {
        throw std::invalid_argument("Size cannot be zero");
    }
    
    unsigned char digit = t;
    if (t > 11) {
        digit = charToDigit(static_cast<char>(t));
    }
    if (!isValidDigit(digit)) {
        throw std::invalid_argument("Invalid digit");
    }
    
    for (size_t i = 0; i < n; ++i) {
        nums.push(digit);
    }
    removeLeadingZeros();
}

Twelve::Twelve(const std::string &t) {
    if (t.empty()) {
        throw std::invalid_argument("String cannot be empty");
    }

    for (int i = static_cast<int>(t.length()) - 1; i >= 0; --i) {
        unsigned char digit = charToDigit(t[i]);
        nums.push(digit);
    }
    removeLeadingZeros();
}

Twelve::Twelve(unsigned long long value) {
    if (value == 0) {
        nums.push(0);
        return;
    }
    
    while (value > 0) {
        nums.push(value % 12);
        value /= 12;
    }
}

Twelve::Twelve(const Twelve &other) : nums(other.nums) {}

Twelve::Twelve(Twelve &&other) noexcept : nums(std::move(other.nums)) {}

Twelve::~Twelve() noexcept {}

bool Twelve::isValidDigit(unsigned char c) const { 
    return (c <= 11); 
}

unsigned char Twelve::charToDigit(char c) const {
    if (c >= '0' && c <= '9') return c - '0';
    if (c == 'A' || c == 'a') return 10;
    if (c == 'B' || c == 'b') return 11;
    throw std::invalid_argument("Invalid digit character");
}

char Twelve::digitToChar(unsigned char d) const {
    if (d >= 0 && d <= 9) return '0' + d;
    if (d == 10) return 'A';
    if (d == 11) return 'B';
    throw std::invalid_argument("Invalid digit value");
}

void Twelve::removeLeadingZeros() {
    while (nums.len() > 1 && nums.get(nums.len() - 1) == 0) {
        nums.pop();
    }
}

int Twelve::compare(const Twelve &other) const {
    if (nums.len() != other.nums.len()) {
        return nums.len() > other.nums.len() ? 1 : -1;
    }

    for (int i = static_cast<int>(nums.len()) - 1; i >= 0; --i) {
        if (nums.get(i) != other.nums.get(i)) {
            return nums.get(i) > other.nums.get(i) ? 1 : -1;
        }
    }
    return 0;
}

size_t Twelve::getSize() const { 
    return nums.len(); 
}

std::string Twelve::toString() const {
    std::string result;
    for (int i = static_cast<int>(nums.len()) - 1; i >= 0; --i) {
        result += digitToChar(nums.get(i));
    }
    return result;
}

Twelve Twelve::sum(const Twelve &other) const {
    Twelve result;
    result.nums.clear();
    
    size_t max_size = (nums.len() > other.nums.len()) ? nums.len() : other.nums.len();
    unsigned char carry = 0;
    
    for (size_t i = 0; i < max_size || carry; ++i) {
        unsigned char sum_val = carry;
        if (i < nums.len()) sum_val += nums.get(i);
        if (i < other.nums.len()) sum_val += other.nums.get(i);
        
        carry = sum_val / 12;
        result.nums.push(sum_val % 12);
    }
    
    return result;
}

Twelve Twelve::subtract(const Twelve &other) const {
    if (this->lessThan(other)) {
        throw std::invalid_argument("Cannot subtract larger number");
    }
    
    Twelve result;
    result.nums.clear();
    
    unsigned char borrow = 0;
    for (size_t i = 0; i < nums.len(); ++i) {
        unsigned char current = nums.get(i) - borrow;
        unsigned char subtract_val = (i < other.nums.len()) ? other.nums.get(i) : 0;
        
        if (current < subtract_val) {
            current += 12;
            borrow = 1;
        } else {
            borrow = 0;
        }
        
        result.nums.push(current - subtract_val);
    }
    
    result.removeLeadingZeros();
    return result;
}

Twelve Twelve::copy() const { 
    return Twelve(*this); 
}

bool Twelve::equals(const Twelve &other) const { 
    return compare(other) == 0; 
}

bool Twelve::lessThan(const Twelve &other) const { 
    return compare(other) < 0; 
}

bool Twelve::greaterThan(const Twelve &other) const { 
    return compare(other) > 0; 
}

void Twelve::print() const {
    std::cout << "Twelve number: " << toString() << " (size: " << nums.len() << ")" << std::endl;
}