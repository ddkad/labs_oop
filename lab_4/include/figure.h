#pragma once
#include <iostream>
#include <cmath>
#include <memory>
#include <concepts>

#include "array.h"
#include "point.h"

template<Scalar T>
class Figure {
protected:
    Array<std::unique_ptr<Point<T>>> vertices;

public:
    Figure() = default;
    virtual ~Figure() = default;

    Figure(const Figure& other);
   
    virtual double area() const = 0;
    virtual Point<T> center() const = 0;
    virtual const char* name() const = 0;
    virtual bool is_valid() const = 0;

    virtual bool operator==(const Figure& other) const;
    virtual operator double() const { return area(); }

    size_t vertex_count() const;
    const Point<T>& vertex(size_t index) const;
    void set_vertex(size_t index, const Point<T>& point);
    void print(std::ostream& os) const;
    void read(std::istream& is);
    virtual double polygon_area() const;
    virtual Point<double> polygon_center() const;
    bool all_vertices_set() const;
};

template<Scalar T>
std::ostream& operator<<(std::ostream& os, const Figure<T>& fig);

template<Scalar T>
std::istream& operator>>(std::istream& is, Figure<T>& fig);

#include "figure.ipp"