#include <iostream>

#include "engine.hpp"

// #include <OpenGL/gl3.h>

namespace eng {
VisualServer::VisualServer(GraphicSettings settings) : settings(settings) {
    render = std::make_unique<cpu_render::CPURender>();
    std::cout << "CPURender created \n";
}

void VisualServer::flush() {
    render->Flush();
}


ResourceRef VisualServer::load_mesh(MeshResource& mesh) {
    return render->load_mesh(mesh);
}

// void VisualServer::draw_polygon(const std::vector<glm::vec4>& points) {
// 	render->draw_polygon(points, camera, settings, frame_buffer);
// }

void VisualServer::draw_mesh(ResourceRef data, BaseShader* shader_in) {
    ProjectionShader* shader = dynamic_cast<ProjectionShader*>(shader_in);
    if (!shader) {
        std::cout << "Can't draw mesh: shader is not ProjectionShader" << std::endl;
        return;
    }
    shader->camera_matrix = camera.get_camera_matrix();
    shader->projection_matrix = camera.get_projection_matrix();
    render->draw_mesh(data, shader_in);
}


void VisualServer::InitGraphic() {
    render->InitGraphic(settings);
}

void VisualServer::RenderScreen() {
    render->RenderScreen();
}

}   // namespace eng
