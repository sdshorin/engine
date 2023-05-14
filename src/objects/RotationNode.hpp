#pragma once

#include "EmptyScript.hpp"

namespace eng {

class RotationNode: public EmptyScript {
    glm::vec3 axis;
    float step;

   public:
    RotationNode(glm::vec3 axis, float step = 0.1) : axis(axis), step(step) {
    }
    void process(float delta);
};
}   // namespace eng
