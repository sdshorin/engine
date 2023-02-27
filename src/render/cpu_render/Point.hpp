#pragma once

# include <glm/glm.hpp>
# include <vector>

namespace cpu_render {

struct  Point {
    glm::vec4 pos;
    glm::vec3 colour;
    glm::vec3 norm;
    glm::vec2 uv;

    Point(): pos(0, 0, 0, 1), colour(0, 0, 0), norm(1, 0, 0), uv(0, 0) {};
    Point operator* (float x) const;
    Point operator+ (const Point& p) const;
    
};

} // namespace cpu_render
