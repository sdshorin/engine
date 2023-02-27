#pragma once
# include <glm/glm.hpp>
# include <vector>
#include "BaseVisualStorage.hpp"
#include "Point.hpp"

namespace cpu_render {

class CPUVisualStorage: public eng::BaseVisualStorage {
public:
    std::vector<Point> data;
    virtual void load_pos(const std::vector<glm::vec4>& data);
    virtual void load_colour(const std::vector<glm::vec3>& data);
    virtual void load_uv(const std::vector<glm::vec2>& data);
    virtual void load_norm(const std::vector<glm::vec3>& data);
    virtual void commit();
};

} // namespace cpu_render
