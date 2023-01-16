
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



void CPURender::draw_mesh(BaseVisualStorage* data, const BaseShader* shader_params, const GraphicSettings* settings, int32_t* frame_buffer) {
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

			p[i].pos.x *= settings->window_width;
        	p[i].pos.y *= settings->window_high;


		}

		Rectangle rect(p[0].pos.x, p[0].pos.y);
		rect.add_point(p[1].pos.x, p[1].pos.y);
		rect.add_point(p[2].pos.x, p[2].pos.y);
       
		std::cout << "rect: "  << rect  << "\n";

        rect.x = std::max(0.0f, rect.x);
        rect.y = std::max(0.0f, rect.y);
        rect.size_x = std::min(settings->window_width - rect.x, rect.size_x);
        rect.size_y = std::min(settings->window_high - rect.y, rect.size_y);


		std::cout << "volume: "  << edge_function(p[0].pos, p[1].pos, p[2].pos) / 2   << "\n";
        float triangle_square = edge_function(p[0].pos, p[1].pos, p[2].pos);

        for (int x = rect.x; x < rect.x + rect.size_x; ++x) {
            // std::cout << "|";
            for (int y = rect.y; y < rect.y + rect.size_y; ++y) {
                glm::vec4 point(x, y, 0, 1);

                float e_1 = edge_function(p[0].pos, p[1].pos, point) / triangle_square;
                float e_2 = edge_function(p[1].pos, p[2].pos, point) / triangle_square;
                float e_3 = edge_function(p[2].pos, p[0].pos, point) / triangle_square;

                if (std::signbit(e_1) == std::signbit(e_2) && std::signbit(e_2) == std::signbit(e_3)) {
                        int32_t a8 = 255;
                        int32_t r8 = int32_t(1 * 255.0f);
                        int32_t g8 = int32_t(0 * 255.0f);
                        int32_t b8 = int32_t(0 * 255.0f);
                        int32_t col32 = a8 << 24 | b8 << 16 | g8 << 8 | r8;
                        frame_buffer[y * settings->window_width + x] = col32;

                    // std::cout << x << " " << y << "\n";
                } else {
					// int32_t r8 = int32_t(((std::signbit(e_1))? 1 : 0) * 255.0f);
					// int32_t g8 = int32_t(((std::signbit(e_2))? 1 : 0) * 255.0f);
					// int32_t b8 = int32_t(((std::signbit(e_3))? 1 : 0) * 255.0f);

					// frame_buffer[y * settings->window_width + x] = r8 << 24 | g8 << 16 | b8 << 8 | r8;
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



CPURender::CPURender() {
	shader_algorithms.push_back(new ProjectionShaderImplementation);
}

ShaderImplementation* CPURender::GetShader(BaseShader::ShaderType type) {
	for (ShaderImplementation* shader : shader_algorithms) {
		if (shader->type == type) {
			return shader;
		}
	}
	return NULL;
}

