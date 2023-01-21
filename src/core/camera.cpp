#include "camera.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>
#include <glm/gtx/string_cast.hpp>

glm::mat4 Camera::get_projection_matrix() const {
    return projection_matrix;
}


glm::mat4 create_camera_matrix(glm::vec3 position, glm::vec3 target, glm::vec3 up)
{
    up = glm::normalize(up);
    glm::vec3 z_camera_dir = glm::normalize(position - target);
    glm::vec3 x_camera_right = glm::normalize(glm::cross(glm::normalize(up), z_camera_dir));
    glm::vec3 y_camera_up = glm::cross(z_camera_dir, x_camera_right);


    glm::mat4 matrix = glm::mat4(1);
	matrix[0][0] = x_camera_right[0];
	matrix[1][0] = x_camera_right[1];
	matrix[2][0] = x_camera_right[2];

    matrix[0][1] = y_camera_up[0];
	matrix[1][1] = y_camera_up[1];
	matrix[2][1] = y_camera_up[2];

    matrix[0][2] = z_camera_dir[0];
	matrix[1][2] = z_camera_dir[1];
	matrix[2][2] = z_camera_dir[2];

    matrix[3][0] = -glm::dot(x_camera_right, position);
    matrix[3][1] = -glm::dot(y_camera_up, position);
    matrix[3][2] = -glm::dot(z_camera_dir, position);

    return matrix;
}


glm::mat4 Camera::get_camera_matrix() const {
    glm::mat4 mat = create_camera_matrix(position, position + front, up);
    return mat;
}

glm::mat4 perspective(float fov, float aspect, float near, float far) {
    glm::mat4 matrix = glm::mat4(1);
    float h_1 = near * tan(fov * glm::pi<float>() / 360.0);
    matrix[3][3] = 0;
    matrix[2][3] = -1;
    matrix[2][2] = -(far + near) / (far - near);;
    matrix[3][2] = (-2 * far * near) / (far - near);
    
    matrix[1][1] = (2 * near) / (h_1 * 2);;
	matrix[0][0] = matrix[1][1] / aspect;
    return matrix;
}


Camera::Camera() {
    position = glm::vec3(0.0, 0.0, 3.0);
    front = glm::vec3(0.0, 0.0, -1.0);
    up = glm::vec3(0.0, 1.0, 0.0);
    camera_matrix  = glm::lookAt(position, position + front, up);
    speed = 1;
    pitch = 0.0f;
	yaw = -90.0f;

    projection_matrix = perspective(
            45.0f,                // field of view
            800.0f / 600.0f,      // aspect ratio
            0.1f, 1000.0f         // near and far clipping planes
        );
    return;

}


void Camera::move(glm::vec3 offset) {
    position += offset * speed;
    // std::cout << "camera pos: "  << glm::to_string(position).c_str()   << "\n";
}


void Camera::move_right(float delta) {
    glm::vec3 right = glm::normalize(glm::cross(front, up));
    position += right * delta * speed;
    // std::cout << "camera pos: "  << glm::to_string(position).c_str()   << "\n";
}


void Camera::move_left(float delta) {
    glm::vec3 right = glm::normalize(glm::cross(front, up));
    position -= right * delta * speed;
    // std::cout << "camera pos: "  << glm::to_string(position).c_str()   << "\n";
}


void Camera::move_up(float delta) {
    position += up * delta * speed;
    // std::cout << "camera pos: "  << glm::to_string(position).c_str()   << "\n";
}


void Camera::move_down(float delta) {
    position -= up * delta * speed;
    // std::cout << "camera pos: "  << glm::to_string(position).c_str()   << "\n";
}


void Camera::rotate(int xrel, int yrel) {
    yaw += xrel * CAMERA_SENSITIVITY;
    pitch += yrel * CAMERA_SENSITIVITY;

    pitch = glm::clamp(pitch, -89.0f, 89.0f);
    
    float pi = glm::pi<float>();
    front.x = cos(yaw / 180.0 * pi) * cos(pitch / 180.0 * pi);
    front.y = sin(pitch / 180.0 * pi);
    front.z = sin(yaw / 180.0 * pi) * cos(pitch / 180.0 * pi);
}
