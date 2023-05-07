#pragma once

#include "MeshResource.hpp"
#include "Shaders.hpp"
#include "Node.hpp"
namespace eng {

class MeshObject {
    // std::vector<glm::vec4> shader_info;
    // Shader sharer
    MeshResource resource;
    BaseShader* shader;
    Node* owner;

   public:
    MeshObject(MeshResource& resource_in);
    MeshObject(MeshObject &&) noexcept;
    MeshObject &operator=(MeshObject &&) noexcept;


    void draw(VisualServer* server) const;
    void process(float delta);
    void set_owner(eng::Node* owner);
};

}   // namespace eng
