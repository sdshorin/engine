#pragma once

#include "EmptyScript.hpp"

namespace scripts {

class RotationScript: public EmptyScript {
    glm::vec3 axis;
    float step;

   public:
    RotationScript(glm::vec3 axis, float step = 0.1) : axis(axis), step(step) {
    }
    void process(float delta);
};
}   // namespace scripts
