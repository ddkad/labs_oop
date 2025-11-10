#include <iostream>
#include <memory>

#include "array.h"
#include "figure.h"
#include "triangle.h"
#include "hexagon.h"
#include "octagon.h"

int main() {
    Array<std::shared_ptr<Figure<int>>> figure_ptr_array;
    
    auto triangle = std::make_shared<Triangle<int>>();
    figure_ptr_array.push(triangle);
    std::cout << "Array<std::shared_ptr<Figure<int>>> size: " << figure_ptr_array.size() << std::endl;

    std::cout << "Enter number of figures: ";
    int n;
    std::cin >> n;
    
    Array<std::shared_ptr<Figure<double>>> figures;
    
    std::cout << "3-Triangle\n6-Hexagon\n8-Octagon" << std::endl;
    
    for (int i = 0; i < n; ++i) {
        std::cout << "Figure " << (i + 1) << " type: ";
        char type;
        std::cin >> type;
        
        std::shared_ptr<Figure<double>> figure;
        if (type == '3') {
            figure = std::make_shared<Triangle<double>>();
        } else if (type == '6') {
            figure = std::make_shared<Hexagon<double>>();
        } else if (type == '8') {
            figure = std::make_shared<Octagon<double>>();
        } else {
            std::cout << "Invalid type" << std::endl;
            --i;
            continue;
        }
        
        std::cout << "Enter " << figure->vertex_count() << " points (x and y): ";
        std::cin >> *figure;
        
        if (!figure->is_valid()) {
            std::cout << "Invalid figure!" << std::endl;
            --i;
            continue;
        }
        
        figures.push(figure);
    }


    double total_area = 0.0;
    for (size_t i = 0; i < figures.size(); ++i) {
        auto& fig = figures[i];
        std::cout << "\nFigure " << (i + 1) << " (" << fig->name() << "):" << std::endl;
        std::cout << "Vertices: " << *fig << std::endl;
        std::cout << "Area: " << fig->area() << std::endl;
        std::cout << "Center: " << fig->center() << std::endl;
        total_area += static_cast<double>(*fig);
    }
    
    std::cout << "\nTotal area: " << total_area << std::endl;
    

     if (figures.size() > 0) {
        std::cout << "Enter index to delete: ";
        size_t index;
        std::cin >> index;
        
        if (index < figures.size()) {
            figures.erase(index);
            
            total_area = 0.0;
            for (size_t i = 0; i < figures.size(); ++i) {
                total_area += static_cast<double>(*figures[i]);
            }
            std::cout << "Total area after deletion: " << total_area << std::endl;
            std::cout << "Remaining figures count: " << figures.size() << std::endl;
        }
    }
    
    return 0;
}
