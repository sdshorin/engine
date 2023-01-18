#pragma once
#include <SDL2/SDL.h> 

struct Screen {
    int32_t* frame_buffer;
    float* z_buffer;
    int window_high;
	int window_width;
};
