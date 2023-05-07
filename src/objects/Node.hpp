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

    void set_parent(Node* new_parent);

   protected:
    glm::mat4 transform;

   public:
    Node(AnyScript script);
    ~Node();
    // TreeObject &operator=(TreeObject &&) noexcept = default;
    // TreeObject(const TreeObject &) noexcept = default;
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
