# pragma once
#include "Shaders.hpp"
#include "Point.hpp"
#include <glm/glm.hpp>

class ShaderImplementation {
public:
    BaseShader::ShaderType type;
    
    // ShaderImplementation() = delete;

    virtual void LoadParams(const BaseShader* params) = 0;
    virtual Point VertexShader(const Point& p) = 0;
    virtual glm::ivec3 FragmentShader(const Point& p) = 0;
};

class ProjectionShaderImplementation: public ShaderImplementation {
    glm::mat4 projection_matrix;
    glm::mat4 camera_matrix;
    glm::mat4 model;
public:
    ProjectionShaderImplementation() {type = BaseShader::ShaderType::ShaderPosition; }
    
    virtual void LoadParams(const BaseShader* params);
    virtual Point VertexShader(const Point& p);
    virtual glm::ivec3 FragmentShader(const Point& p);
};

// class ColourShaderImplementation: public ProjectionShaderImplementation {
//     ColourShaderImplementation() {type = BaseShader::ShaderType::ShaderColor; }

//     virtual void LoadParams(const BaseShader* params);
//     virtual Point VertexShader(const Point& p);
//     virtual Point FragmentShader(const Point& p);
// };
