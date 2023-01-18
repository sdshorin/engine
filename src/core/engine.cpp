

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
        // root->process(0.02);
        root.draw(visual_server);
        visual_server->RenderScreen();
        
        
        auto loop_end = std::chrono::steady_clock::now();
        float used_time = delta = std::chrono::duration_cast<std::chrono::milliseconds>(loop_end - loop_start).count();
        long sleep_time = std::max(static_cast<long>(1000.0 / MAX_FPS - used_time), 0L);
        delta = used_time + sleep_time;
        
        usleep(sleep_time * 1000);
    }
}

void Engine::process_keyboard_event(SDL_Keycode sym, float delta) {
    switch (sym)
    {
    case SDLK_w:
        visual_server->camera->move(visual_server->camera->front * delta);
        break;
    case SDLK_s:
        visual_server->camera->move(-visual_server->camera->front * delta);
        break;
    case SDLK_a:
        visual_server->camera->move_left(delta);
        break;
    case SDLK_d:
        visual_server->camera->move_right(delta);
        break;
    case SDLK_q:
        visual_server->camera->move_up(delta);
        break;
    case SDLK_e:
        visual_server->camera->move_down(delta);
        break;
    default:
        break;
    }
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
            case SDL_KEYDOWN:
                process_keyboard_event(event.key.keysym.sym, delta);
                break;
            
        }
    }
    return true;
}


