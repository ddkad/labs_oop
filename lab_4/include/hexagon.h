#pragma once
#include "figure.h"

template<Scalar Type>
class Hexagon : public Figure<Type> {
public:
    Hexagon();
    Hexagon(const std::initializer_list<Point<Type>>& points);
    
    double area() const override;
    Point<Type> center() const override;
    const char* name() const override;
    bool is_valid() const override;
};

#include "hexagon.ipp"