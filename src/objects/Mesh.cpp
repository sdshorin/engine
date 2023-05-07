#include "Mesh.hpp"

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <sstream>

#include "VisualServer.h"
// #include <sstream>
#include <fstream>
#include <string>

namespace eng {

MeshObject::MeshObject(MeshResource& resource_in) : resource(resource_in) {
    ProjectionShader* p_shader = new ProjectionShader;
    p_shader->model = glm::mat4(1.0f);
    shader = p_shader;
    owner = NULL;
}

MeshObject::MeshObject(MeshObject&& other) noexcept: resource(std::move(other.resource))  {
    shader = std::move(other.shader);
    owner = other.owner;
}


MeshObject &MeshObject::operator=(MeshObject &&other) noexcept {
    resource = std::move(other.resource);
    shader = std::move(other.shader);
    owner = other.owner;

}

void MeshObject::set_owner(eng::Node* owner_p) {
    owner = owner_p;
}

void MeshObject::draw(VisualServer* server) const {
    ProjectionShader* projection_shader = dynamic_cast<ProjectionShader*>(shader);
    if (projection_shader) {
        projection_shader->model = owner->get_world_transform();
    }
    server->draw_mesh(resource.GetStorage(), shader);
}

void MeshObject::process(float delta) {

}

}   // namespace eng
