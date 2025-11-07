#pragma once
#include <iostream>
#include <concepts>

template<typename T>
concept Scalar = std::is_scalar_v<T>;

template<Scalar T> 
class Point {
public:
    T x, y;

    Point();
    Point(T x, T y);
    
    friend std::istream& operator>> <>(std::istream&, Point<T>&);
    friend std::ostream& operator<< <>(std::ostream&, const Point<T>&);
    friend bool operator== <>(const Point<T>&, const Point<T>&);
    friend bool operator!= <>(const Point<T>&, const Point<T>&);
};

template<Scalar T>
std::istream& operator>>(std::istream&, Point<T>&);

template<Scalar T>
std::ostream& operator<<(std::ostream&, const Point<T>&);

template<Scalar T>
bool operator==(const Point<T>&, const Point<T>&);

template<Scalar T>
bool operator!=(const Point<T>&, const Point<T>&);


#include <point.ipp>