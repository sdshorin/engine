#pragma once

#include "TreeObject.hpp"
#include "MeshResource.hpp"

class Mesh: public TreeObject {
	void draw_self(VisualServer* server) const override;
    // std::vector<glm::vec4> shader_info;
    // Shader sharer
    MeshResource resource;

public:
    Mesh(MeshResource& resource_in);
};


