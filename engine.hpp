#pragma once
# include <vector>
# include <string>
# include <glm/glm.hpp>
#include "VisualServer.h"
#include "camera.hpp"


#include <iostream>

class TreeObject {
	glm::mat4 transform;
	std::vector<TreeObject*> childrens;
public:
	void Notification(int notification);
	void add_child(TreeObject* node);
	void draw(VisualServer* server) const;
	virtual void draw_self(VisualServer* server) const;
};

class Triangle: public TreeObject {
	void draw_self(VisualServer* server) const override;
};

// class VisualObject: TreeObject {
// public:
// 	void TreeNotification(int notification);

// };

class Engine {

	bool process_events(float delta);
	void process_keyboard_event(SDL_Keycode sym, float delta);
public:
	VisualServer *visual_server;
	TreeObject* root;

	Engine();
	void Run();
	void InputEvent();
	void SubscribeToInputEvents();
};