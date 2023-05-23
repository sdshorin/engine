#include "SqueezeScript.hpp"

#include "glm/gtc/matrix_transform.hpp"

namespace scripts {

void SqueezeScript::process(float delta) {

    glm::mat4 translation(1.0f);

    time += delta * speed;

    translation[0][0] = 1 + sensitivity[0] * sin(time);
    translation[1][1] = 1 + sensitivity[1] * cos(time);
    translation[2][2] = 1 + sensitivity[2] * sin(time + 1);

    owner->transform = translation;
}

}   // namespace scripts