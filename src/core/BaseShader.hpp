#pragma once

#include <string.h>
#include <glm/glm.hpp>


class BaseShader {
    enum ShaderType {ShaderPosition, ShaderColor, ShaderLight, ShaderMaterial};
    ShaderType type;
    virtual void set_uniform(std::string name, glm::vec3 value) = 0;
    virtual void set_uniform(std::string name, glm::mat4 value) = 0;
};
