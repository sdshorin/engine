#pragma once

# include <glm/glm.hpp>

class Camera {
public:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::mat4 projection_matrix;
    glm::mat4 camera_matrix;

    float speed;

    Camera();
    glm::mat4 get_projection_matrix() const;
    glm::mat4 get_camera_matrix() const;

    void move(glm::vec3 offset);
    void move_right(float delta);
    void move_left(float delta);

    void move_down(float delta);
    void move_up(float delta);
};

