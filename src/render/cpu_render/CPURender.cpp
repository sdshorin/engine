
#include "CPURender.hpp"

# include <vector>
# include <glm/glm.hpp>

#include <glm/gtx/string_cast.hpp>
#include <iostream>
struct Rectangle {
	float x, y, size_x, size_y;

	Rectangle(float x_p, float y_p): x(x_p), y(y_p), size_x(0), size_y(0) {}

	void add_point(float x_p, float y_p) {
		if (x_p > x) {
			size_x = std::max(size_x, x_p - x);
		} else {
			size_x += (x - x_p);
			x = x_p;
		}
		if (y_p > y) {
			size_y = std::max(size_y, y_p - y);
		} else {
			size_y += (y - y_p);
			y = y_p;
		}
	}

};

std::ostream &operator<<(std::ostream &os, Rectangle const &rect) { 
	return os << "Rect(x: " << rect.x << ", y: " << rect.y << ", size_x: " << rect.size_x << ", size_y: " << rect.size_y << ")";
}

float edge_function(glm::vec4& v0, glm::vec4& v1, glm::vec4& v2) {
	return (v1.x - v0.x) * (v2.y - v0.y) - (v1.y - v0.y) * (v2.x - v0.x);
}



void CPURender::draw_mesh(BaseVisualStorage* data, const BaseShader* shader_params) {
	std::cout << "VisualServer draw_mesh \n";

	ShaderImplementation* shader_imp = GetShader(shader_params->type); 
	if (!shader_imp) {
		throw std::invalid_argument("Can't find shader");
	}
	shader_imp->LoadParams(shader_params);

	CPUVisualStorage *store = dynamic_cast<CPUVisualStorage*>(data);
	if (!store) {
		std::cout << "VisualServer wrong storage! \n";
	}

	const std::vector<Point>& points = store->data;
	std::cout << "VisualServer points size: " << points.size() << "\n";
	
	for (int i = 0; i < points.size(); i += 3) {
		Point p[3] = {points[i], points[i + 1], points[i + 2]};

		for (int i = 0; i < 3; ++i) {

			p[i].pos = p[i].pos / p[i].pos.w;

			p[i] = shader_imp->VertexShader(p[i]);
			
			p[i].pos = p[i].pos / p[i].pos.w;

			p[i].pos.x = p[i].pos.x * 0.5 + 0.5f;
			p[i].pos.y = -p[i].pos.y * 0.5 + 0.5f;

			p[i].pos.x *= screen.window_width;
        	p[i].pos.y *= screen.window_high;


		}

		Rectangle rect(p[0].pos.x, p[0].pos.y);
		rect.add_point(p[1].pos.x, p[1].pos.y);
		rect.add_point(p[2].pos.x, p[2].pos.y);
       
		// std::cout << "rect: "  << rect  << "\n";

        rect.x = std::max(0.0f, rect.x);
        rect.y = std::max(0.0f, rect.y);
        rect.size_x = std::min(screen.window_width - rect.x, rect.size_x);
        rect.size_y = std::min(screen.window_high - rect.y, rect.size_y);


		// std::cout << "volume: "  << edge_function(p[0].pos, p[1].pos, p[2].pos) / 2   << "\n";
        float triangle_square = edge_function(p[0].pos, p[1].pos, p[2].pos);

        for (int x = rect.x; x < rect.x + rect.size_x; ++x) {
            // std::cout << "|";
            for (int y = rect.y; y < rect.y + rect.size_y; ++y) {
                glm::vec4 point(x, y, 0, 1);

                float e_1 = edge_function(p[0].pos, p[1].pos, point) / triangle_square;
                float e_2 = edge_function(p[1].pos, p[2].pos, point) / triangle_square;
                float e_3 = edge_function(p[2].pos, p[0].pos, point) / triangle_square;

				// TODO: check z-buffer
                if (std::signbit(e_1) == std::signbit(e_2) && std::signbit(e_2) == std::signbit(e_3)) {
						Point pixel = p[0] * e_1 + p[1] * e_2 + p[2] * e_3;
                        int32_t a8 = 255;
                        int32_t r8 = int32_t(pixel.colour.x);
                        int32_t g8 = int32_t(pixel.colour.y);
                        int32_t b8 = int32_t(pixel.colour.z);
                        int32_t col32 = a8 << 24 | b8 << 16 | g8 << 8 | r8;
                        screen.frame_buffer[y * screen.window_width + x] = col32;

                    // std::cout << x << " " << y << "\n";
                } else {
					// int32_t r8 = int32_t(((std::signbit(e_1))? 1 : 0) * 255.0f);
					// int32_t g8 = int32_t(((std::signbit(e_2))? 1 : 0) * 255.0f);
					// int32_t b8 = int32_t(((std::signbit(e_3))? 1 : 0) * 255.0f);

					// frame_buffer[y * screen.window_width + x] = r8 << 24 | g8 << 16 | b8 << 8 | r8;
                    // std::cout << "0";
                }
            }
            // std::cout << "|\n";
        }
	}

}


BaseVisualStorage* CPURender::create_storage() {
	CPUVisualStorage* store = new CPUVisualStorage;
	storages.push_back(store);
	return store;
}

void CPURender::Flush() {
	for (int i = 0; i < screen.window_width * screen.window_high; ++i) {
		screen.frame_buffer[i] = 100 << 24 | 100 << 16 | 100 << 8 | 100;
		screen.z_buffer[i] = 1000000;
	}
}

void CPURender::InitGraphic(GraphicSettings* settings) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }
	screen.window_width = settings->window_width;
	screen.window_high = settings->window_high;
    window = SDL_CreateWindow(settings->window_name.c_str(),
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       screen.window_width, screen.window_high, SDL_WINDOW_SHOWN);
	screen.frame_buffer = (int32_t*)malloc(screen.window_width * screen.window_high * sizeof(int32_t));
	screen.z_buffer = (int32_t*)malloc(screen.window_width * screen.window_high * sizeof(int32_t));
}

void CPURender::RenderScreen() {
	std::cout << "Render Screen\n";
	SDL_Surface *pixelSurface = SDL_CreateRGBSurfaceFrom(screen.frame_buffer,
                                                         screen.window_width,
                                                         screen.window_high,
                                                         8 * 4,										   // depth in bits (BitsPerByte * BytesPerPixel)
                                                         screen.window_width * 4,						// pitch (row length * BytesPerPixel)
                                                         0x000000ff,                                   // red mask
                                                         0x0000ff00,                                   // green mask
                                                         0x00ff0000,                                   // blue mask
                                                         0);   

	SDL_BlitSurface(pixelSurface, NULL, SDL_GetWindowSurface(window), NULL);

    SDL_FreeSurface(pixelSurface); 
	SDL_UpdateWindowSurface(window);
}


CPURender::CPURender() {
	shader_algorithms.push_back(new ProjectionShaderImplementation);
}

CPURender::~CPURender() {
	SDL_DestroyWindow(window);
    window = NULL;
    SDL_Quit();
}


ShaderImplementation* CPURender::GetShader(BaseShader::ShaderType type) {
	for (ShaderImplementation* shader : shader_algorithms) {
		if (shader->type == type) {
			return shader;
		}
	}
	return NULL;
}

