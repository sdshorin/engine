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
}

void MeshObject::draw(VisualServer* server) const {
    ProjectionShader* projection_shader = dynamic_cast<ProjectionShader*>(shader);
    if (projection_shader) {
        projection_shader->model = get_world_transform();
    }
    if () { 
        server->draw_mesh(resource.GetStorage(), shader);
    } else {
        server->draw_mesh(resource.GetStorage(), shader_2);
    }
}

}   // namespace eng
