#pragma once

#include "camera.hpp"
#include "CPURender.hpp"

// #define GL_SILENCE_DEPRECATION
// #include <GLFW/glfw3.h>
#include "BaseVisualStorage.hpp"
#include "Shaders.hpp"

namespace eng {

class BaseRender {
};


class VisualServer {

	GraphicSettings* settings;
	cpu_render::CPURender* render;
public:
	Camera *camera;
	VisualServer();
	
	void InitGraphic();
	void flush();
	void RenderScreen();
	void draw_mesh(BaseVisualStorage* data, BaseShader* shader);
	BaseVisualStorage* create_storage();
};

} // namespace eng





