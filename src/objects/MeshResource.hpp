#pragma once

#include "TreeObject.hpp"
#include "VisualServer.h"

class MeshResource {
    BaseVisualStorage* storage;
public:
    MeshResource(std::string path);
    BaseVisualStorage* GetStorage() const;

};


