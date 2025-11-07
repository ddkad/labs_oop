template<Scalar T>
bool Figure<T>::operator==(const Figure<T>& other) const {
    if (vertex_count() != other.vertex_count()) return false;
    for (size_t i = 0; i < vertex_count(); ++i) {
        if (vertex(i) != other.vertex(i)) return false;
    }
    return true;
}

template<Scalar T>
void Figure<T>::set_vertex(size_t index, const Point<T>& point) {
    if (index < vertices.size()) {
        vertices[index] = std::make_unique<Point<T>>(point);
    }
}

template<Scalar T>
bool Figure<T>::all_vertices_set() const {
    for (size_t i = 0; i < vertices.size(); ++i) {
        if (!vertices[i]) return false;
    }
    return true;
}

template<Scalar T>
size_t Figure<T>::vertex_count() const { 
    return vertices.size(); 
}

template<Scalar T>
const Point<T>& Figure<T>::vertex(size_t index) const { 
    return *vertices[index]; 
}

template<Scalar T>
void Figure<T>::print(std::ostream& os) const {
    for (size_t i = 0; i < vertices.size(); ++i) {
        if (vertices[i]) {
            os << *vertices[i];
        }
        if (i + 1 < vertices.size()) os << " ";
    }
}

template<Scalar T>
void Figure<T>::read(std::istream& is) {
    for (size_t i = 0; i < vertices.size(); ++i) {
        T x, y;
        is >> x >> y;
        set_vertex(i, Point<T>(x, y));
    }
}

template<Scalar T>
double Figure<T>::polygon_area() const {
    if (vertices.size() < 3) return 0.0;
    
    double sum = 0.0;
    for (size_t i = 0; i < vertices.size(); ++i) {
        if (!vertices[i] || !vertices[(i + 1) % vertices.size()]) continue;
        const Point<T>& p1 = *vertices[i];
        const Point<T>& p2 = *vertices[(i + 1) % vertices.size()];
        sum += static_cast<double>(p1.x) * static_cast<double>(p2.y);
        sum -= static_cast<double>(p2.x) * static_cast<double>(p1.y);
    }
    return std::abs(sum) / 2.0;
}

template<Scalar T>
Point<double> Figure<T>::polygon_center() const {
    if (vertices.size() == 0) return Point<double>(0, 0);
    
    double center_x = 0.0, center_y = 0.0;
    size_t count = 0;
    for (size_t i = 0; i < vertices.size(); ++i) {
        if (vertices[i]) {
            center_x += static_cast<double>(vertices[i]->x);
            center_y += static_cast<double>(vertices[i]->y);
            count++;
        }
    }
    
    if (count == 0) return Point<double>(0, 0);
    center_x /= count;
    center_y /= count;
    return Point<double>(center_x, center_y);
}

template<Scalar T>
Figure<T>::Figure(const Figure& other) {
    vertices = Array<std::unique_ptr<Point<T>>>(other.vertices.size());
    for (size_t i = 0; i < other.vertices.size(); ++i) {
        if (other.vertices[i]) {
            vertices[i] = std::make_unique<Point<T>>(*other.vertices[i]);
        }
    }
}

template<Scalar T>
std::ostream& operator<<(std::ostream& os, const Figure<T>& fig) {
    fig.print(os);
    return os;
}

template<Scalar T>
std::istream& operator>>(std::istream& is, Figure<T>& fig) {
    fig.read(is);
    return is;
}