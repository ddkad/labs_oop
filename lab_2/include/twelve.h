#ifndef TWELVE_H
#define TWELVE_H

#include <exception>
#include <iostream>
#include <string>

class Vector {
private:
    size_t cnt_elem;
    size_t memory_size;
    unsigned char *v;
    void resize(size_t sz);

public:
    void push(unsigned char);
    void pop();
    void clear();

    unsigned char get(size_t) const;
    void set(size_t, unsigned char);

    void swap(size_t, size_t);

    size_t len() const;

    Vector(Vector&&) noexcept;
    Vector(const Vector &);
    Vector();
    ~Vector();
};

class Twelve {
private:
  Vector nums;

  bool isValidDigit(unsigned char c) const;
  unsigned char charToDigit(char c) const;
  char digitToChar(unsigned char d) const;
  void removeLeadingZeros();
  int compare(const Twelve &other) const;

public:
  Twelve();
  explicit Twelve(const size_t &n, unsigned char t = 0);
  explicit Twelve(const std::string &t);
  Twelve(unsigned long long value);
  Twelve(const Twelve &other);
  Twelve(Twelve &&other) noexcept;
  virtual ~Twelve() noexcept;

  size_t getSize() const;
  std::string toString() const;
  
  Twelve sum(const Twelve &other) const;
  Twelve subtract(const Twelve &other) const;
  Twelve copy() const;

  bool equals(const Twelve &other) const;
  bool lessThan(const Twelve &other) const;
  bool greaterThan(const Twelve &other) const;

  void print() const;
};

#endif