#pragma once

#include <iostream>

#include "point.h"

template<Scalar T>
Point<T>::Point() : x(T()), y(T()) {}

template<Scalar T>
Point<T>::Point(T x_, T y_) : x(x_), y(y_) {}

template<Scalar T>
std::istream& operator>>(std::istream& is, Point<T>& p) {
    is >> p.x >> p.y;
    return is;
}

template<Scalar T>
std::ostream& operator<<(std::ostream& os, const Point<T>& p) {
    os << '(' << p.x << ' ' << p.y << ')';
    return os;
}

template<Scalar T>
bool operator==(const Point<T>& a, const Point<T>& b) { return a.x == b.x && a.y == b.y; }

template<Scalar T>
bool operator!=(const Point<T>& a, const Point<T>& b) { return !(a == b); }