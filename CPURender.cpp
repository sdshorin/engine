
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

void CPURender::draw_polygon(std::vector<glm::vec4>& points, const Camera *camera, const GraphicSettings* settings, int32_t* frame_buffer) {
	std::cout << "VisualServer draw_polygon \n";

	for (int i = 0; i < points.size(); i += 3) {
		std::vector<glm::vec4> v = {points[i], points[i + 1], points[i + 2]};

		glm::mat4 camera_matrix = camera->get_camera_matrix();

        camera_matrix = camera->get_projection_matrix() * camera_matrix;
        // camera_matrix = camera_matrix;


		for (int i = 0; i < 3; ++i) {

			v[i] = camera_matrix * v[i];
			v[i] = v[i] / v[i].w;

			v[i].x = v[i].x * 0.5 + 0.5f;
			v[i].y = -v[i].y * 0.5 + 0.5f;

			v[i].x *= settings->window_width;
        	v[i].y *= settings->window_high;


		}

		Rectangle rect(v[0].x, v[0].y);
		rect.add_point(v[1].x, v[1].y);
		rect.add_point(v[2].x, v[2].y);
       
		std::cout << "rect: "  << rect  << "\n";

        rect.x = std::max(0.0f, rect.x);
        rect.y = std::max(0.0f, rect.y);
        rect.size_x = std::min(settings->window_width - rect.x, rect.size_x);
        rect.size_y = std::min(settings->window_high - rect.y, rect.size_y);


		std::cout << "volume: "  << edge_function(v[0], v[1], v[2]) / 2   << "\n";
        float triangle_square = edge_function(v[0], v[1], v[2]);

        for (int x = rect.x; x < rect.x + rect.size_x; ++x) {
            // std::cout << "|";
            for (int y = rect.y; y < rect.y + rect.size_y; ++y) {
                glm::vec4 point(x, y, 0, 1);

                float e_1 = edge_function(v[0], v[1], point) / triangle_square;
                float e_2 = edge_function(v[1], v[2], point) / triangle_square;
                float e_3 = edge_function(v[2], v[0], point) / triangle_square;

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

		// rect.



	}

}