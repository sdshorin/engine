#pragma once
# include <glm/glm.hpp>
# include <vector>
#include "VisualServer.h"

class TreeObject {
	glm::mat4 transform;
	std::vector<TreeObject*> childrens;
public:
	void Notification(int notification);
	void add_child(TreeObject* node);
	void draw(VisualServer* server) const;
	virtual void draw_self(VisualServer* server) const;
};








