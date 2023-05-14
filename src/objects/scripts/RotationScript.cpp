#include "RotationScript.hpp"

#include "glm/gtc/matrix_transform.hpp"

namespace eng {

void RotationScript::process(float delta) {
    float rotated_radians = 3.14f * delta * step;
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), rotated_radians, axis);

    owner->transform = rotationMatrix * owner->transform;
}

}   // namespace eng