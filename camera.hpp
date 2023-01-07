#pragma once

# include <glm/glm.hpp>

class Camera {
public:
    glm::vec4 position;
    glm::vec4 front;
    glm::vec4 up;
    glm::mat4 projection_matrix;
    glm::mat4 camera_matrix;

    Camera();
    glm::mat4 get_projection_matrix() const;
    glm::mat4 get_camera_matrix() const;
};

