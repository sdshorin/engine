#pragma once
#include <glm/glm.hpp>
#include <vector>

#include "BaseVisualStorage.hpp"
#include "Point.hpp"

#include "MeshResource.hpp"

namespace cpu_render {

class CPUVisualStorage : public eng::BaseVisualStorage {
   public:
    std::vector<Point> data;
    CPUVisualStorage(eng::MeshResource& res);
    ~CPUVisualStorage() = default;
    virtual void load_pos(const std::vector<glm::vec4>& data);
    virtual void load_colour(const std::vector<glm::vec3>& data);
};

}   // namespace cpu_render
