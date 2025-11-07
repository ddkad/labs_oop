template<Scalar Type>
Octagon<Type>::Octagon() {
    this->vertices = Array<std::unique_ptr<Point<Type>>>(8);
    for (size_t i = 0; i < 8; ++i) {
        this->vertices[i] = std::make_unique<Point<Type>>();
    }
}

template<Scalar Type>
Octagon<Type>::Octagon(const std::initializer_list<Point<Type>>& points) {
    this->vertices = Array<std::unique_ptr<Point<Type>>>(points.size());
    size_t i = 0;
    for (const auto& point : points) {
        this->vertices[i++] = std::make_unique<Point<Type>>(point);
    }
}

template<Scalar Type>
double Octagon<Type>::area() const {
    return this->polygon_area();
}

template<Scalar Type>
Point<Type> Octagon<Type>::center() const {
    return Point<Type>(this->polygon_center());
}

template<Scalar Type>
const char* Octagon<Type>::name() const { 
    return "Octagon"; 
}

template<Scalar Type>
bool Octagon<Type>::is_valid() const {  
    if (!this->all_vertices_set()) return false;
    return true;
}