
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
		glm::vec4 v0, v1, v2;
		glm::mat4 camera_matrix = camera->get_camera_matrix();

        camera_matrix = camera->get_projection_matrix() * camera_matrix;
		
		// v0 = points[i];
		// v1 = points[i + 1];
		// v2 = points[i + 2];
		v0 = camera_matrix * points[i];
		v1 = camera_matrix * points[i + 1];
		v2 = camera_matrix * points[i + 2];

        // glm::vec4 test = v0;
        // std::reference_wrapper<glm::vec<4, float, glm::packed_highp>> test = std::ref(v0);
        // test = v1;


		// for (auto& point : {std::ref(v0), std::ref(v1), std::ref(v2)}) {
        //     point = v0;
		// 	point = camera_matrix * point;
		// 	point = point / point.w;
		// 	point.x *= 
		// }

		// for 

		v0 = v0 / v0.w;
		v1 = v1 / v1.w;
		v2 = v2 / v2.w;

        v0.x *= settings->window_width;
        v0.y *= settings->window_high;
        v1.x *= settings->window_width;
        v1.y *= settings->window_high;
        v2.x *= settings->window_width;
        v2.y *= settings->window_high;


		Rectangle rect(v0.x, v0.y);
		std::cout << "v0:"  << glm::to_string(v0).c_str()   << "\n";
		std::cout << "rect: "  << rect  << "\n";

		std::cout << "v1:"  << glm::to_string(v1).c_str()   << "\n";
		rect.add_point(v1.x, v1.y);
		std::cout << "rect: "  << rect  << "\n";

		std::cout << "v2:"  << glm::to_string(v2).c_str()   << "\n";
		rect.add_point(v2.x, v2.y);
		std::cout << "rect: "  << rect  << "\n";

        rect.x = std::max(0.0f, rect.x);
        rect.y = std::max(0.0f, rect.y);
        rect.size_x = std::min(settings->window_width - rect.x, rect.size_x);
        rect.size_y = std::min(settings->window_high - rect.y, rect.size_y);


		std::cout << "volume: "  << edge_function(v0, v1, v2) / 2   << "\n";
        float triangle_square = edge_function(v0, v1, v2);

        for (int x = rect.x; x < rect.size_x; ++x) {
            // std::cout << "|";
            for (int y = rect.y; y < rect.size_y; ++y) {
                glm::vec4 point(x, y, 0, 1);

                float e_1 = edge_function(v1, v2, point) / triangle_square;
                float e_2 = edge_function(v0, v2, point) / triangle_square;
                float e_3 = edge_function(v0, v1, point) / triangle_square;

                if (std::signbit(e_1) == std::signbit(e_2) && std::signbit(e_2) == std::signbit(e_3)) {
                        int32_t a8 = 255;
                        int32_t r8 = int32_t(1 * 255.0f);
                        int32_t g8 = int32_t(0 * 255.0f);
                        int32_t b8 = int32_t(0 * 255.0f);
                        int32_t col32 = a8 << 24 | b8 << 16 | g8 << 8 | r8;
                        frame_buffer[y * settings->window_width + x] = col32;

                    // std::cout << x << " " << y << "\n";
                } else {
                    // std::cout << "0";
                }
            }
            // std::cout << "|\n";

        }

		// rect.



	}

}