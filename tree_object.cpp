#include "engine.hpp"



void TreeObject::draw(VisualServer* server) const {
    for (const TreeObject* child: childrens) {
        child->draw(server);
    }
    draw_self(server);
}
void TreeObject::draw_self(VisualServer* server) const {

}


void Triangle::draw_self(VisualServer* server) const {
    std::cout << "Draw Triangle\n";
    std::vector<glm::vec4> triangle;
    // glm::vec4 vec = glm::vec4(0.0, 1.0, 0.0, 1.0);
    triangle.emplace_back(0.0, 0.0, 1.0, 1.0);
    triangle.emplace_back(1.0, 0.0, 0.0, 1.0);
    triangle.emplace_back(0.0, 1.0, 0.0, 1.0);
    server->draw_polygon(triangle);
    
}

void TreeObject::add_child(TreeObject* node) {
    childrens.push_back(node);
}




