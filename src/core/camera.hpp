#pragma once

# include <glm/glm.hpp>

# define CAMERA_SENSITIVITY 0.05f

class Camera {
public:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::mat4 projection_matrix;
    glm::mat4 camera_matrix;

    float pitch;
	float yaw;

    float speed;

    Camera();
    glm::mat4 get_projection_matrix() const;
    glm::mat4 get_camera_matrix() const;

    void rotate(int xrel, int yrel);

    void move(glm::vec3 offset);
    void move_right(float delta);
    void move_left(float delta);

    void move_down(float delta);
    void move_up(float delta);
};

