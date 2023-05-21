#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <AnyScript.hpp>

#include "VisualServer.h"

#include <memory>

namespace eng {

class Node {
private:
    std::vector<std::unique_ptr<Node> > childrens;
    Node* parent;

    void set_parent(Node* new_parent);

   public:
    glm::mat4 transform;
    AnyScript script;
    Node(AnyScript script);

    ~Node();
    Node &operator=(Node &) noexcept = delete;
    Node &operator=(Node &&) noexcept = delete;
    Node(Node &&) noexcept = delete;
    Node(const Node &) noexcept = delete;
    void add_child(std::unique_ptr<Node> node);

    void move(const glm::vec3& offset);
    void scale(const glm::vec3& scale);
    void draw_notification(VisualServer* server) const;
    void process_notification(float delta);
    glm::mat4 get_world_transform() const;

};

}   // namespace eng
