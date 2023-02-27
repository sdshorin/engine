#pragma once

#include "TreeObject.hpp"
#include "VisualServer.h"

namespace eng {

class MeshResource {
    BaseVisualStorage* storage;

   public:
    MeshResource(std::string path);
    BaseVisualStorage* GetStorage() const;
};

}   // namespace eng
