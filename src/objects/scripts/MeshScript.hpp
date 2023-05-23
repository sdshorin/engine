#pragma once

#include "MeshResource.hpp"
#include "Shaders.hpp"
#include "Node.hpp"
#include "EmptyScript.hpp"
namespace scripts {

class MeshScript: public EmptyScript {
    eng::ResourceRef resource;
    std::unique_ptr<eng::BaseShader> shader;

   public:
    MeshScript(eng::ResourceRef resource_in);


    void draw(eng::VisualServer* server) const;
    void process(float delta);
};

}   // namespace scripts
