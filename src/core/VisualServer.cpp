#include "engine.hpp"
#include <iostream>


// #include <OpenGL/gl3.h>


VisualServer::VisualServer() {
	render = new CPURender;
	camera = new Camera;
	settings = new GraphicSettings;
	std::cout << "CPURender created \n";
}

void VisualServer::flush() {
	for (int i = 0; i < settings->window_width * settings->window_high; ++i) {
		frame_buffer[i] = 100 << 24 | 100 << 16 | 100 << 8 | 100;
	}
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
    render->draw_mesh(data, shader_in, settings, frame_buffer);
}

BaseVisualStorage* VisualServer::create_storage() {
    return render->create_storage();
}

void VisualServer::InitGraphic() {

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }
    window = SDL_CreateWindow("GAME",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       settings->window_width, settings->window_high, SDL_WINDOW_SHOWN);
	frame_buffer = (int32_t*)malloc(settings->window_width * settings->window_high * sizeof(int32_t));
	// gWindowID = SDL_GetWindowID(gWindow);
}

void VisualServer::RenderScreen() {
	std::cout << "Render Screen\n";
	SDL_Surface *pixelSurface = SDL_CreateRGBSurfaceFrom(frame_buffer,
                                                         settings->window_width,
                                                         settings->window_high,
                                                         8 * 4,										   // depth in bits (BitsPerByte * BytesPerPixel)
                                                         settings->window_width * 4,						   // pitch (row length * BytesPerPixel)
                                                         0x000000ff,                                   // red mask
                                                         0x0000ff00,                                   // green mask
                                                         0x00ff0000,                                   // blue mask
                                                         0);   


	SDL_BlitSurface(pixelSurface, NULL, SDL_GetWindowSurface(window), NULL);

    SDL_FreeSurface(pixelSurface); 
	SDL_UpdateWindowSurface(window);
}


VisualServer::~VisualServer() {
	SDL_DestroyWindow(window);
    window = NULL;
    SDL_Quit();
}
