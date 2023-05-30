#pragma once
#include <glm/glm.hpp>

#include "Point.hpp"
#include "Shaders.hpp"

namespace cpu_render {

class ShaderImplementation {
   public:
    eng::BaseShader::ShaderType type;

    virtual void LoadParams(const eng::BaseShader* params) = 0;
    virtual Point VertexShader(const Point& p) = 0;
    virtual glm::ivec3 FragmentShader(const Point& p) = 0;
    virtual ~ShaderImplementation() = default;
};

class ProjectionShaderImplementation : public ShaderImplementation {
    glm::mat4 projection_matrix;
    glm::mat4 camera_matrix;
    glm::mat4 model;

   public:
    ProjectionShaderImplementation() {
        type = eng::BaseShader::ShaderType::ShaderPosition;
    }

    virtual void LoadParams(const eng::BaseShader* params);
    virtual Point VertexShader(const Point& p);
    virtual glm::ivec3 FragmentShader(const Point& p);
};

}   // namespace cpu_render
