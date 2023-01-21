#pragma once

# include <glm/glm.hpp>
# include <SDL2/SDL.h>
# include <vector>
#include "GraphicSettings.hpp"
#include "CPUVisualStorage.hpp"
#include "ShaderImplementation.hpp"
#include "Screen.hpp"
#include "GraphicSettings.hpp"
class CPURender {
    std::vector<CPUVisualStorage*> storages;
    std::vector<ShaderImplementation*> shader_algorithms;
    Screen screen;
    SDL_Window* window;
    
    ShaderImplementation* GetShader(BaseShader::ShaderType type);
    void RasterizerTriangle(ShaderImplementation* shader_imp, const Point& p_1, const Point& p_2, const Point& p_3);

public:

    CPURender();
    void Flush();
    void InitGraphic(GraphicSettings* settings);
    void RenderScreen();
	// void draw_polygon(const std::vector<glm::vec4>& points, const Camera *camera, const GraphicSettings* settings, int32_t* frame_buffer);
	void draw_mesh(BaseVisualStorage* data, const BaseShader* shader_params);
    BaseVisualStorage* create_storage();
    ~CPURender();
};
