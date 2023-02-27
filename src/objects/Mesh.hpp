#pragma once

#include "MeshResource.hpp"
#include "Shaders.hpp"
#include "TreeObject.hpp"

namespace eng {

class MeshObject : public TreeObject {
    void draw(VisualServer* server) const override;
    // std::vector<glm::vec4> shader_info;
    // Shader sharer
    MeshResource resource;
    BaseShader* shader;

   public:
    MeshObject(MeshResource& resource_in);
};

}   // namespace eng
