#pragma once

#include "TreeObject.hpp"
#include "MeshResource.hpp"
#include "Shaders.hpp"

class Mesh: public TreeObject {
	void draw_self(VisualServer* server) const override;
    // std::vector<glm::vec4> shader_info;
    // Shader sharer
    MeshResource resource;
    BaseShader* shader;

public:
    Mesh(MeshResource& resource_in);
};


