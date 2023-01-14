#pragma once

# include <glm/glm.hpp>
# include <vector>
#include "camera.hpp"
#include "GraphicSettings.hpp"
#include "CPUVisualStorage.hpp"

class CPURender {
    std::vector<CPUVisualStorage*> storages;

    public:
	// void draw_polygon(const std::vector<glm::vec4>& points, const Camera *camera, const GraphicSettings* settings, int32_t* frame_buffer);
	void draw_mesh(BaseVisualStorage* data, const Camera *camera, const GraphicSettings* settings, int32_t* frame_buffer);
    BaseVisualStorage* create_storage();
};
