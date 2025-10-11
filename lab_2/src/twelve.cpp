#include "twelve.h"

void Twelve::reverseVector(std::vector<unsigned char> &vector) {
  size_t left = 0;
  size_t right = vector.size() - 1;
  while (left < right) {
    unsigned char temp = vector[left];
    vector[left] = vector[right];
    vector[right] = temp;
    left++;
    right--;
  }
}

Twelve::Twelve() : size(1) { nums.push_back(0); }

Twelve::Twelve(const size_t &n, unsigned char t) : size(n) {
  if (n == 0) {
    throw std::exception();
  }
  unsigned char digit = t;
  if (t > 11) {
    digit = charToDigit(static_cast<char>(t));
  }
  if (!isValidDigit(digit)) {
    throw std::exception();
  }
  nums = std::vector<unsigned char>(n, digit);
  removeLeadingZeros();
}

Twelve::Twelve(const std::initializer_list<unsigned char> &t) {
  if (t.size() == 0) {
    throw std::exception();
  }

  for (auto i = t.begin(); i != t.end(); ++i) {
    unsigned char digit = *i;
    if (digit > 11) {
      digit = charToDigit(static_cast<char>(digit));
    }
    if (!isValidDigit(digit)) {
      throw std::exception();
    }
    nums.push_back(digit);
  }
  size = nums.size();
  reverseVector(nums);
  removeLeadingZeros();
}

Twelve::Twelve(const std::string &t) {
  if (t.empty()) {
    throw std::exception();
  }

  for (int i = static_cast<int>(t.length()) - 1; i >= 0; --i) {
    unsigned char digit = charToDigit(t[i]);
    nums.push_back(digit);
  }
  size = nums.size();
  removeLeadingZeros();
}

Twelve::Twelve(Twelve &&other) noexcept
    : nums(std::move(other.nums)), size(other.size) {
  other.size = 0;
}

Twelve::~Twelve() noexcept {}

bool Twelve::isValidDigit(unsigned char c) const { return (c >= 0 && c <= 11); }

unsigned char Twelve::charToDigit(char c) const {
  if (c >= '0' && c <= '9')
    return c - '0';
  if (c == 'A' || c == 'a')
    return 10;
  if (c == 'B' || c == 'b')
    return 11;
  throw std::exception();
}

char Twelve::digitToChar(unsigned char d) const {
  if (d >= 0 && d <= 9)
    return '0' + d;
  if (d == 10)
    return 'A';
  if (d == 11)
    return 'B';
  throw std::exception();
}

void Twelve::removeLeadingZeros() {
  while (size > 1 && nums[size - 1] == 0) {
    nums.pop_back();
    size--;
  }
}

int Twelve::compare(const Twelve &other) const {
  if (size != other.size) {
    return size > other.size ? 1 : -1;
  }

  for (int i = static_cast<int>(size) - 1; i >= 0; --i) {
    if (nums[i] != other.nums[i]) {
      return nums[i] > other.nums[i] ? 1 : -1;
    }
  }
  return 0;
}

size_t Twelve::getSize() const { return size; }

std::string Twelve::toString() const {
  std::string result;
  for (int i = static_cast<int>(size) - 1; i >= 0; --i) {
    result += digitToChar(nums[i]);
  }
  return result;
}

const std::vector<unsigned char> &Twelve::getNums() const { return nums; }

Twelve Twelve::sum(const Twelve &other) const {
  Twelve result = *this;
  return result.sumAssign(other);
}

Twelve Twelve::subtract(const Twelve &other) const {
  if (this->lessThan(other)) {
    throw std::exception();
  }
  Twelve result = *this;
  return result.subtractAssign(other);
}

Twelve Twelve::copy() const { return Twelve(*this); }

bool Twelve::equals(const Twelve &other) const { return compare(other) == 0; }

bool Twelve::lessThan(const Twelve &other) const { return compare(other) < 0; }

bool Twelve::greaterThan(const Twelve &other) const {
  return compare(other) > 0;
}

Twelve Twelve::sumAssign(const Twelve &other) {
  size_t mx_size = (size > other.size) ? size : other.size;
  std::vector<unsigned char> resultDigits;
  unsigned char res = 0;
  for (size_t i = 0; i < mx_size || res; ++i) {
    unsigned char sum = res;
    if (i < size)
      sum += nums[i];
    if (i < other.size)
      sum += other.nums[i];
    res = sum / 12;
    resultDigits.push_back(sum % 12);
  }
  nums = resultDigits;
  size = nums.size();
  return *this;
}

Twelve Twelve::subtractAssign(const Twelve &other) {
  std::vector<unsigned char> resultDigits;
  unsigned char zaem = 0;

  for (size_t i = 0; i < size; ++i) {
    unsigned char now_num = nums[i] - zaem;
    unsigned char vitchitaemoe = (i < other.size) ? other.nums[i] : 0;
    if (now_num < vitchitaemoe) {
      now_num += 12;
      zaem = 1;
    } else {
      zaem = 0;
    }
    resultDigits.push_back(now_num - vitchitaemoe);
  }
  nums = resultDigits;
  size = nums.size();
  removeLeadingZeros();
  return *this;
}

void Twelve::print() const {
  std::cout << "Twelve number: " << toString() << " (size: " << size << ")"
            << std::endl;
  std::cout << "nums: ";
  for (int i = static_cast<int>(size) - 1; i >= 0; --i) {
    std::cout << static_cast<int>(nums[i]) << " ";
  }
  std::cout << std::endl;
}