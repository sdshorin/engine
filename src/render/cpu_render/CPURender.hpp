#pragma once

#include <SDL2/SDL.h>

#include <glm/glm.hpp>
#include <vector>

#include "CPUVisualStorage.hpp"
#include "GraphicSettings.hpp"
#include "Screen.hpp"
#include "ShaderImplementation.hpp"

namespace cpu_render {

class CPURender {
    std::vector<CPUVisualStorage*> storages;
    std::vector<ShaderImplementation*> shader_algorithms;
    Screen screen;
    SDL_Window* window;

    ShaderImplementation* GetShader(eng::BaseShader::ShaderType type);
    void RasterizerTriangle(ShaderImplementation* shader_imp, const Point& p_1, const Point& p_2, const Point& p_3);

   public:
    CPURender();
    void Flush();
    void InitGraphic(eng::GraphicSettings* settings);
    void RenderScreen();
    void draw_mesh(eng::BaseVisualStorage* data, const eng::BaseShader* shader_params);
    eng::BaseVisualStorage* create_storage();
    ~CPURender();
};

}   // namespace cpu_render
