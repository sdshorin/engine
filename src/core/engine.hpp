#pragma once
#include <glm/glm.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "Node.hpp"
#include "VisualServer.h"
#include "camera.hpp"
#include "ProjectSettings.hpp"

#define MAX_FPS 30.0

namespace eng {

class Engine {
    bool process_events(float delta);
    void process_keyboard_events(const Uint8* keyboard_state, float delta);
    void process_rotation(int xrel, int yrel);

   public:
    VisualServer visual_server;
    Node root;

    eng::ResourceRef load_resource(const std::string& path);


    Engine(const ProjectSettings& settings);
    void Run();
    void InputEvent();
    void SubscribeToInputEvents();
};

}   // namespace eng