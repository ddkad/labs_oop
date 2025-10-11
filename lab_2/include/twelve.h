#ifndef TWELVE_H
#define TWELVE_H

#include <exception>
#include <iostream>
#include <string>
#include <vector>

class Twelve {
private:
  std::vector<unsigned char> nums;
  size_t size;

  bool isValidDigit(unsigned char c) const;
  unsigned char charToDigit(char c) const;
  char digitToChar(unsigned char d) const;
  void removeLeadingZeros();
  int compare(const Twelve &other) const;
  void reverseVector(std::vector<unsigned char> &vector);

public:
  Twelve();
  explicit Twelve(const size_t &n, unsigned char t = 0);
  Twelve(const std::initializer_list<unsigned char> &t);
  explicit Twelve(const std::string &t);
  Twelve(const Twelve &other) = default;
  Twelve(Twelve &&other) noexcept;
  virtual ~Twelve() noexcept;

  size_t getSize() const;
  std::string toString() const;
  const std::vector<unsigned char> &getNums() const;

  Twelve sum(const Twelve &other) const;
  Twelve subtract(const Twelve &other) const;
  Twelve copy() const;

  bool equals(const Twelve &other) const;
  bool lessThan(const Twelve &other) const;
  bool greaterThan(const Twelve &other) const;

  Twelve sumAssign(const Twelve &other);
  Twelve subtractAssign(const Twelve &other);

  void print() const;
};

#endif