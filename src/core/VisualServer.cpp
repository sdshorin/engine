#include "engine.hpp"
#include <iostream>


// #include <OpenGL/gl3.h>


VisualServer::VisualServer() {
	camera = new Camera;
	settings = new GraphicSettings;
	render = new CPURender();
	std::cout << "CPURender created \n";
}

void VisualServer::flush() {
    render->Flush();
	
}

// void VisualServer::draw_polygon(const std::vector<glm::vec4>& points) {
// 	render->draw_polygon(points, camera, settings, frame_buffer);
// }

void VisualServer::draw_mesh(BaseVisualStorage* data, BaseShader* shader_in) {
    ProjectionShader* shader = dynamic_cast<ProjectionShader*>(shader_in);
    if (!shader) {
        std::cout << "Can't draw mesh: shader is not ProjectionShader" << std::endl;
        return;
    }
    shader->camera_matrix = camera->get_camera_matrix();
    shader->projection_matrix = camera->get_projection_matrix();
    render->draw_mesh(data, shader_in);
}

BaseVisualStorage* VisualServer::create_storage() {
    return render->create_storage();
}

void VisualServer::InitGraphic() {
    render->InitGraphic(settings);
}

void VisualServer::RenderScreen() {
    render->RenderScreen();
	
}

