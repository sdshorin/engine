#include "Triangle.hpp"
#include <iostream>

namespace eng {

void Triangle::draw(VisualServer* server) const {
    std::cout << "Draw Triangle\n";
    std::vector<glm::vec4> triangle;
    // glm::vec4 vec = glm::vec4(0.0, 1.0, 0.0, 1.0);
    triangle.emplace_back(0.0, 0.0, 1.0, 1.0);
    triangle.emplace_back(1.0, 0.0, 0.0, 1.0);
    triangle.emplace_back(0.0, 1.0, 0.0, 1.0);
    // server->draw_polygon(triangle);
    
}

} // namespace eng
