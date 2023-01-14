#pragma once
# include <vector>
# include <string>
# include <glm/glm.hpp>
#include "VisualServer.h"
#include "camera.hpp"
#include "TreeObject.hpp"

#include <iostream>




class Engine {

	bool process_events(float delta);
	void process_keyboard_event(SDL_Keycode sym, float delta);
public:
	VisualServer *visual_server;
	TreeObject root;

	static Engine& getInstance()
	{
		static Engine instance;
		return instance;
    }
 	Engine(Engine const&) = delete;
    void operator=(Engine const&)  = delete;
	
	Engine();
	void Run();
	void InputEvent();
	void SubscribeToInputEvents();
};