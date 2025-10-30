#include "figures.h"
#include "rectangle.h"
#include "square.h"
#include "trapezoid.h"
#include "vector_figures.h"
#include <iostream>

int main() {
  VectorFigure v;

  std::cout << "Input vector size: ";
  int n;
  std::cin >> n;

  std::cout << "1-Square\n2-Rectangle\n3-Trapezoid\n";

  for (int i = 0; i < n; ++i) {
    char c;
    std::cin >> c;
    Figure *f = nullptr;

    if (c == '1') {
      f = new Square();
    } else if (c == '2') {
      f = new Rectangle();
    } else if (c == '3') {
      f = new Trapezoid();
    } else {
      std::cout << "Unknown figure\n";
      continue;
    }

    std::cin >> *f;
    v.push(f);
  }

  std::cout << "\nInformation about figures:\n";
  for (size_t i = 0; i < v.len(); ++i) {
    Figure *fig = v.get(i);
    Point center = fig->Center();
    std::cout << "Figure " << i << ": ";
    std::cout << "Center" << center << " ";
    std::cout << "Area" << fig->Area() << " ";
    std::cout << "Vertices" << *fig << "\n";
  }

  std::cout << "Input erase index: ";
  size_t ind;
  std::cin >> ind;
  v.erase(ind);

  std::cout << "Remaining figures: " << v.len() << std::endl;
  for (size_t i = 0; i < v.len(); ++i) {
    std::cout << v.get(i)->Area() << std::endl;
  }

  return 0;
}