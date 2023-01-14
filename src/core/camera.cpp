#include "camera.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>
#include <glm/gtx/string_cast.hpp>

glm::mat4 Camera::get_projection_matrix() const {
    return projection_matrix;
}

glm::mat4 Camera::get_camera_matrix() const {
    // return camera_matrix;
    return glm::lookAt(position, position + front, up);
}

Camera::Camera() {
    position = glm::vec3(0.0, 0.0, 3.0);
    front = glm::vec3(0.0, 0.0, -1.0);
    up = glm::vec3(0.0, 1.0, 0.0);
    camera_matrix  = glm::lookAt(position, position + front, up);
    speed = 1;

    projection_matrix = glm::perspective(
            glm::radians(45.0f),    // field of view
            800.0f / 600.0f,      // aspect ratio
            0.1f, 1000.0f            // near and far clipping planes
        );
}

void Camera::move(glm::vec3 offset) {
    position += offset * speed;
    std::cout << "camera pos: "  << glm::to_string(position).c_str()   << "\n";
}

void Camera::move_right(float delta) {
    glm::vec3 right = glm::normalize(glm::cross(front, up));
    position += right * delta * speed;
    std::cout << "camera pos: "  << glm::to_string(position).c_str()   << "\n";
}

void Camera::move_left(float delta) {
    glm::vec3 right = glm::normalize(glm::cross(front, up));
    position -= right * delta * speed;
    std::cout << "camera pos: "  << glm::to_string(position).c_str()   << "\n";
}

void Camera::move_up(float delta) {
    position += up * delta * speed;
    std::cout << "camera pos: "  << glm::to_string(position).c_str()   << "\n";
}

void Camera::move_down(float delta) {
    position -= up * delta * speed;
    std::cout << "camera pos: "  << glm::to_string(position).c_str()   << "\n";
}

