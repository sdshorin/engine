#pragma once

# include <glm/glm.hpp>
# include <SDL2/SDL.h>
# include <vector>
#include "GraphicSettings.hpp"
#include "CPUVisualStorage.hpp"
#include "ShaderImplementation.hpp"
#include "Screen.hpp"
#include "GraphicSettings.hpp"

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
	// void draw_polygon(const std::vector<glm::vec4>& points, const Camera *camera, const GraphicSettings* settings, int32_t* frame_buffer);
	void draw_mesh(eng::BaseVisualStorage* data, const eng::BaseShader* shader_params);
    eng::BaseVisualStorage* create_storage();
    ~CPURender();
};

} // namespace cpu_render
