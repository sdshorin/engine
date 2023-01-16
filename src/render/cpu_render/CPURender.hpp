#pragma once

# include <glm/glm.hpp>
# include <vector>
#include "GraphicSettings.hpp"
#include "CPUVisualStorage.hpp"
#include "ShaderImplementation.hpp"

class CPURender {
    std::vector<CPUVisualStorage*> storages;
    std::vector<ShaderImplementation*> shader_algorithms;
    
    ShaderImplementation* GetShader(BaseShader::ShaderType type);

    public:

    CPURender();
	// void draw_polygon(const std::vector<glm::vec4>& points, const Camera *camera, const GraphicSettings* settings, int32_t* frame_buffer);
	void draw_mesh(BaseVisualStorage* data, const BaseShader* shader_params, const GraphicSettings* settings, int32_t* frame_buffer);
    BaseVisualStorage* create_storage();
};
