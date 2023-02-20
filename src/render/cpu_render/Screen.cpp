#include "Screen.hpp"

Screen::Screen() {
    window_width = 100;
    window_high = 100;
    frame_buffer = new int32_t[window_width * window_high];
	z_buffer = new float[window_width * window_high];
}


Screen::Screen(int window_high, int window_width): window_high(window_high), window_width(window_width)  {
    frame_buffer = new int32_t[window_width * window_high];
	z_buffer = new float[window_width * window_high];
}


Screen::~Screen() {
    if (frame_buffer) {
        delete[] frame_buffer;
    }
    if (z_buffer) {
        delete[] z_buffer;
    }
}



