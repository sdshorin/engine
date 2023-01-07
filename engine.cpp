

#include "engine.hpp"
#include <unistd.h>
#include <iostream>

Engine::Engine() {
    root = new TreeObject;
}

void Engine::Run() {
    bool is_running = true;
    while (is_running) {
        SDL_Event event;
         while (SDL_PollEvent(&event) != 0)
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    is_running = false;
                    std::cout << "Exit \n";
                    break;
            }
        }
        if (!is_running) {
            break;
        }
        usleep(2000000);
        visual_server->flush();
        // root->process(0.02);
        root->draw(visual_server);
        visual_server->RenderScreen();
    }
}



