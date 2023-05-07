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
    AnyScript script;
    glm::mat4 transform;

    void set_parent(Node* new_parent);

   public:
    Node(AnyScript script);

    ~Node();
    Node &operator=(Node &) noexcept = delete;
    Node &operator=(Node &&) noexcept = delete;
    Node(Node &&) noexcept = delete;
    Node(const Node &) noexcept = delete;
    void add_child(std::unique_ptr<Node> node);

    // move(glm::mat4 ) ?????
    void draw_notification(VisualServer* server) const;
    void process_notification(float delta);
    glm::mat4 get_world_transform() const;

    // void move(const glm::vec3& move_transform);
    // virtual void process(float delta);
    // virtual void draw(VisualServer* server) const;
};

}   // namespace eng
