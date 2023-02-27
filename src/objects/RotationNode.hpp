#pragma once
#include "TreeObject.hpp"

namespace eng {

class RotationNode: public TreeObject {
    glm::vec3 axis;
    float step;
public:
    RotationNode(glm::vec3 axis, float step = 0.1): axis(axis), step(step) {}
    virtual void process(float delta);
};
} // namespace eng
