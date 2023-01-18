# include <glm/glm.hpp>
#include "Mesh.hpp"
#include <iostream>
#include "VisualServer.h"
#include <sstream>
#include <glm/gtx/string_cast.hpp>
// #include <sstream>
#include <string>
#include <fstream>

Mesh::Mesh(MeshResource& resource_in): resource(resource_in) {
    ProjectionShader *p_shader = new ProjectionShader;
    p_shader->model = glm::mat4(1.0f);
    shader = p_shader;
}


void Mesh::draw_self(VisualServer* server) const {
    server->draw_mesh(resource.GetStorage(), shader);
}

