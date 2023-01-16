#include "ShaderImplementation.hpp"

#include <stdexcept>
// class ProjectionShaderImplementation: public ShaderImplementation {
//     ProjectionShaderImplementation() {type = BaseShader::ShaderType::ShaderPosition; }
    
//     ProjectionShaderImplementation::VertexShader(const Point& p);
//     virtual Point FragmentShader(const Point& p);

// };

// class ColourShaderImplementation: public ShaderImplementation {
//     ColourShaderImplementation() {type = BaseShader::ShaderType::ShaderColor; }

//     virtual Point VertexShader(const Point& p);
//     virtual Point FragmentShader(const Point& p);
// };


void ProjectionShaderImplementation::LoadParams(const BaseShader* params_in) {
    const ProjectionShader* params = dynamic_cast<const ProjectionShader*>(params_in);
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

glm::ivec3 ProjectionShaderImplementation::FragmentShader(const Point& p) {
    return glm::ivec3(255, 0, 0); 
}
