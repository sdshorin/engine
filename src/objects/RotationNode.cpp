#include "RotationNode.hpp"

#include "glm/gtc/matrix_transform.hpp"

void RotationNode::process(float delta) {
    float rotated_radians = 3.14f * delta * step;
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), rotated_radians, axis);

    transform = rotationMatrix * transform;
}   