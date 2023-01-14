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
}


void Mesh::draw_self(VisualServer* server) const {
    std::cout << "Draw Mesh\n";
    server->draw_mesh(resource.GetStorage());
}

