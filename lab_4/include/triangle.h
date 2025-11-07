#pragma once
#include "figure.h"

template<Scalar Type>
class Triangle : public Figure<Type> {
public:
    Triangle();
    Triangle(const std::initializer_list<Point<Type>>& points);
    
    double area() const override;
    Point<Type> center() const override;
    const char* name() const override;
    bool is_valid() const override;
};

#include "triangle.ipp"