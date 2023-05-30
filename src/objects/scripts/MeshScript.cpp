#include "MeshScript.hpp"

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <sstream>

#include "VisualServer.h"
// #include <sstream>
#include <fstream>
#include <string>

namespace scripts {

MeshScript::MeshScript(eng::ResourceRef resource_in) : resource(resource_in) {
    std::unique_ptr<eng::ProjectionShader> p_shader = std::make_unique<eng::ProjectionShader>();
    p_shader->model = glm::mat4(1.0f);
    shader = std::move(p_shader);
    owner = NULL;
}



void MeshScript::draw(eng::VisualServer* server) const {
    eng::ProjectionShader* projection_shader = dynamic_cast<eng::ProjectionShader*>(shader.get());
    if (projection_shader) {
        projection_shader->model = owner->get_world_transform();
    }
    server->draw_mesh(resource, shader.get());
}

void MeshScript::process(float delta) {

}

}   // namespace scripts
