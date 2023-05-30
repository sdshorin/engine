#pragma once

#if __linux__
#include <memory>
#endif

#include "CPURender.hpp"
#include "camera.hpp"

// #define GL_SILENCE_DEPRECATION
// #include <GLFW/glfw3.h>
#include "BaseVisualStorage.hpp"
#include "Shaders.hpp"

namespace eng {

using ResourceRef = std::shared_ptr<const BaseVisualStorage>;

class BaseRender {};

class VisualServer {
    GraphicSettings settings;
    std::unique_ptr<cpu_render::CPURender> render;

   public:
    Camera camera;
    VisualServer(GraphicSettings settings);

    void InitGraphic();
    void flush();
    void RenderScreen();
    void draw_mesh(ResourceRef data, BaseShader* shader);
    ResourceRef load_mesh(eng::MeshResource& mesh);

};

}   // namespace eng
