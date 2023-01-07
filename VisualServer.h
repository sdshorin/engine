#pragma once

#include "camera.hpp"
#include "CPURender.hpp"
#include <SDL2/SDL.h> 
// #define GL_SILENCE_DEPRECATION
// #include <GLFW/glfw3.h>



class BaseRender {
};



class VisualServer {
	GraphicSettings* settings;
	CPURender* render;
	Camera *camera;
	// GLFWwindow* window;
	SDL_Window* window;
	int32_t* frame_buffer;
public:
	VisualServer();
	~VisualServer();
	void InitGraphic();
	void flush();
	void RenderScreen();
	// void DrawObject();
	void draw_polygon(std::vector<glm::vec4>& points);
};


class Material {
	std::string code_vertex;
	std::string code_fragment;

	// GLuint shader_program;
	void CreateProgram();

};





