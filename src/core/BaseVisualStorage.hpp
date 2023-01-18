#pragma once
# include <glm/glm.hpp>
# include <vector>

class BaseVisualStorage {
public:
    virtual void load_pos(const std::vector<glm::vec4>& data) = 0;
    virtual void load_colour(const std::vector<glm::vec3>& data) = 0;
    virtual void load_uv(const std::vector<glm::vec2>& data) = 0;
    virtual void load_norm(const std::vector<glm::vec3>& data) = 0;
    virtual void commit() = 0;
};
