#pragma once

# include <glm/glm.hpp>
# include <vector>
#include "camera.hpp"
#include "GraphicSettings.hpp"

class CPURender {
    public:
	void draw_polygon(const std::vector<glm::vec4>& points, const Camera *camera, const GraphicSettings* settings, int32_t* frame_buffer);
};
