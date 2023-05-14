#pragma once

#include "MeshResource.hpp"
#include "Shaders.hpp"
#include "Node.hpp"
#include "EmptyScript.hpp"
namespace eng {

class MeshScript: public EmptyScript {
    // std::vector<glm::vec4> shader_info;
    // Shader sharer
    MeshResource resource;
    BaseShader* shader;

   public:
    MeshScript(MeshResource& resource_in);
    MeshScript(MeshScript &&) noexcept;
    MeshScript &operator=(MeshScript &&) noexcept;


    void draw(VisualServer* server) const;
    void process(float delta);
};

}   // namespace eng
