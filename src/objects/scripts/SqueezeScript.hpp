#pragma once

#include "EmptyScript.hpp"

namespace eng {

class SqueezeScript: public EmptyScript {
    glm::vec3 sensitivity;
    float time;
    float speed;

   public:
    SqueezeScript(glm::vec3 sensitivity, float speed = 0.1) : sensitivity(sensitivity), speed(speed), time(0) {
    }
    void process(float delta);
};
}   // namespace eng
