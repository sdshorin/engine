#pragma once

#include "TreeObject.hpp"

class Mesh: public TreeObject {
	void draw_self(VisualServer* server) const override;
    // std::vector<glm::vec4> shader_info;
    // Shader sharer

public:
    std::vector<glm::vec4> triangles;
    void load_obj_file(std::string path);

};