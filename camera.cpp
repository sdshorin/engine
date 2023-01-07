#include "camera.hpp"
#include "glm/gtc/matrix_transform.hpp"

glm::mat4 Camera::get_projection_matrix() const {
    return projection_matrix;
}

glm::mat4 Camera::get_camera_matrix() const {
    return camera_matrix;
}

Camera::Camera() {
    camera_matrix  = glm::lookAt(glm::vec3(-12.0, 1.3, 0.0), glm::vec3(0.0, 0.3, 0.0), glm::vec3(0.0, 1.0, 0.0));

    projection_matrix = glm::perspective(
            glm::radians(45.0f),    // field of view
            800.0f / 600.0f,      // aspect ratio
            0.0f, 1000.0f            // near and far clipping planes
        );
}
