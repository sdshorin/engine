#pragma once

# include <glm/glm.hpp>


struct BaseShader {
    enum ShaderType {ShaderPosition, ShaderColor, ShaderLight, ShaderMaterial};
    ShaderType type;
    BaseShader(ShaderType type_in): type(type_in) {}
    virtual ~BaseShader() {}
};


struct ProjectionShader: public BaseShader {
    glm::mat4 projection_matrix;
    glm::mat4 camera_matrix;
    glm::mat4 model;

    ProjectionShader(): BaseShader(BaseShader::ShaderPosition) {}
};

struct ShaderColor: public ProjectionShader {
    ShaderColor() {
        type = BaseShader::ShaderColor;
    }
};


