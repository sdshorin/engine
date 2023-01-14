

#include "engine.hpp"
#include <unistd.h>
#include <iostream>


Engine::Engine() {
}

void Engine::Run() {
    bool is_running = true;
    while (is_running) {
        float delta = 0.2;
        is_running = process_events(delta);
        if (!is_running) {
            break;
        }
        visual_server->flush();
        // root->process(0.02);
        root.draw(visual_server);
        visual_server->RenderScreen();
        usleep(200000);
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


