#pragma once
#include <glm/glm.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "Node.hpp"
#include "VisualServer.h"
#include "camera.hpp"

#define MAX_FPS 30.0

namespace eng {

class Engine {
    bool process_events(float delta);
    void process_keyboard_events(const Uint8* keyboard_state, float delta);
    void process_rotation(int xrel, int yrel);

   public:
    VisualServer* visual_server;
    Node root;

    static Engine& getInstance() {
        static Engine instance;
        return instance;
    }
    Engine(Engine const&) = delete;
    void operator=(Engine const&) = delete;

    Engine();
    void Run();
    void InputEvent();
    void SubscribeToInputEvents();
};

}   // namespace eng