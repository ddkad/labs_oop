template<Scalar Type>
Triangle<Type>::Triangle() {
    this->vertices = Array<std::unique_ptr<Point<Type>>>(3);
    for (size_t i = 0; i < 3; ++i) {
        this->vertices[i] = std::make_unique<Point<Type>>();
    }
}

template<Scalar Type>
Triangle<Type>::Triangle(const std::initializer_list<Point<Type>>& points) {
    this->vertices = Array<std::unique_ptr<Point<Type>>>(points.size());
    size_t i = 0;
    for (const auto& point : points) {
        this->vertices[i++] = std::make_unique<Point<Type>>(point);
    }
}

template<Scalar Type>
double Triangle<Type>::area() const {
    if (!this->vertices[0] || !this->vertices[1] || !this->vertices[2]) return 0.0;
    
    const auto& a = *this->vertices[0];
    const auto& b = *this->vertices[1];
    const auto& c = *this->vertices[2];
    
    return std::abs(
        a.x * (b.y - c.y) + 
        b.x * (c.y - a.y) + 
        c.x * (a.y - b.y)
    ) / 2.0;
}

template<Scalar Type>
Point<Type> Triangle<Type>::center() const {
    if (!this->vertices[0] || !this->vertices[1] || !this->vertices[2]) {
        return Point<Type>();
    }
    
    Type center_x = (this->vertices[0]->x + this->vertices[1]->x + this->vertices[2]->x) / 3;
    Type center_y = (this->vertices[0]->y + this->vertices[1]->y + this->vertices[2]->y) / 3;
    return Point<Type>(center_x, center_y);
}

template<Scalar Type>
const char* Triangle<Type>::name() const { 
    return "Triangle"; 
}

template<Scalar Type>
bool Triangle<Type>::is_valid() const {  
    if (!this->all_vertices_set()) return false;
    return true;
}