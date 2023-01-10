
#include "TreeObject.hpp"


void TreeObject::draw(VisualServer* server) const {
    for (const TreeObject* child: childrens) {
        child->draw(server);
    }
    draw_self(server);
}
void TreeObject::draw_self(VisualServer* server) const {

}


void TreeObject::add_child(TreeObject* node) {
    childrens.push_back(node);
}




