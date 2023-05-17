#pragma once

#include "MeshResource.hpp"
#include "Shaders.hpp"
#include "Node.hpp"
#include "EmptyScript.hpp"
namespace eng {

class MeshScript: public EmptyScript {
    ResourceRef resource;
    std::unique_ptr<BaseShader> shader;

   public:
    MeshScript(ResourceRef resource_in);


    void draw(VisualServer* server) const;
    void process(float delta);
};

}   // namespace eng
