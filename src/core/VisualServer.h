#pragma once

#include "camera.hpp"
#include "CPURender.hpp"
#include <SDL2/SDL.h> 
// #define GL_SILENCE_DEPRECATION
// #include <GLFW/glfw3.h>
#include "BaseVisualStorage.hpp"
#include "BaseShader.hpp"

class BaseRender {
};


class VisualServer {

	GraphicSettings* settings;
	CPURender* render;
	// GLFWwindow* window;
	SDL_Window* window;
	int32_t* frame_buffer;
public:
	Camera *camera;
	VisualServer();
	~VisualServer();
	void InitGraphic();
	void flush();
	void RenderScreen();
	// void DrawObject();
	// void draw_polygon(const std::vector<glm::vec4>& points);
	void draw_mesh(BaseVisualStorage* data);
	// BaseVisualStorage* create_storage(BaseShader::ShaderType type);
	// BaseVisualStorage* create_storage(MeshResource::MeshType type);
	BaseVisualStorage* create_storage(); // always use large points
};

// Требования:
// MeshResource загружается в видеопамять один раз, при создании
// Видеопамять поддерживает разное количество информации для шейдеров, в том числе позволяет быстро создавать новые типы точек с новыми данными
// Точки наследуются, шейдеры могут работать с конкретными точками и любыми их наследованиями
// <===> Для продвинутых точек можно использовать сколь угодно простой шейдер.

// Упрощаем: всегда используем одни и те же точки. маленькие потери по памяти, но нет усложнения кода и замедления из-за dynamic cast

// Надо ли использовать отдельный объект для передачи данных из вершинного шейдера во фрагментный? Надо, но потом.



// Алгоритм работы с графикой:
// 0. полигон загружается из файла
// 1. Полигон загружается в созданный BaseVisualStorage (который создается под конкретный шейдер)
//      			MeshResource выбирает шейдер, который 
// 2. Создается шейдер (объект, который хранит в себе тип шейдера и его униформы)
// 3. draw(BaseVisualStorage*, BaseShader*);
// 4. CPURenderer смотрит, какие точки хранятся в BaseVisualStorage, и выбирает нужную функцию: draw_mesh<LitedPoint>(BaseVisualStorage*, BaseShader*);
//						(В начале определяемся с данными, и только потом - с методами)
// 5. draw_mesh<LitedPoint> загружает реализацию шейдера и проверяет, что он поддерживает заданные точки
// 6. Работаем с точками, которые заданы статично.






// class Material {
// 	std::string code_vertex;
// 	std::string code_fragment;

// 	// GLuint shader_program;
// 	void CreateProgram();

// };



// TODO:
// 1. add VisualDataStorage, render cube
// 2. add vs shader, render cube
// 2. add colour fragment shader, render coloured cube


// class MeshResource {
//     GPUStorage graphic_data;
// }

// class GPUStorage {
//     BaseStorage* data
// public:
//     void transfer_pos() {data->load_pos()};
//     void transfer_colour();
//     void transfer_uv();
//     void transfer_norm();
//     void commit();
// };



// template <class Point>
// class CPUShader: public BaseShader {
//     glm::mat4 model;
//     glm::mat4 view;
//     glm::mat4 view;

//     Point vertex_shader(Point p);
//     gml::ivec3 fragment_shader(Point p);
    
//     void set_uniform(std::string name, glm::vec3 value);
//     void set_uniform(std::string name, glm::mat4 value);

// }




// void render_mesh(const GPUStorage& data, const CPUShader* shader) {
//     switch (shader.type)
//     {
//     case Shader::Base:
//         render_mesh<BasePoint>(data, shader);
//         break;
//     case Shader::Color:
//         render_mesh<BasePoint>(data, shader);
//         break;
    
//     default:
//         break;
//     }
// }







