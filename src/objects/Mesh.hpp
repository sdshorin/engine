#pragma once

#include "MeshResource.hpp"
#include "Shaders.hpp"
#include "Node.hpp"
#include "EmptyScript.hpp"
namespace eng {

class MeshObject: public EmptyScript {
    // std::vector<glm::vec4> shader_info;
    // Shader sharer
    MeshResource resource;
    BaseShader* shader;

   public:
    MeshObject(MeshResource& resource_in);
    MeshObject(MeshObject &&) noexcept;
    MeshObject &operator=(MeshObject &&) noexcept;


    void draw(VisualServer* server) const;
    void process(float delta);
};

}   // namespace eng
