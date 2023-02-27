#pragma once

#include "TreeObject.hpp"

namespace eng {

class Triangle : public TreeObject {
    void draw(VisualServer* server) const override;
};

}   // namespace eng
