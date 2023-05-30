#pragma once

#include <SDL2/SDL.h>

#include <glm/glm.hpp>
#include <vector>

#include "CPUVisualStorage.hpp"
#include "ProjectSettings.hpp"
#include "Screen.hpp"
#include "ShaderImplementation.hpp"



namespace cpu_render {

class CPURender {
    std::vector<std::shared_ptr<const CPUVisualStorage> > storages;
    Screen screen;
    SDL_Window* window;

    std::unique_ptr<ShaderImplementation> GetShader(eng::BaseShader::ShaderType type);
    void RasterizerTriangle(ShaderImplementation* shader_imp, const Point& p_1, const Point& p_2, const Point& p_3);

   public:
    CPURender();
    void Flush();
    void InitGraphic(eng::GraphicSettings settings);
    void RenderScreen();
    void draw_mesh(eng::ResourceRef data, const eng::BaseShader* shader_params);
    eng::ResourceRef load_mesh(eng::MeshResource& mesh);
    ~CPURender();
};

}   // namespace cpu_render
