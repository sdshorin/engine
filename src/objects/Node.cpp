
#include "Node.hpp"

#include <iostream>
#include <stdexcept>

namespace eng {

Node::Node(AnyScript script_p): script(std::move(script_p)) {
    script.set_owner(this);
    transform = glm::mat4(1.0f);
    parent = NULL;
}


Node::~Node() {
    parent = NULL;
    std::cout << "~Node" << std::endl;
}

// Node &Node::operator=(Node &&from) noexcept {
//     childrens = std::move(from.childrens);
//     parent = from.parent;
//     transform = from.transform;
// }

void Node::draw_notification(VisualServer* server) const {
    for (const std::unique_ptr<Node>& child : childrens) {
        child->draw_notification(server);
    }
    script.draw(server);
}

void Node::process_notification(float delta) {
    for (std::unique_ptr<Node>& child : childrens) {
        child->process_notification(delta);
    }
    script.process(delta);
}

// void Node::draw(VisualServer* server) const {
// }

void Node::move(const glm::vec3& direction) {
    glm::mat4 translation(1.0f);
    translation[3][0] = direction.x;
    translation[3][1] = direction.y;
    translation[3][2] = direction.z;
    transform = translation * transform;
}

glm::mat4 Node::get_world_transform() const {
    if (parent) {
        return parent->get_world_transform() * transform;
    }
    return transform;
}

// void Node::process(float delta) {
// }

void Node::set_parent(Node* new_parent) {
    parent = new_parent;
}

void Node::add_child(std::unique_ptr<Node> node) {
    if (node->parent) {
        throw std::invalid_argument("This node already have parent");
    }
    node->set_parent(this);
    childrens.push_back(std::move(node));
}

}   // namespace eng
