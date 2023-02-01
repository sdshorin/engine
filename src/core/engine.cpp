

#include "engine.hpp"
#include <unistd.h>
#include <iostream>
#include <chrono>

Engine::Engine() {
}

void Engine::Run() {
    bool is_running = true;
    auto loop_start = std::chrono::steady_clock::now();
    float delta = 0.2;
    while (is_running) {
        loop_start = std::chrono::steady_clock::now();
        is_running = process_events(delta / 1000);
        if (!is_running) {
            break;
        }
        visual_server->flush();
        root.process_notification(delta / 1000);
        root.draw_notification(visual_server);
        visual_server->RenderScreen();
        
        
        auto loop_end = std::chrono::steady_clock::now();
        float used_time = delta = std::chrono::duration_cast<std::chrono::milliseconds>(loop_end - loop_start).count();
        long sleep_time = std::max(static_cast<long>(1000.0 / MAX_FPS - used_time), 0L);
        delta = used_time + sleep_time;
        std::cout << "FPS: " << 1000.0 / delta << "\n";
        
        usleep(sleep_time * 1000);
    }
}


void Engine::process_keyboard_events(const Uint8* keyboard_state, float delta) {
    if (keyboard_state[SDL_SCANCODE_W]) {
        visual_server->camera->move(visual_server->camera->front * delta);
    }
    if (keyboard_state[SDL_SCANCODE_S]) {
        visual_server->camera->move(-visual_server->camera->front * delta);
    }
    if (keyboard_state[SDL_SCANCODE_A]) {
        visual_server->camera->move_left(delta);
    }
    if (keyboard_state[SDL_SCANCODE_D]) {
        visual_server->camera->move_right(delta);
    }
    if (keyboard_state[SDL_SCANCODE_Q]) {
        visual_server->camera->move_up(delta);
    }
    if (keyboard_state[SDL_SCANCODE_E]) {
        visual_server->camera->move_down(delta);
    }
}

void Engine::process_rotation(int xrel, int yrel) {
    visual_server->camera->rotate(xrel, -yrel);

}

bool Engine::process_events(float delta) {
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0)
    {
        switch (event.type)
        {
            case SDL_QUIT:
                std::cout << "Exit \n";
                return false;
                break;
            case SDL_MOUSEMOTION:
                process_rotation(event.motion.xrel, event.motion.yrel);
                break;
        }
    }

    const Uint8* state = SDL_GetKeyboardState(nullptr);
    if (state[SDL_SCANCODE_ESCAPE]) {
        std::cout << "Exit \n";
        return false;
    }
    process_keyboard_events(state, delta);


    return true;
}


