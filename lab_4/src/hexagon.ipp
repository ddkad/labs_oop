template<Scalar Type>
Hexagon<Type>::Hexagon() {
    this->vertices = Array<std::unique_ptr<Point<Type>>>(6);
    for (size_t i = 0; i < 6; ++i) {
        this->vertices[i] = std::make_unique<Point<Type>>();
    }
}

template<Scalar Type>
Hexagon<Type>::Hexagon(const std::initializer_list<Point<Type>>& points) {
    this->vertices = Array<std::unique_ptr<Point<Type>>>(points.size());
    size_t i = 0;
    for (const auto& point : points) {
        this->vertices[i++] = std::make_unique<Point<Type>>(point);
    }
}

template<Scalar Type>
double Hexagon<Type>::area() const {
    return this->polygon_area();
}

template<Scalar Type>
Point<Type> Hexagon<Type>::center() const {
    return Point<Type>(this->polygon_center());
}

template<Scalar Type>
const char* Hexagon<Type>::name() const { 
    return "Hexagon"; 
}

template<Scalar Type>
bool Hexagon<Type>::is_valid() const {  
    if (!this->all_vertices_set()) return false;
    return true;
}