
#include "CPURender.hpp"

# include <vector>
# include <glm/glm.hpp>

#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <array>

namespace cpu_render {

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

float edge_function(const glm::vec4& v0, const glm::vec4& v1, const glm::vec4& v2) {
	return (v1.x - v0.x) * (v2.y - v0.y) - (v1.y - v0.y) * (v2.x - v0.x);
}

Point ProjectToPanel(const Point& p1, const Point& p2, float panel_z, bool& successfully) {
	float height_prev = std::abs(p1.pos.z - panel_z);
	float height_current = std::abs(p2.pos.z - panel_z);
	if (height_prev + height_current == 0) {
		successfully = false;
		return {};
	}
	float height_prev_normed = (height_prev / (height_prev + height_current));
	float height_current_normed = (height_current / (height_prev + height_current));
	successfully = true;

	return p2 * height_prev_normed + p1 * height_current_normed;
}

int ClipTriangle(const std::array<Point, 3>& p, std::array<Point, 4>& clipped_p, float dist) {
	bool isLastClipped = p[0].pos.z < dist;
	int last_processed_index = 0;

	for (int i = 1; i <= 3; ++i) {
		if (p[i % 3].pos.z < dist) {
			if (!isLastClipped) {
				// went through the panel
				// add a point projected to the panel
				bool successfully;
				clipped_p[last_processed_index] = ProjectToPanel(p[i - 1], p[i  % 3], dist, successfully);
				last_processed_index++;
				if (!successfully) {
					return 0;
				}
			} else {
				// behind the panel - ignore
			}
			isLastClipped = true;
		} else {
			if (!isLastClipped) {
				// both points on screen
				clipped_p[last_processed_index] = p[i  % 3];
				last_processed_index++;
			} else {
				// left the panel. add a projected point;
				bool successfully;
				clipped_p[last_processed_index] = ProjectToPanel(p[i - 1], p[i  % 3], dist, successfully);
				last_processed_index++;
				if (!successfully) {
					return 0;
				}
				// add current point
				clipped_p[last_processed_index] = p[i  % 3];
				last_processed_index++;
			}
			isLastClipped = false;
		}
	}
	return last_processed_index;
}

void CPURender::draw_mesh(eng::BaseVisualStorage* data, const eng::BaseShader* shader_params) {

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
	
	for (int i = 0; i < points.size(); i += 3) {
		std::array<Point, 3> p = {points[i], points[i + 1], points[i + 2]};

		bool clipped = false;
		for (int i = 0; i < 3; ++i) {
			// to func vertexShader
			p[i].pos = p[i].pos / p[i].pos.w;

			p[i] = shader_imp->VertexShader(p[i]);
		}
		// clipping
		std::array<Point, 4> clipped_p;
		// Point clipped_p[4];
		int filled_points = ClipTriangle(p, clipped_p, 0.1);

		for (int i = 0; i < filled_points; ++i) {
			clipped_p[i].pos = clipped_p[i].pos / clipped_p[i].pos.w;

			clipped_p[i].pos.x = clipped_p[i].pos.x * 0.5 + 0.5f;
			clipped_p[i].pos.y = -clipped_p[i].pos.y * 0.5 + 0.5f;

			clipped_p[i].pos.x *= screen.window_width;
        	clipped_p[i].pos.y *= screen.window_high;
		}

		if (filled_points == 3) {
			RasterizerTriangle(shader_imp, clipped_p[0], clipped_p[1], clipped_p[2]);
		} else if (filled_points == 4) {
			RasterizerTriangle(shader_imp, clipped_p[0], clipped_p[1], clipped_p[2]);
			RasterizerTriangle(shader_imp, clipped_p[0], clipped_p[2], clipped_p[3]);
		}
	}
}

void CPURender::RasterizerTriangle(ShaderImplementation* shader_imp, const Point& p_1, const Point& p_2, const Point& p_3) {
	Rectangle rect(p_1.pos.x, p_1.pos.y);
	rect.add_point(p_2.pos.x, p_2.pos.y);
	rect.add_point(p_3.pos.x, p_3.pos.y);
	
	if (rect.x < 0.0f) {
		rect.size_x += rect.x;
		rect.size_x = std::max(rect.size_x, 0.0f);
		rect.x = 0;
	}
	rect.size_x = std::min(std::max(screen.window_width - rect.x, 0.0f), rect.size_x);

	if (rect.y < 0.0f) {
		rect.size_y += rect.y;
		rect.size_y = std::max(rect.size_y, 0.0f);
		rect.y = 0;
	}
	rect.size_y = std::min(std::max(screen.window_high - rect.y, 0.0f), rect.size_y);

	float triangle_square = edge_function(p_1.pos, p_2.pos, p_3.pos);
	for (int x = rect.x; x < rect.x + rect.size_x; ++x) {
		for (int y = rect.y; y < rect.y + rect.size_y; ++y) {
			glm::vec4 point(x, y, 0, 1);

			float e_1 = edge_function(p_1.pos, p_2.pos, point) / triangle_square;
			float e_2 = edge_function(p_2.pos, p_3.pos, point) / triangle_square;
			float e_3 = edge_function(p_3.pos, p_1.pos, point) / triangle_square;

			if (std::signbit(e_1) == std::signbit(e_2) && std::signbit(e_2) == std::signbit(e_3)) {
					Point pixel = p_3 * e_1 + p_1 * e_2 + p_2 * e_3;

					if ( pixel.pos.z > screen.z_buffer[y * screen.window_width + x]) {
						continue;
					}
					
					glm::ivec3 colour = shader_imp->FragmentShader(pixel);
					int32_t col32 = 255 << 24 | colour.b << 16 | colour.g << 8 | colour.r;

					screen.frame_buffer[y * screen.window_width + x] = col32;
					screen.z_buffer[y * screen.window_width + x] = pixel.pos.z;

			}
		}
	}
}


eng::BaseVisualStorage* CPURender::create_storage() {
	CPUVisualStorage* store = new CPUVisualStorage;
	storages.push_back(store);
	return store;
}

void CPURender::Flush() {
	for (int i = 0; i < screen.window_width * screen.window_high; ++i) {
		screen.frame_buffer[i] = 100 << 24 | 100 << 16 | 100 << 8 | 100;
		screen.z_buffer[i] = 1.0;
	}
}

void CPURender::InitGraphic(eng::GraphicSettings* settings) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }
	screen = Screen(settings->window_high, settings->window_width);
    window = SDL_CreateWindow(settings->window_name.c_str(),
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       screen.window_width, screen.window_high, SDL_WINDOW_SHOWN);
	
	SDL_SetRelativeMouseMode(SDL_TRUE);
}

void CPURender::RenderScreen() {
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


ShaderImplementation* CPURender::GetShader(eng::BaseShader::ShaderType type) {
	for (ShaderImplementation* shader : shader_algorithms) {
		if (shader->type == type) {
			return shader;
		}
	}
	return NULL;
}

} // namespace cpu_render
