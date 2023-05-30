#pragma once
#include <SDL2/SDL.h>

namespace cpu_render {

struct Screen {
    int32_t* frame_buffer;
    float* z_buffer;
    int window_high;
    int window_width;

    Screen();
    Screen& operator=(Screen&& other);
    Screen(int window_high, int window_width);
    ~Screen();
};

}   // namespace cpu_render
