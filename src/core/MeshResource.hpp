#pragma once

#include <glm/glm.hpp>
#include <vector>

#if __linux__
#include <string>
#endif

namespace eng {

class MeshResource {
   public:
    std::vector<glm::vec3> colours;
    std::vector<glm::vec4> triangles;

    MeshResource(std::string path);
};

}   // namespace eng
