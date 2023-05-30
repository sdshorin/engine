#include "ShaderImplementation.hpp"

#include <stdexcept>

namespace cpu_render {

void ProjectionShaderImplementation::LoadParams(const eng::BaseShader* params_in) {
    const eng::ProjectionShader* params = dynamic_cast<const eng::ProjectionShader*>(params_in);
    if (!params) {
        throw std::invalid_argument("Can't convert shader_params to ProjectionShader*");
    }
    projection_matrix = params->projection_matrix;
    camera_matrix = params->camera_matrix;
    model = params->model;
}

Point ProjectionShaderImplementation::VertexShader(const Point& p) {
    Point res(p);
    res.pos = projection_matrix * camera_matrix * model * p.pos;
    return res;
}

glm::ivec3 ProjectionShaderImplementation::FragmentShader(const Point& pixel) {
    return glm::ivec3(pixel.colour.r, pixel.colour.g, pixel.colour.b);
}

}   // namespace cpu_render
