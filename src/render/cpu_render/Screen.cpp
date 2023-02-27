#include "Screen.hpp"
#include <iostream>

namespace cpu_render {

Screen::Screen() {
    window_width = 100;
    window_high = 100;
    frame_buffer = new int32_t[window_width * window_high];
	z_buffer = new float[window_width * window_high];
    std::cout << "Create screen (default)" <<  window_width << " " << window_high << std::endl;
}


Screen::Screen(int window_high, int window_width): window_high(window_high), window_width(window_width)  {
    frame_buffer = new int32_t[window_width * window_high];
	z_buffer = new float[window_width * window_high];
    std::cout << "Create screen" <<  window_width << " " << window_high << std::endl;
}


Screen::~Screen() {
    if (frame_buffer) {
        delete[] frame_buffer;
    }
    if (z_buffer) {
        delete[] z_buffer;
    }
    std::cout << "Delete screen " << window_width << " " << window_high << std::endl;
}

Screen& Screen::operator=(Screen&& other) {
    std::cout << "Move screen " << std::endl;
     if (frame_buffer) {
        delete[] frame_buffer;
    }
    if (z_buffer) {
        delete[] z_buffer;
    }
    window_width = other.window_width;
    window_high = other.window_high;
    frame_buffer = other.frame_buffer;
    z_buffer = other.z_buffer;

    other.frame_buffer = NULL;
    other.z_buffer = NULL;

    return *this;
}

} // namespace cpu_render
