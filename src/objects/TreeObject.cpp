
#include "TreeObject.hpp"
#include <stdexcept>

TreeObject::TreeObject() {
    transform = glm::mat4(1.0f);
    parent = NULL;
}

void TreeObject::draw_notification(VisualServer* server) const {
    for (const TreeObject* child: childrens) {
        child->draw_notification(server);
    }
    draw(server);
}

void TreeObject::process_notification(float delta) {
    for (TreeObject* child: childrens) {
        child->process_notification(delta);
    }
    process(delta);
}

void TreeObject::draw(VisualServer* server) const {

}

void TreeObject::move(const glm::vec3& direction) {
    glm::mat4 translation(1.0f);
    translation[3][0] = direction.x;
    translation[3][1] = direction.y;
    translation[3][2] = direction.z;
    transform = translation * transform;
}

glm::mat4 TreeObject::get_world_transform() const {
    if (parent) {
        return parent->get_world_transform() * transform;
    }
    return transform;
}


void TreeObject::process(float delta) {
    
}

void TreeObject::add_child(TreeObject* node) {
    if (node->parent) {
        throw std::invalid_argument("This node already have parent");
    }
    childrens.push_back(node);
    node->parent = this;
}




